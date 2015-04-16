/*=====================================================
Version: DTL-DataSync-06-07-Oracle
-----------

number of scripts: 3
scripts name:
1.DTL-DataSync-06-07-Oracle-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-07-Oracle-AQ-Check.sql	-- Create sequences, unique constraints and triggers for AQ check. 
3.TACOMP.SQL					-- Compile invalid objects.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db(Central DB). e.g.:sqlplus it271350_2/it271350_2@transact
3. type @DTL-DataSync-06-07-Oracle-Main.sql


Verification Steps
-------------------
1. check the log to ensure there is no ora- error.
2. Run below SQL to check the values, the all of returned 'value' should be '1':
sql> select decode(count(*),4,1,0) value from user_objects where object_name in ('AQ_ENQ_DUP_CHECK_SEQ','AQ_DEQ_TOKEN_CHECK_SEQ','AQ_DEQ_TOKEN_CHECK_BIR_TRG','AQ_ENQ_DUPLICATE_CHECK_BIR_TRG');
sql> select decode(status,'VALID',1,0) value from user_objects where object_name in ('AQ_ENQ_DUP_CHECK_SEQ','AQ_DEQ_TOKEN_CHECK_SEQ','AQ_DEQ_TOKEN_CHECK_BIR_TRG','AQ_ENQ_DUPLICATE_CHECK_BIR_TRG');
sql> select decode(count(*),2,1,0) value from user_constraints where constraint_name in ('AQ_DEQ_TOKEN_CHECK_U01','AQ_ENQ_DUPLICATE_CHECK_U01');
========================================================*/





