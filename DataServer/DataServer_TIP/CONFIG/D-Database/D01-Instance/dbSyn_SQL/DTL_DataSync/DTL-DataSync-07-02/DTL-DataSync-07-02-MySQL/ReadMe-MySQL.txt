/*=====================================================
Version: DTL-DataSync-07-02-MySQL
-----------

number of scripts: 4
scripts name:
1.DTL-DataSync-07-02-MySQL-Main.sql		-- Main script to call other script(s).
2.DTL-DataSync-07-02-MySQL-trg.sql		-- Drop triggers on adm_sequence, create new triggers on adm_sequence_rep. 
3.DTL-DataSync-07-02-MySQL-prc_create_queue.sql	-- Replace procedure prc_create_queue.
4.DTL-DataSync-07-02-MySQL-prc_drop_queue.sql	-- Replace procedure prc_drop_queue.

========================================================*/

/*===Notes===
1. How to check status (ReadWrite or ReadOnly) of MySQL database:
mysql> select @@read_only;
0--ReadWrite 1--ReadOnly

2. '--comments' is a connection parameter too, please do not ignore it.
===========*/

/*=====================================================
Installation Steps
------------
1. cd to the folder containing these patches 
2. Login MySQL 'ReadWrite' db by the application user of the database. Just only choose one node (any node) to apply if the both nodes are  'ReadWrite'.
mysql --comments -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-01 -uIT271350_5 -pIT271350_5 -Dtra_occ 
3. type below command and Enter:
source DTL-DataSync-07-02-MySQL-Main.sql
4. Login MySQL 'ReadOnly' db of Failover Envrionment by the application user of the database. If it's single-node environment or both nodes are 'ReadWrite', please ignore step 4.
mysql --comments -h[DBserver_hostname] -u[user] -p[passwd] -D[DB_Name] 
e.g.: mysql --comments -hocc-cms-02 -uIT271350_5 -pIT271350_5 -Dtra_occ 
5. type below command and enter:
drop trigger if exists adm_seq_air_trg;
drop trigger if exists adm_seq_adr_trg;

Verification Steps
-------------------
1. check the log to ensure there is no 'ERROR' error. Please clean the log first if re-patch it.
========================================================*/





