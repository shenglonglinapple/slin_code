set autocommit=off;

source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\adm_sequence.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\error_log.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\patch_log.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\aq_sys_queue_e.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\aq_sys_queue_m.sql

source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\func_seq_get_next_number.sql


source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\prc_add_subscriber.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\prc_create_queue.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\prc_drop_queue.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\prc_start_queue.sql
source C:\LSL\SVNWork\slin_code\DataServer\DataServer_TIP\CONFIG\my_learn_STE_AQ\prc_stop_queue.sql


insert into patch_log values ('DTL-DataSync-05-MySQL',sysdate());



call prc_create_queue('audit_data_queue', 0, 0, 0);

commit;




