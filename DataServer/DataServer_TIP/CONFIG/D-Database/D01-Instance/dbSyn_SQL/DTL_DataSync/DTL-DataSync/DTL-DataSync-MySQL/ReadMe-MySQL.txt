/*=====================================================
Version: DTL-DataSync-MySQL
-----------

number of scripts: 6
scripts name:
1.DTL-DataSync-MySQL-Main.sql			-- Main script to call other script(s).
2.DTL-DataSync-MySQL-prepare.sql		-- Preparation before create aq objects.
3.DTL-DataSync-MySQL-create_aq.sql		-- Create AQ tables.
4.DTL-DataSync-MySQL-enq_proc.sql		-- Create enqueue routines.
5.DTL-DataSync-MySQL-deq_proc.sql		-- Create dequeue routines.
6.DTL-DataSync-MySQL-Recipient.sql		-- Setup Recipient information.


========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name]
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ
3. type below command and Enter:
source DTL-DataSync-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




