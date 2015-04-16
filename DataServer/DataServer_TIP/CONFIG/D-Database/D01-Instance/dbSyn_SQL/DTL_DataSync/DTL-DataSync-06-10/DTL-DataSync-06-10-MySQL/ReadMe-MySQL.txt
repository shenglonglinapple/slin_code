/*=====================================================
Version: DTL-DataSync-06-10-MySQL
-----------

number of scripts: 3
scripts name:
1.DTL-DataSync-06-10-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-10-MySQL-Enq-NoTrans.sql	-- Create new procedure prc_enqueue_notrans.
3.DTL-DataSync-06-10-MySQL-enq_audit_data.sql	-- Update procedure prc_enqueue_audit_data.

========================================================*/

/*===Notes===
1. In MySQL failover environment. Please only apply the DB patch scripts on 'ReadWrite' node. But verificate the result value on both nodes.
mysql> select @@read_only;
0--ReadWrite 1--ReadOnly

2. '--comments' is a connection parameter too, please do not ignore it.
===========*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db by the application user of the database. 
mysql --comments -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ 
3. type below command and Enter:
source DTL-DataSync-06-10-MySQL-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
2. Run below SQL to check the values, the all of returned values should be '1':
# mysql --comments -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] 
mysql> SELECT if(count(*)=2,1,0) value FROM information_schema.ROUTINES R where routine_name in ('prc_enqueue_audit_data','prc_enqueue_notrans') and routine_schema=database();
========================================================*/





