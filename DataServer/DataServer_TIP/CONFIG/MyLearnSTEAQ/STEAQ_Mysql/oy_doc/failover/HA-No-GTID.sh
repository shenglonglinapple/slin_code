#!/bin/ksh
g_datasyn_synid=$1
master_hostname=$2
slave_hostname=$3
user=$4
passwd=$5
port=$6
i=0
#g_datasyn_synid=1
g_datasyn_status="null"
g_datasyn_exe_path=/u01/app/datasyn/bin/SynchEngine
g_datasyn_config_file_path=/u01/app/datasyn/bin/c_cfg.cnf

if [ ${#} -lt 2 ] || [ "$1" = "-h" -o "$1" = "-?" ]; then
  echo "Usage: $0 <local_hostname> <remote_node_hostname> <username> <passwd> <port> 
  E.G.: ./HA-No-GTID.sh occ-cms-A occ-cms-B root root 3306"
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
	
 get_readonly_status()
{
lv_readonly=`mysql -N -r -B -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_VARIABLES  where variable_name = 'READ_ONLY';
`

echo "lv_readonly:"$lv_readonly 
}

 get_slave_status()
{

lv_status=`mysql -N -r -B -h$slave_hostname -u$user -p$passwd << END
	SELECT variable_value FROM information_schema.GLOBAL_STATUS  where variable_name = 'SLAVE_RUNNING';
`
# The lv_status is not the variable_value of 'SLAVE_RUNNING'
if [ "$lv_status" = "" ]; then
	lv_status="OFF"
else
	lv_status="ON"
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
 lv_slave_status=`mysql -u$user -p$passwd -e "show slave status\G"|grep Slave_SQL_Running:`
 lv_slave_status=${lv_slave_status##*"Slave_SQL_Running:"}
  if [ $lv_slave_status = 'No' ]; then
	`mysql -N -r -B -u$user -p$passwd << END
		start slave;
	` 
  fi
  
 lv_slave_status=`mysql -u$user -p$passwd -e "show slave status\G"|grep Slave_SQL_Running:`
 lv_slave_status=${lv_slave_status##*"Slave_SQL_Running:"}
 echo "lv_slave_status:"$lv_slave_status
 }

  stop_slave()
 {
 lv_slave_status=`mysql -u$user -p$passwd -e "show slave status\G"|grep Slave_SQL_Running:`
 lv_slave_status=${lv_slave_status##*"Slave_SQL_Running:"}
  if [ $lv_slave_status = 'Yes' ]; then
	`mysql -N -r -B -u$user -p$passwd << END
	stop slave;
	`
  fi
  
 lv_slave_status=`mysql -u$user -p$passwd -e "show slave status\G"|grep Slave_SQL_Running:`
 lv_slave_status=${lv_slave_status##*"Slave_SQL_Running:"}
 echo "lv_slave_status:"$lv_slave_status  
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
	
	v_mem_used=`ps -p $v_proc_id -o vsz | awk 'NR==2{printf ($1)}'`	
	if [ $v_mem_used -ge 300000 ]; then
		echo "memory usage is exceed, restart..."
		kill -9 $v_proc_id
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
 stop_slave
 #get_curr_rid
 #get_curr_wid
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
 return
fi

if [ "$lv_readonly" = "ON" -a "$lv_status" = "ON" ]; then
 get_rem_readonly_status
 if [ "$lv_rem_readonly" = "ON" ]; then
	get_readonly_time
	get_rem_readonly_time
	if [ $lv_readonly_time -lt $lv_rem_readonly_time ]; then
		`mysql -N -r -B -u$user -p$passwd << END
		update rep.adm_rep_mon set times=times+1, updtime=now() where status='WRITE';
		set global read_only='OFF';
		`
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
		fi
	start_slave
  fi
	#start_slave
    return
elif [ "$lv_readonly" = "OFF" -a "$lv_status" = "OFF" ]; then
	stop_slave
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