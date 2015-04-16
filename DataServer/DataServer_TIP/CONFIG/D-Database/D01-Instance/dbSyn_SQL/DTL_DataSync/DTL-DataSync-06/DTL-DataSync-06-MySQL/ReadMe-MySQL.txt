/*=====================================================
Version: DTL-DataSync-06-MySQL
Note: Please config the recipient tables after apply this DB patch according by the AQ document or asking DBA's assistance.

-----------

number of scripts: 
scripts name: 13
1.DTL-DataSync-06-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-1Remove.sql			-- Remove the old objects.
3.DTL-DataSync-06-2SysTabs.sql			-- Create AQ system tables.
4.DTL-DataSync-06-3func_isnotnum.sql		-- Create function isnotnum.
5.DTL-DataSync-06-4enq_prc.sql			-- Create enq procedures.
6.DTL-DataSync-06-5deq_prc.sql			-- Create deq procedures.
7.DTL-DataSync-06-6enq_audit_data.sql		-- Create enq app procedure.
8.DTL-DataSync-06-7deq_audit_data.sql		-- Create deq app procedure.
9.DTL-DataSync-06-8aq_api_commit.sql		-- Create AQ api procedure.
10.DTL-DataSync-06-9man_procs.sql		-- Create AQ manage procedure.
11.DTL-DataSync-06-10Create-Queue.sql		-- Create AQ.
12.DTL-DataSync-06-11aq_trg.sql			-- Create AQ triggers.
13.DTL-DataSync-06-aq_rec_tabs.sql		-- Re-create recipient tables.

========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db(Station DB) by the supper user as 'root' of the database. 
mysql -h[DBserver_hostname] -u[mysqlrootuser] -p[mysqlrootpasswd] -D[DB_Name]
e.g.: mysql -hocc-cms-01 -uroot -proot -Dtra_occ
3. type below command and Enter:
source DTL-DataSync-06-MySQL-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.

========================================================*/




