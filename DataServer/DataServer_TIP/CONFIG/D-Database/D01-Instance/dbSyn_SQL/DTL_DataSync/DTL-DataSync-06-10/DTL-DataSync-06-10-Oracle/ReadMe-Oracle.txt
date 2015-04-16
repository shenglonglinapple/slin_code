/*=====================================================
Version: DTL-DataSync-06-10-Oracle
-----------

number of scripts: 4
scripts name:
1.DTL-DataSync-06-10-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-10-Oracle-prc_log_errors.sql	-- Create autonomous transaction procedure to log errors.
3.DTL-DataSync-06-10-Oracle-prc_enq_audit_data.sql	-- Use prc_log_errors.
4.TACOMP.SQL					-- Compile invalid objects.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db. e.g.:sqlplus it271350_5/it271350_5@transact
3. type @DTL-DataSync-06-10-Oracle-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no ora- error.
2. Run below SQL to check the values, the all of returned 'value' should be '1':
sql> select decode(status,'VALID',1,0) value from user_objects where object_name in ('PRC_ENQ_AUDIT_DATA','PRC_LOG_ERRORS');
sql> select decode(count(*),2,1,0) value from user_objects where object_name in ('PRC_ENQ_AUDIT_DATA','PRC_LOG_ERRORS');
========================================================*/





