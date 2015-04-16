#!/bin/ksh
g_datasyn_synid=`sed '/^g_datasyn_synid=/!d;s/.*=//' /u01/app/HA/ha.cnf`
g_datasyn_synid=`echo $g_datasyn_synid|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

master_hostname=`sed '/^ha_master_hostname=/!d;s/.*=//' /u01/app/HA/ha.cnf`
master_hostname=`echo $master_hostname|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

slave_hostname=`sed '/^ha_slave_hostname=/!d;s/.*=//' /u01/app/HA/ha.cnf`
slave_hostname=`echo $slave_hostname|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

user=`sed '/^ha_user=/!d;s/.*=//' /u01/app/HA/ha.cnf`|sed 's/ *$//g'
user=`echo $user|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

passwd=`sed '/^ha_passwd=/!d;s/.*=//' /u01/app/HA/ha.cnf`
passwd=`echo $passwd|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

port=`sed '/^ha_port=/!d;s/.*=//' /u01/app/HA/ha.cnf`
port=`echo $port|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

timeout=`sed '/^ha_timeout=/!d;s/.*=//' /u01/app/HA/ha.cnf`
timeout=`echo $timeout|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`


g_datasyn_exe_path=`sed '/^g_datasyn_exe_path=/!d;s/.*=//' /u01/app/HA/ha.cnf`
g_datasyn_exe_path=`echo $g_datasyn_exe_path|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

g_datasyn_config_file_path=`sed '/^g_datasyn_config_file_path=/!d;s/.*=//' /u01/app/HA/ha.cnf`
g_datasyn_config_file_path=`echo $g_datasyn_config_file_path|sed 's/^[ \t]*//g'|sed 's/[ \t]*$//g'`

g_datasyn_status="null"
i=0
slave_err_cnt=0

if [ "$g_datasyn_synid" = "" -o "$master_hostname" = "" ]; then
  echo "Please set the configuration file /u01/app/HA/ha.cnf properly."
  exit 1
fi

if [ "$user" = "" ]; then
	user="root"
fi


if [ "$passwd" = "" ]; then
	passwd="root"
fi

if [ "$port" = "" ]; then
	port="3306"
fi
	
if [ "$timeout" = "" ]; then
	timeout="2"
fi
	
 get_readonly_status()
{
lv_readonly=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_VARIABLES  where variable_name = 'READ_ONLY';
`

