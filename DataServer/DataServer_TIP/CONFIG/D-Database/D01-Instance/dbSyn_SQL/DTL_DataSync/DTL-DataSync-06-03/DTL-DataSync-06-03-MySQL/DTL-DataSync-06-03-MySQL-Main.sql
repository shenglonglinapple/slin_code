tee LOG-DTL-DataSync-06-03-Mysql-Main.txt
set autocommit=off;

source DTL-DataSync-06-03-MySQL-AQ-Man.sql
source DTL-DataSync-06-03-MySQL-Recreate-AQ.sql
source DTL-DataSync-06-03-MySQL-Enq.sql
source DTL-DataSync-06-03-MySQL-prc_deq.sql
source DTL-DataSync-06-03-enq_audit_data.sql
source DTL-DataSync-06-03-deq_audit_data.sql
source DTL-DataSync-06-03-MySQL-SeqMerge.sql

insert into patch_log values ('DTL-DataSync-06-03-MySQL', sysdate());

commit;

notee;