/*=====================================================
Version: DTL-DataSync-06-08-MySQL
-----------

number of scripts: 2
scripts name:
1.DTL-DataSync-06-08-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-08-MySQL-Tab.sql		-- Alter table aq_sys_queue_m add enq_mode.

========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db by the application user of the database. 
mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-08-MySQL-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
2. Run below SQL to check the values, the all of returned values should be '1':
# mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
mysql> SELECT count(*) value FROM information_schema.`COLUMNS` C where table_name='aq_sys_queue_m' and column_name='enq_mode' and table_schema=database();

========================================================*/





