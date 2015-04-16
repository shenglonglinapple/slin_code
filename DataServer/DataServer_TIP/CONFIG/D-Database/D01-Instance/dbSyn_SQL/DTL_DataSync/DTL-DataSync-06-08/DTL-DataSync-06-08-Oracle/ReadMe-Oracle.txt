/*=====================================================
Version: DTL-DataSync-06-08-Oracle
-----------

number of scripts: 3
scripts name:
1.DTL-DataSync-06-08-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-08-Oracle-Tab.sql		-- Create table AQ_SYS_QUEUE_M.
3.DTL-DataSync-06-08-Oracle-Prc.sql		-- Create procedure prc_enq_audit_data.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db. e.g.:sqlplus it271350_2/it271350_2@transact
3. type @DTL-DataSync-06-08-Oracle-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no ora- error.
2. Run below SQL to check the values, the all of returned 'value' should be '1':
sql> select decode(count(*),2,1,0) value from aq_sys_queue_m where q_name in ('AUDIT_DATA_QUEUE','MMS_DATA_QUEUE') and enq_mode=2;
sql> select decode(status,'VALID',1,0) value from user_objects where object_name='PRC_ENQ_AUDIT_DATA';
========================================================*/





