tee LOG-DTL-DataSync-05-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-05-MySQL-Enq.sql
source DTL-DataSync-05-MySQL-Deq.sql

insert into patch_log values ('DTL-DataSync-05-MySQL',sysdate());

commit;

notee;


