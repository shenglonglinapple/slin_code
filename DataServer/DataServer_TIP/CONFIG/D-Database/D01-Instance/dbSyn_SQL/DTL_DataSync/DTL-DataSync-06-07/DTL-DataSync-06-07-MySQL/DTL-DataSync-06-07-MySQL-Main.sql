tee LOG-DTL-DataSync-06-07-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-06-07-MySQL-AQ-Check.sql

insert into patch_log values ('DTL-DataSync-06-07-MySQL', sysdate());

commit;

notee;