tee LOG-DTL-DataSync-06-05-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-06-05-MySQL-Tab.sql

insert into patch_log values ('DTL-DataSync-06-05-MySQL', sysdate());

commit;

notee;