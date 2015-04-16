tee LOG-DTL-DataSync-06-10-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-06-10-MySQL-Enq-NoTrans.sql
source DTL-DataSync-06-10-MySQL-enq_audit_data.sql

insert into patch_log values ('DTL-DataSync-06-10-MySQL', sysdate());

commit;

notee;