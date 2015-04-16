#!/bin/bash

g_datasyn_synid=1
g_datasyn_exe_path=/u01/app/datasync/bin/SynchEngine
g_datasyn_config_file_path=/u01/app/datasync/bin/c_cfg.cnf

mode=$1
#if [ "$1"  -ne "start" -o ]; then
case "$mode" in
  'start')
  #/etc/init.d/mysql.server start
  /u01/app/HA/HA-No-GTID.sh 1>/dev/null 2>> >( while read line; do echo "$(date): ${line}"; done >> /u01/app/HA/HA-No-GTID.log ) &
  ;;
  'stop')
  #/etc/init.d/mysql.server stop
  kill -9 $(pgrep HA-No-GTID)
  $g_datasyn_exe_path --default-file=$g_datasyn_config_file_path --mode=stop --SynID=$g_datasyn_synid
  ;;
  'restart')
  #/etc/init.d/mysql.server restart
  ;;
  'reload')
  #/etc/init.d/mysql.server reload
  ;;
  'force-reload')
  #/etc/init.d/mysql.server force-reload
  ;;
  'status')
  #/etc/init.d/mysql.server status
  ps -ef | grep HA-No-GTID
  ;;
  *)
 	echo "Usage: ./mysql-ha.sh  {start|stop|restart|reload|force-reload|status} "
	exit 1
	;;
esac	