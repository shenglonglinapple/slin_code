tee LOG-DTL-DataSync-04-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-04-MySQL-REC-Table.sql
source DTL-DataSync-04-MySQL-Create-AQ.sql
source DTL-DataSync-04-MySQL-Enq-Update.sql
source DTL-DataSync-04-MySQL-Deq-Update.sql

insert into patch_log values ('DTL-DataSync-04-MySQL',sysdate());

commit;

notee;


