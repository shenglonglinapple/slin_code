tee LOG-DTL-DataSync-06-02-Mysql-Main.txt
set autocommit=off;

source DTL-DataSync-06-02-MySQL-enq_prc.sql
source DTL-DataSync-06-02-MySQL-enq_audit_data.sql

insert into patch_log values ('DTL-DataSync-06-02-MySQL', sysdate());

commit;

notee;