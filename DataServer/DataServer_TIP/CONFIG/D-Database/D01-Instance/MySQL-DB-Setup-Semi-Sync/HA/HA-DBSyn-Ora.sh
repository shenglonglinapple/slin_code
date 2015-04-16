#!/bin/ksh
i=0
g_datasyn_synid=$1
g_datasyn_exe_path=/u01/app/datasyn/bin/SynchEngine
g_datasyn_config_file_path=/u01/app/datasyn/bin/s_cfg.cnf

  # notify SynchEngine the DB current status
 notify_datasyn()
 {	
	# check the pass in mode
	case $1 in
		'control') 
		v_proc_count=`ps -ef | grep "SynID="$g_datasyn_synid | grep -v grep | awk '{print $0}' |wc -l`
		if [ $v_proc_count -eq 0 ]; then			
			$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=stop  
			$g_datasyn_exe_path --SynID=$g_datasyn_synid --default-file=$g_datasyn_config_file_path --mode=control &
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

 # monitor the memory usage of the SynchEngine at DBS. 
 # if memory usage >1024MB, then restart.
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
		if [ $v_mem_used -ge 1024000 ]; then
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
notify_datasyn "control"
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