tee LOG-DTL-DataSync-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-MySQL-Recipient.sql
source DTL-DataSync-MySQL-prepare.sql
source DTL-DataSync-MySQL-create_aq.sql
source DTL-DataSync-MySQL-enq_proc.sql
source DTL-DataSync-MySQL-deq_proc.sql

insert into patch_log values ('DTL-DataSync-MySQL-Main',sysdate());

show warnings;

commit;

notee;
