tee LOG-DTL-DataSync-06-06-MySQL-Main.txt
set autocommit=off;

source DTL-DataSync-06-06-MySQL-prc_enq_tab.sql

insert into patch_log values ('DTL-DataSync-06-06-MySQL', sysdate());

commit;

notee;