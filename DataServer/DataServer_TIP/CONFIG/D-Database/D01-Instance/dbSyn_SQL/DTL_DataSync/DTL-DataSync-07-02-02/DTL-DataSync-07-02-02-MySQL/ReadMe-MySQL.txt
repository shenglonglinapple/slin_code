/*=====================================================
Version: DTL-DataSync-07-02-02-MySQL

This patch should be applied following DTL-DataSync-07-02-MySQL.
-----------

number of scripts: 1
scripts name:
1.DTL-DataSync-07-02-02-MySQL-Main.sql		-- Drop triggers if exists.

========================================================*/

/*=====================================================
Installation Steps
------------
1. Please apply the DB patch on both nodes if it's HA(failover) environment.
2. cd to the folder containing these patches 
3. Login MySQL Node A database by the database supper user 'root' of the database.  
mysql --comments -h[DBserver_hostname] -u[rootuser] -p[rootpasswd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-01 -uroot -proot -Dtra_occ 
4. type below command and Enter:
source DTL-DataSync-07-02-02-MySQL-Main.sql
5. Login MySQL Node B database by the database supper user 'root' of the database.  
mysql --comments -h[DBserver_hostname] -u[rootuser] -p[rootpasswd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-02 -uroot -proot -Dtra_occ 
6. type below command and Enter:
source DTL-DataSync-07-02-02-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
========================================================*/





