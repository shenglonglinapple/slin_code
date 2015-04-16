tee LOG-DTL-DataSync-07-03-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-07-03-MySQL-FlushJob.sql

insert into patch_log values ('DTL-DataSync-07-03-MySQL', sysdate());

commit;

notee;