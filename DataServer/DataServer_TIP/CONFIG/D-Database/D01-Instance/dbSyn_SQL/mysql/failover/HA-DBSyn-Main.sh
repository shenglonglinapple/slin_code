#!/bin/bash
g_datasyn_synid=1
g_datasyn_exe_path=/u01/app/datasyn/bin/SynchEngine
g_datasyn_config_file_path=/u01/app/datasyn/bin/s_cfg.cnf

mode=$1
#if [ "$1"  -ne "start" -o ]; then
case "$mode" in
  'start')
  #/etc/init.d/mysql.server start
  /u01/app/datasyn/bin/HA-DBSyn-Ora.sh 1>/dev/null 2>> >( while read line; do echo "$(date): ${line}"; done >> /u01/app/datasyn/bin/HA-DBSyn-Ora.log ) &
  ;;
  'stop')
  #/etc/init.d/mysql.server stop
  kill -9 $(pgrep HA-DBSyn-Ora)
  $g_datasyn_exe_path --default-file=$g_datasyn_config_file_path --mode=stop --SynID=$g_datasyn_synid
  ;;
 'status')
  #/etc/init.d/mysql.server status
  ps -ef | grep HA-DBSyn-Ora
  ;;
  *)
 	echo "Usage: ./HA-DBSyn-Ora.sh  {start|stop|restart|reload|force-reload|status} "
	exit 1
	;;
esac	