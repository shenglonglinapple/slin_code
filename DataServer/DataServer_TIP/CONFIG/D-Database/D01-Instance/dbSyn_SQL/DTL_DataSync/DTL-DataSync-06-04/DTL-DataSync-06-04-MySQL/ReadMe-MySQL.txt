/*=====================================================
Version: DTL-DataSync-06-04-MySQL
Note: Please apply the DB patch DTL-DataSync-06-03-MySQL before apply this one.
-----------

number of SQL scripts: 2
1.DTL-DataSync-06-04-MySQL-Main.sql	-- Main script to call other script(s).
2.DTL-DataSync-06-04-MySQL-Func-Seq.sql	-- Modify function 'func_seq_get_next_number'.

========================================================*/

/*=====================================================
Installation Steps
------------
For SQL scripts:
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user as 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-04-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
========================================================*/