echo "lv_readonly:"$lv_readonly 
}

 get_slave_status()
{
lv_status=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_STATUS  where variable_name = 'SLAVE_RUNNING';
`
if [ "$lv_status" = "ON" ]; then
	lv_status="ON"
	if [ $slave_err_cnt != 0 ]; then
		slave_err_cnt=0
		echo "Slave status of $slave_hostname is recovered to ON." 1>&2
	fi
else
	ping $slave_hostname $timeout > /dev/null
	if [ $? -eq 0 ]; then
		#Add connect-timeout by Will on 5Jun2013
		#lv_status=`mysql --connect-timeout=$timeout -N -r -B -h$slave_hostname -u$user -p$passwd 2>&1 << END
		lv_status=`mysql --connect-timeout=$timeout -N -r -B -h$slave_hostname -u$user -p$passwd 2>&1 << END		
	SELECT variable_value FROM information_schema.GLOBAL_STATUS  where variable_name = 'SLAVE_RUNNING';
`
		if [ $? != 0 -a $slave_err_cnt = 0 ]; then
			echo "ERROR"${lv_status#*"ERROR"} 1>&2
			echo "NOTE: Slave connection error will be reported one time only until recover." 1>&2
			slave_err_cnt=$((slave_err_cnt+1))
			lv_status=""
		elif [ $? != 0 -a $slave_err_cnt != 0 ]; then
			slave_err_cnt=$((slave_err_cnt+1))
			lv_status=""
		fi 

		if [ "$lv_status" = "" ]; then
			lv_status="OFF"
		else
			lv_status="ON"
			if [ $slave_err_cnt != 0 ]; then
				slave_err_cnt=0
				echo "Slave status of $slave_hostname is recovered to ON." 1>&2
			fi
		fi	
	else 
		lv_status="OFF"
		if [ $slave_err_cnt = 0 ]; then
			echo "Ping $slave_hostname timeout in $timeout seconds." 1>&2
			echo "NOTE: Slave connection error will be reported one time only until recover." 1>&2
			slave_err_cnt=$((slave_err_cnt+1))
		fi	
	fi
fi

echo "lv_status:"$lv_status
}

 get_rem_readonly_status()
{
lv_rem_readonly=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM rep.GLOBAL_VARIABLES_DBLINK where variable_name = 'READ_ONLY';
`

echo "lv_rem_readonly:"$lv_rem_readonly 
}

 get_curr_rid()
{
lv_rid=`mysql -u$user -p$passwd -e "show slave status\G"|grep Retrieved_Gtid_Set`
lv_rid=${lv_rid##*"Retrieved_Gtid_Set:"}
echo "curr_rid:"$lv_rid
}

 get_curr_wid()
{
lv_wid=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_VARIABLES G where variable_name = 'GTID_DONE';
`
echo "curr_wid:"$lv_wid
}

 get_saved_rid()
{
lv_s_rid=`mysql -N -r -B -u$user -p$passwd << END
	SELECT value FROM rep.adm_rep_variables where variable_name = 'LAST_RETRIEVED_GTID';
`
echo "saved_rid:"$lv_s_rid
}

 get_saved_wid()
{
lv_s_wid=`mysql -N -r -B -u$user -p$passwd << END
	SELECT value FROM rep.adm_rep_variables where variable_name = 'LAST_EXECUTED_GTID';
`
echo "saved_wid:"$lv_s_wid
}

 get_rem_saved_wid()
{
lv_rem_s_wid=`mysql -N -r -B -u$user -p$passwd << END
	SELECT value FROM rep.adm_rep_variables_dblink where variable_name = 'LAST_EXECUTED_GTID';
`
echo "lv_rem_s_wid:"$lv_rem_s_wid
}


 get_readonly_time()
{
lv_readonly_time=`mysql -N -r -B -u$user -p$passwd << END
	select updtime from rep.adm_rep_mon where status = 'READ';
`
lv_readonly_time=`echo $lv_readonly_time | tr -d "[-][:][ ]"`

echo "lv_readonly_time:"$lv_readonly_time 
}

 get_rem_readonly_time()
{
lv_rem_readonly_time=`mysql -N -r -B -u$user -p$passwd << END
	select updtime from rep.adm_rep_mon_dblink where status = 'READ';
`
lv_rem_readonly_time=`echo $lv_rem_readonly_time | tr -d "[-][:][ ]"`

echo "lv_rem_readonly_time:"$lv_rem_readonly_time 
}

 get_readwrite_time()
{
lv_write_time=`mysql -N -r -B -u$user -p$passwd << END
	select updtime from rep.adm_rep_mon where status = 'WRITE';
`
lv_write_time=`echo $lv_write_time | tr -d "[-][:][ ]"`

echo "lv_write_time:"$lv_write_time 
}

 get_rem_readwrite_time()
{
lv_rem_write_time=`mysql -N -r -B -u$user -p$passwd << END
	select updtime from rep.adm_rep_mon_dblink where status = 'WRITE';
`
lv_rem_write_time=`echo $lv_rem_write_time | tr -d "[-][:][ ]"`

echo "lv_rem_write_time:"$lv_rem_write_time 
}

 get_sign()
 {
 lv_sign=`mysql -N -r -B -u$user -p$passwd << END
	SELECT value FROM rep.adm_rep_variables where name = 'IsFromRWtoRO';
`

 echo "lv_sign:"$lv_sign
 }
 
 start_slave()
 {
 lv_slave_status=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_STATUS where variable_name='SLAVE_RUNNING';
`
  if [ $lv_slave_status = 'OFF' ]; then
	`mysql -N -r -B -u$user -p$passwd << END
		start slave;
	` 
  fi
  
 lv_slave_status=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_STATUS where variable_name='SLAVE_RUNNING';
`
 echo "lv_slave_status:"$lv_slave_status
 }

  stop_slave()
 {
# Prevent slave auto start. 
# will use stop_slave when handle data merge
	`mysql -N -r -B -u$user -p$passwd << END
	stop slave;
	`
  
 lv_slave_status=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_STATUS where variable_name='SLAVE_RUNNING';
`
 echo "lv_slave_status:"$lv_slave_status  
 }

 get_srv_id()
 {
 lv_srv_id=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.global_variables where variable_name='SERVER_ID';;
`

 echo "lv_srv_id:"$lv_srv_id
 } 
 
  get_rem_srv_id()
 {
 lv_rem_srv_id=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM rep.global_variables_dblink g where variable_name='SERVER_ID';;
`

 echo "lv_rem_srv_id:"$lv_rem_srv_id
 } 
 
 # Add check_slave_apply by Will on 5Jun2013
  check_slave_apply()
  {
  lv_read_master_log_pos=`mysql -u$user -p$passwd -e "show slave status\G"|grep Read_Master_Log_Pos`
  lv_read_master_log_pos=${lv_read_master_log_pos##*"Read_Master_Log_Pos:"}
  echo "read_master_log_pos:"$lv_read_master_log_pos
  
  lv_exec_master_log_pos=`mysql -u$user -p$passwd -e "show slave status\G"|grep Exec_Master_Log_Pos`
  lv_exec_master_log_pos=${lv_exec_master_log_pos##*"Exec_Master_Log_Pos:"}
  echo "exec_master_log_pos:"$lv_exec_master_log_pos
  
  if [ $lv_exec_master_log_pos -lt $lv_read_master_log_pos ]; then
  lv_check_slave_apply=0
  else 
  lv_check_slave_apply=1
  fi
  
  echo "check_slave_apply:"$lv_check_slave_apply
  }
  
  # notify SynchEngine the DB current status
 notify_datasyn()
 {	
	# check the pass in mode
	case $1 in
		'control') 
		v_proc_count=`ps -ef | grep "SynID="$g_datasyn_synid | grep -v grep | awk '{print $2}' |wc -l`
		if [ $v_proc_count -eq 0 -o $g_datasyn_status != $1 ]; then			
			g_datasyn_status=$1
			if [ $v_proc_count -eq 0 ]; then
				$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=stop  
			fi
			$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=control &	
			echo "datasyn_status:"$g_datasyn_status			
		fi		
		;;
		'monitor')
		v_proc_count=`ps -ef | grep "SynID="$g_datasyn_synid | grep -v grep | awk '{print $2}' |wc -l`
		if [ $v_proc_count -eq 0 -o $g_datasyn_status != $1 ]; then
			g_datasyn_status=$1
			if [ $v_proc_count -eq 0 ]; then
				$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=stop  
			fi
			$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=monitor &	
			echo "datasyn_status:"$g_datasyn_status	
		fi
		;;		
		'stop')
		v_proc_count=`ps -ef | grep "SynID="$g_datasyn_synid | grep -v grep | awk '{print $2}' |wc -l`
		if [ $v_proc_count -eq 0 ]; then
			echo "there is no SynchEngine running..."
		else			
			$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=stop 
			echo "stop datasyn..."
		fi 
		;;		
		*)
		echo "Usage: start_datasyn  {control|monitor|stop}"
		exit 1
		;;
	esac
 }

 # monitor the memory usage of the SynchEngine at station. 
 # if memory usage >300MB, then restart.
monitor_mem_status()
{
	v_proc_id=`ps -ef | grep "SynID="$g_datasyn_synid | grep -v grep | cut -c10-15`
	if [ -z $v_proc_id ]; then
		echo "no related SynchEngine running..."
		return 1
	fi
	
	echo $v_proc_id | grep " " >/dev/null
	if [ $? != 0 ]; then	
		v_mem_used=`ps -p $v_proc_id -o vsz | awk 'NR==2{printf ($1)}'`	
		if [ $v_mem_used -ge 300000 ]; then
			echo "memory usage is exceed, restart..."
			kill -9 $v_proc_id
		fi
	fi	
}

 main()
 {
##########################################
# Main
##########################################
get_readonly_status
get_slave_status
#get_rid

if [ "$lv_readonly" = "" ]; then
  notify_datasyn "stop"
fi

if [ "$lv_readonly" = "ON" -a "$lv_status" = "OFF" ]; then
# will use stop_slave when handle data merge
 #stop_slave
 #get_curr_rid
 #get_curr_wid
 check_slave_apply
 if [ $lv_check_slave_apply = 1 ]; then
	 `mysql -N -r -B -u$user -p$passwd << END
		#update rep.adm_rep_variables set value="$lv_rid" where name = 'LAST_RETRIEVED_GTID';
		#update rep.adm_rep_variables set value="$lv_wid" where name = 'LAST_EXECUTED_GTID';
		update rep.adm_rep_mon set times=times+1, updtime=now() where status='WRITE';
		set global read_only='OFF';
		#update rep.adm_rep_sign set sign=1;
		update rep.adm_rep_variables set value = '1' where name = 'IsFromRWtoRO';
	`
	# notify SynchEngine to be control mode
	  notify_datasyn "control"	
 else
	echo "Slave logs have not been applied completely. Status will not change. 
	lv_read_master_log_pos:$lv_read_master_log_pos;lv_exec_master_log_pos:$lv_exec_master_log_pos." 1>&2
 fi	
 return
fi

if [ "$lv_readonly" = "ON" -a "$lv_status" = "ON" ]; then
 get_rem_readonly_status
 if [ "$lv_rem_readonly" = "ON" ]; then
	get_readonly_time
	get_rem_readonly_time
	if [ $lv_readonly_time -lt $lv_rem_readonly_time ]; then
	check_slave_apply
		if [ $lv_check_slave_apply = 1 ]; then
			`mysql -N -r -B -u$user -p$passwd << END
			update rep.adm_rep_mon set times=times+1, updtime=now() where status='WRITE';
			set global read_only='OFF';
			`
		else
			echo "Slave logs have not been applied completely. Status will not change.
			lv_read_master_log_pos:$lv_read_master_log_pos;lv_exec_master_log_pos:$lv_exec_master_log_pos." 1>&2
		fi			
	fi
 fi
  start_slave
  # notify SynchEngine to be monitor mode
  notify_datasyn "monitor"  
 return
fi

if [ "$lv_readonly" = "OFF" -a "$lv_status" = "ON" ]; then
 get_rem_readonly_status
  if [ "$lv_rem_readonly" = "ON" ]; then
	get_sign
	if [ $lv_sign = 1 ]; then
	  #get_saved_rid
	  #get_rem_saved_wid
	  #echo $lv_rem_s_wid|/usr/xpg4/bin/grep -q $lv_s_rid
	  #if [ $? -eq 0 ]; then
		`mysql -N -r -B -u$user -p$passwd << END
		start slave;
		#update rep.adm_rep_sign set sign=0;
		update rep.adm_rep_variables set value = '0' where name = 'IsFromRWtoRO';
		`
		return
	  #else 
	  #   echo "LAST_RETRIEVED_GTID<>REMOTE_LAST_EXECUTED_GTID!!!"
      #	`mysql -N -r -B -u$user -p$passwd << END
	  #	insert into rep.adm_rep_gtid_log(last_rec_gtid,last_exec_gtid) 
	  #		values ($lv_s_rid,$lv_rem_s_wid);
	  #	start slave;
	  #	update rep.adm_rep_sign set sign=0;
	  #	`
	  #	return
	  #fi
	fi
	start_slave
    # notify SynchEngine to be control mode
	notify_datasyn "control"	
	#return
  elif [ "$lv_rem_readonly" = "OFF" ]; then
	 get_readwrite_time
	 get_rem_readwrite_time
		if [ $lv_write_time -lt $lv_rem_write_time ]; then
			`mysql -N -r -B -u$user -p$passwd << END
			update rep.adm_rep_mon set times=times+1, updtime=now() where status='READ';
			set global read_only='ON';
			`
			#get_curr_rid
			#get_curr_wid
			#`mysql -N -r -B -u$user -p$passwd << END
			#update rep.adm_rep_variables set value="$lv_rid" where name = 'LAST_RETRIEVED_GTID';
			#update rep.adm_rep_variables set value="$lv_wid" where name = 'LAST_EXECUTED_GTID';
			#`	
		    # notify SynchEngine to be monitor mode
			notify_datasyn "monitor"			
		elif [ $lv_write_time -eq $lv_rem_write_time ]; then
			get_srv_id
			get_rem_srv_id
				if [ $lv_srv_id -gt $lv_rem_srv_id ]; then
					`mysql -N -r -B -u$user -p$passwd << END
					update rep.adm_rep_mon set times=times+1, updtime=now() where status='READ';
					set global read_only='ON';
					`
					notify_datasyn "monitor"
				else
					notify_datasyn "control"
				fi
		else
			notify_datasyn "control"
		fi
	start_slave
  fi
	#start_slave
    return
elif [ "$lv_readonly" = "OFF" -a "$lv_status" = "OFF" ]; then
# will use stop_slave when handle data merge
#	stop_slave
#	start_slave
	notify_datasyn "control"	
fi
monitor_mem_status		
}

##########################################
#Loop Begin
##########################################
while :; do
main
i=$((i+1))
echo $i
sleep 1
done