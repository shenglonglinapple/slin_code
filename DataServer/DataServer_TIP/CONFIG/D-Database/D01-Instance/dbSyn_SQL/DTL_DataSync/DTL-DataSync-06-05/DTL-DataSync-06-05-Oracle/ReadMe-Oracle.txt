/*=====================================================
Version: DTL-DataSync-06-05-Oracle
-----------

number of SQL scripts: 3
scripts name:
1.DTL-DataSync-06-05-Oracle-Main.sql	-- Main script to call other script(s).
2.DTL-DataSync-06-05-Oracle-Tab.sql	-- Create AQ check tables.
3.TACOMP.SQL				-- Comile invalid objects.

========================================================*/

/*=====================================================
Installation Steps
------------
note: Please stop all agent services before apply DB patch.

For SQL scripts:
1. cd to the folder containing these patches 
2. sqlplus to login Oracle db(Central DB). e.g.:sqlplus it271350_2/it271350_2@transact
3. type @DTL-DataSync-06-05-Oracle-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no ora- error.
2. Run below SQL to check the values, the all of returned values should be '1':
select decode(count(*),2,1,0) value from user_tables where table_name in ('AQ_DEQ_TOKEN_CHECK','AQ_ENQ_DUPLICATE_CHECK');
========================================================*/




