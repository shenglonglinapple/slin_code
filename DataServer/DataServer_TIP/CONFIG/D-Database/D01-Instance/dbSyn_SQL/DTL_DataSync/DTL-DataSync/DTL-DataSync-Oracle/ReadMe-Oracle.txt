/*=====================================================
Version: DTL-DataSync-Oracle
-----------

number of scripts: 4
scripts name:
1.DTL-DataSync-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-enq_proc_orc.sql		-- Re-create AQ package.
3.DTL-DataSync-Oracle_alter_var1.sql	-- Disable system jobs.
4.DTL-DataSync-Oracle_alter_var2.sql	-- Enable system jobs.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db(Central DB) as sysdba. e.g.:sqlplus "sys/sys@transact as sysdba"
3. type @DTL-DataSync-Oracle_alter_var1.sql
4. Restart Database
   e.g.
   sqlplus "sys/sys@transact as sysdba"
     shutdown immediate;
     startup;
     quit;
5. sqlplus to login Oracle db(Central DB). e.g.:sqlplus it271350_2/it271350_2@transact
6. type @DTL-DataSync-Oracle-Main.sql
7. sqlplus to login Oracle db(Central DB) as sysdba. e.g.:sqlplus "sys/sys@transact as sysdba"
8. type @DTL-DataSync-Oracle_alter_var2.sql


Verification Steps
-------------------
1. check the log to ensure there is no ora- error.

========================================================*/




