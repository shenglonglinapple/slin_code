tee LOG-DTL-DataSync-06-11-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-06-11-MySQL-prc_enqueue.sql
source DTL-DataSync-06-11-MySQL-prc_enqueue_notrans.sql

insert into patch_log values ('DTL-DataSync-06-11-MySQL', sysdate());

commit;

notee;