/*=====================================================
Version: DTL-DataSync-06-Oracle
Note: Please config the recipient tables after apply this DB patch according by the AQ document or asking DBA's assistance.
-----------

number of scripts: 7
scripts name:
1.DTL-DataSync-06-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-Oracle-AQ-PKG.sql		-- Recreate package 'audit_data_queue_pkg' to support MMS Enq and Deq.
3.DTL-DataSync-06-Oracle-REC-Tabs.sql		-- Recreate recipient tables.
4.DTL-DataSync-06-Oracle-Create-MMS-AQ.sql	-- Create MMS AQ and dequeue job.
5.DTL-DataSync-06-Oracle_alter_var1.sql		-- Disable system jobs.
6.DTL-DataSync-06-Oracle_alter_var2.sql		-- Enable system jobs.
7.TACOMP.SQL					-- Compile invalid objects.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db(Central DB) as sysdba. e.g.:sqlplus "sys/sys@transact as sysdba"
3. type @DTL-DataSync-06-Oracle_alter_var1.sql
4. Restart Database
   e.g.
   sqlplus "sys/sys@transact as sysdba"
     shutdown immediate;
     startup;
     quit;
5. sqlplus to login Oracle db(Central DB). e.g.:sqlplus it271350_2/it271350_2@transact
6. type @DTL-DataSync-06-Oracle-Main.sql
7. sqlplus to login Oracle db(Central DB) as sysdba. e.g.:sqlplus "sys/sys@transact as sysdba"
8. type @DTL-DataSync-06-Oracle_alter_var2.sql



Verification Steps
-------------------
1. check the log to ensure there is no ora- error.

========================================================*/




