/*=====================================================
Version: DTL-DataSync-05-MySQL

Note: This DB patch must be applied after DTL-DataSync-04-MySQL applied.
-----------

number of scripts: 3
scripts name:
1.DTL-DataSync-05-MySQL-Main.sql			-- Main script to call other script(s).
2.DTL-DataSync-05-MySQL-Enq.sql			-- Modify enq procedures.
3.DTL-DataSync-05-MySQL-Deq.sql			-- Modify deq procedures.
========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name]
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ
3. type below command and Enter:
source DTL-DataSync-05-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




