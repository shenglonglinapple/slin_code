tee LOG-DTL-DataSync-06-04-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-06-04-MySQL-Func-Seq.sql

insert into patch_log values ('DTL-DataSync-06-04-MySQL', sysdate());

commit;

notee;