/*=====================================================
Version: DTL-DataSync-06-02-MySQL
Note: Please apply the DB patch DTL-DataSync-06-MySQL before apply this one.

-----------

number of scripts: 
scripts name: 3
1.DTL-DataSync-06-02-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-02-MySQL-enq_prc.sql		-- Create prc_enqueue.
3.DTL-DataSync-06-02-MySQL-enq_audit_data.sql	-- Create prc_enqueue_audit_data.

========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user as 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-02-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




