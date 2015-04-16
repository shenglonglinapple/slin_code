tee LOG-DTL-DataSync-02-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-02-MySQL-Recipient.sql
source DTL-DataSync-02-MySQL-Recreate-AQ.sql
source DTL-DataSync-02-MySQL-Trg-Updated.sql
source DTL-DataSync-02-MySQL-Enq-Updated.sql
source DTL-DataSync-02-MySQL-Deq-Updated.sql

insert into patch_log values ('DTL-DataSync-02-MySQL-Main',sysdate());

show warnings;

commit;

notee;
