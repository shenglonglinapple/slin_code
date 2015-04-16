tee LOG-DTL-DataSync-06-Mysql-Main.txt
set autocommit=off;

source DTL-DataSync-06-1Remove.sql
source DTL-DataSync-06-aq_rec_tabs.sql
source DTL-DataSync-06-2SysTabs.sql
source DTL-DataSync-06-3func_isnotnum.sql
source DTL-DataSync-06-4enq_prc.sql
source DTL-DataSync-06-5deq_prc.sql
source DTL-DataSync-06-6enq_audit_data.sql
source DTL-DataSync-06-7deq_audit_data.sql
source DTL-DataSync-06-8aq_api_commit.sql
source DTL-DataSync-06-9man_procs.sql
source DTL-DataSync-06-10Create-Queue.sql
source DTL-DataSync-06-11aq_trg.sql

insert into patch_log values ('DTL-DataSync-06-MySQL', sysdate());

commit;

notee;