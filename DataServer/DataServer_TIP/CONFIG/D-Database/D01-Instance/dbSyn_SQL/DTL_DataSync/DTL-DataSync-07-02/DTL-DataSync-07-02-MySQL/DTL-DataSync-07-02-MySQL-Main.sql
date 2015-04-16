tee LOG-DTL-DataSync-07-02-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-07-02-MySQL-trg.sql
source DTL-DataSync-07-02-MySQL-prc_create_queue.sql
source DTL-DataSync-07-02-MySQL-prc_drop_queue.sql


insert into patch_log values ('DTL-DataSync-07-02-MySQL', sysdate());

commit;

notee;