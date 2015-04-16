/*=====================================================
Version: DTL-DataSync-07-03-MySQL
-----------

number of scripts: 2
scripts name:
1.DTL-DataSync-07-03-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-07-03-MySQL-FlushJob.sql		-- Create 'flush-host' job.

========================================================*/

/*=====================================================
Installation Steps Part I
------------
Please execute below steps of Part I on both Nodes:
1. Login MySQL DB Servers via OS user 'mysql'.
2. Login MySQL database via DB user 'root' on local Server. (Can not login DB remotely).
e.g. # mysql -uroot -proot
3. Grant 'RELOAD' to IT271350_5@% by typing below command (Please replace user 'IT271350_5' with proper user name):
mysql> grant reload on *.* to 'IT271350_5'@'%';
mysql> quit;
========================================================*/

/*===Notes===
For Installation Steps Part II:
1. In MySQL failover environment. Please only apply the DB patch scripts on 'ReadWrite' node. But verificate the result value on both nodes.
mysql> select @@read_only;
0--ReadWrite 1--ReadOnly

2. '--comments' is a connection parameter too, please do not ignore it.
===========*/

/*=====================================================
Installation Steps Part II
------------
1. cd to the folder containing these patches 
2. Login MySQL db by the application user of the database. 
mysql --comments -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ 
3. type below command and Enter:
source DTL-DataSync-07-03-MySQL-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
========================================================*/





