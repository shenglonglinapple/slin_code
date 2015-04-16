/*=====================================================
Version: DTL-DataSync-06-05-MySQL

-----------

number of SQL scripts: 2
1.DTL-DataSync-06-05-MySQL-Main.sql	-- Main script to call other script(s).
2.DTL-DataSync-06-05-MySQL-Tab.sql	-- Create AQ check tables.

========================================================*/

/*=====================================================
Installation Steps
------------
For SQL scripts:
1. cd to the folder containing these patches 
3. Login MySQL db(Station DB) by the application user of the database. 
mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-05-MySQL-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
2. Run below SQL to check the values, the all of returned values should be '1':
select if(count(*)=2,1,0) value from information_schema.`TABLES` where table_name in ('aq_deq_token_check','aq_enq_duplicate_check');
========================================================*/




