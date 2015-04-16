/*=====================================================
Version: DTL-DataSync-04-MySQL
-----------

number of scripts: 5
scripts name:
1.DTL-DataSync-04-MySQL-Main.sql			-- Main script to call other script(s).
2.DTL-DataSync-04-MySQL-REC-Table.sql		-- Add columns prop_type, db_type of recipient tables.
3.DTL-DataSync-04-MySQL-Create-AQ.sql		-- Recreate AQ tables.
4.DTL-DataSync-04-MySQL-Enq-Update.sql		-- Modify enq procedures.
5.DTL-DataSync-04-MySQL-Deq-Update.sql		-- Modify deq procedures.
========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-04-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




