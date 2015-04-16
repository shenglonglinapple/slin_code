/*=====================================================
Version: DTL-DataSync-06-09-Oracle
-----------

number of scripts: 3
scripts name:
1.DTL-DataSync-06-09-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-09-Oracle-Trg-EnqMode.sql	-- Drop printable triggers and update the enq_mode of AQ_SYS_QUEUE_M.
3.TACOMP.SQL					-- Compile invalid objects.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db. e.g.:sqlplus it271350_2/it271350_2@transact
3. type @DTL-DataSync-06-09-Oracle-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no ora- error.
2. Run below SQL to check the values, the all of returned 'value' should be '1':
sql> select decode(count(*),0,1,0) value from user_triggers where trigger_name in ('ALARM_PRINTEVENT_TRG','EVCOM_PRINTEVENT_TRG');
sql> select decode(enq_mode,4,1,0) value from AQ_SYS_QUEUE_M;
========================================================*/





