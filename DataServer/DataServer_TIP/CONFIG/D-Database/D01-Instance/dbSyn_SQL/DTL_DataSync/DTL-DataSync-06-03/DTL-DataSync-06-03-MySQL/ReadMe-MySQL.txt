/*=====================================================
Version: DTL-DataSync-06-03-MySQL
Note: Please apply the DB patch DTL-DataSync-06-MySQL before apply this one.

-----------

number of scripts: 
scripts name: 8
DTL-DataSync-06-03-MySQL-Main.sql		-- Main script to call other script(s).
DTL-DataSync-06-03-MySQL-AQ-Man.sql		-- Modify AQ managed routines.
DTL-DataSync-06-03-MySQL-Recreate-AQ.sql	-- Recreate AQ.
DTL-DataSync-06-03-MySQL-Enq.sql		-- Modify enq routines.
DTL-DataSync-06-03-MySQL-prc_deq.sql		-- Modify deq routines.
DTL-DataSync-06-03-enq_audit_data.sql		-- Modify app enq procedure.
DTL-DataSync-06-03-deq_audit_data.sql		-- Modify app deq procedure.
DTL-DataSync-06-03-MySQL-SeqMerge.sql		-- Create sequence-merge objects.

========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user as 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-03-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




