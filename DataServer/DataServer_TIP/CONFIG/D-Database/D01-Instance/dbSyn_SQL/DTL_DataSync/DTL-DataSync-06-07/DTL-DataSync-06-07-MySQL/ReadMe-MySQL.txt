/*=====================================================
Version: DTL-DataSync-06-07-MySQL
-----------

number of scripts: 2
scripts name:
1.DTL-DataSync-06-07-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-06-07-MySQL-AQ-Check.sql		-- Create sequences, unique constraints and triggers for AQ check. 

========================================================*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL db by the application user of the database. 
mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments
e.g.: mysql -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ --comments
3. type below command and Enter:
source DTL-DataSync-06-07-MySQL-Main.sql

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
2. Run below SQL to check the values, the all of returned values should be '1':
# mysql -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] --comments

mysql> select if(count(*)=2,1,0) value from adm_sequence where name in ('AQ_ENQ_DUP_CHECK_SEQ','AQ_DEQ_TOKEN_CHECK_SEQ');
mysql> SELECT if(count(*)=2,1,0) value FROM information_schema.TRIGGERS T where trigger_name in ('aq_deq_token_check_bir_trg','aq_enq_duplicate_check_bir_trg') and trigger_schema=database();
mysql> SELECT if(count(*)=2,1,0) value FROM information_schema.TABLE_CONSTRAINTS T where constraint_name in ('AQ_DEQ_TOKEN_CHECK_U01','AQ_ENQ_DUPLICATE_CHECK_U01') and constraint_schema=database();

========================================================*/





