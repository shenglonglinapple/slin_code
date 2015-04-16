/*=====================================================
Version: DTL-DataSync-06-06-MySQL
Note: Please apply the DB patch DTL-DataSync-06-04-MySQL before apply this one.
-----------

number of SQL scripts: 2
1.DTL-DataSync-06-06-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-06-MySQL-prc_enq_tab.sql	-- Modify function 'prc_enq_table'.

========================================================*/

/*=====================================================
Installation Steps
------------
For SQL scripts:
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the application user of the database. 
mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-06-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
========================================================*/




