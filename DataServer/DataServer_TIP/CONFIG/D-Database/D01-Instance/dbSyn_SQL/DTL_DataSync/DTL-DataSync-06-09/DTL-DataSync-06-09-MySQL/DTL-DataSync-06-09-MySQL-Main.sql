tee LOG-DTL-DataSync-06-09-MySQL-Main.txt
set autocommit=off;
set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES');

source DTL-DataSync-06-09-MySQL-Drop-Trg.sql
source DTL-DataSync-06-09-MySQL-AnalyzeJob.sql

insert into patch_log values ('DTL-DataSync-06-09-MySQL', sysdate());

commit;

notee;