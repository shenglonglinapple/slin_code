/*=====================================================
Version: DTL-DataSync-06-09-MySQL
-----------

number of scripts: 4
scripts name:
1.DTL-DataSync-06-09-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-09-MySQL-Drop-Trg.sql		-- Drop printable triggers.
3.DTL-DataSync-06-09-MySQL-AnalyzeJob.sql	-- Create job to analyze tables.
4.HA-MySQL.bsh					-- New failover script.


========================================================*/

/*=====================================================
Installation Steps
------------
1. Apply DB patch scripts on 'ReadWrite' node.
mysql> select @@read_only;
0--ReadWrite 1--ReadOnly
1.1 cd to the folder containing these patches 
1.2 Login MySQL db by the application user of the database. 
mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ --comments
1.3 type below command and Enter:
source DTL-DataSync-06-09-MySQL-Main.sql

2. Check the mysql path to make sure it can use 'ping'.
Please check whether the OS user ¡®mysql¡¯ can execute the OS command ¡®ping¡¯.
If ¡®ping: command not found¡¯, please adding the path of ¡®ping¡¯ into mysql profile as below.
-bash$ su - mysql
-bash$ cd
-bash$ pwd
/u01/app/mysql
-bash$ echo "export PATH=/usr/sbin:/usr/bin:/usr/local/bin:/u01/app/mysql/bin" >> .profile
-bash$ source .profile
-bash$ ping
usage: ping host [timeout]
usage: ping -s [-l | U] [adLnRrv] [-A addr_family] [-c traffic_class]
        [-g gateway [-g gateway ...]] [-F flow_label] [-I interval]
        [-i interface] [-P tos] [-p port] [-t ttl] host [data_size] [npackets]


3. Replace script HA-MySQL.bsh. (Use OS user mysql)
3.1 Backup old HA-MySQL.bsh
# cd /u01/app/HA
# cp HA-MySQL.bsh HA-MySQL.bsh.bak
3.2 ftp HA-MySQL.bsh into '/u01/app/HA' of both failover Nodes by Binary mode for replacing.
3.3 Chown and Chmod
# cd /u01/app/HA
# chown mysql:mysql HA-MySQL.bsh
# chmod 755 HA-MySQL.bsh

4. Update parameters of MySQL (Only for MySQL Nodes of Failover Environment, please don't apply this item in Single Node MySQL DB without failover)
#########pre-Check##########
# mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name]
a. SELECT if(variable_value=10,1,0) value FROM information_schema.GLOBAL_STATUS G where variable_name='SLAVE_HEARTBEAT_PERIOD';
If the value is equal to 1, please ignore this step 4.
############################
4.1 Login OS by OS user mysql
4.2 Stop HA-MySQL.bsh monitor process on both failover Nodes.
# /u01/app/HA/HA-MySQL.bsh stop
4.3 Change Master Hearbeat period on both failover Nodes:
< # mysql -u[OSMySQLrootUser] -p[OSMySQLrootUserPasswd] >
e.g. mysql -uroot -proot
mysql> stop slave;
mysql> change master to master_heartbeat_period=10;
mysql> start slave;
mysql> quit;
4.4 Start HA-MySQL.bsh monitor process on both failover Nodes.
# /u01/app/HA/HA-MySQL.bsh start <local_hostname> <remote_node_hostname>

5. Generate new my.cnf and replace the old one.
Please run the DB patch tool DTL-MyCnf-Generate according to its readme file.


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
2. Run below SQL to check the values, the all of returned values should be '1':
# mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
mysql> SELECT if(count(*)=0,1,0) value FROM information_schema.TRIGGERS T where trigger_name in ('alarm_printevent_trg','evcom_printevent_trg') and trigger_schema=database();
mysql> SELECT count(*) FROM information_schema.`EVENTS` E where event_name='job_analyze_tab_week' and event_schema=database();
mysql> SELECT count(*) FROM information_schema.`EVENTS` E where event_name='job_analyze_tab_daily' and event_schema=database();
-- Below are Only for the nodes of failover environment.
mysql> SELECT if(variable_value=10,1,0) value FROM information_schema.GLOBAL_STATUS G where variable_name='SLAVE_HEARTBEAT_PERIOD';
mysql> SELECT if(variable_value='1032,1053,1062',1,0) value FROM information_schema.GLOBAL_VARIABLES G where variable_name = 'SLAVE_SKIP_ERRORS';
mysql> SELECT if(variable_value=6,1,0) value FROM information_schema.GLOBAL_VARIABLES G where variable_name = 'SLAVE_NET_TIMEOUT';
mysql> SELECT if(variable_value=5000,1,0) value FROM information_schema.GLOBAL_VARIABLES G where variable_name = 'RPL_SEMI_SYNC_MASTER_TIMEOUT';

3. Double check the mysql path to make sure it can use 'ping'.

========================================================*/





