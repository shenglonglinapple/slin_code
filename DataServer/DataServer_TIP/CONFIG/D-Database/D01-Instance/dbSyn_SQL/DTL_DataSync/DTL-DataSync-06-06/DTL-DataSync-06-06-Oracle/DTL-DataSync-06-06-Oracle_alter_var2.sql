alter system set job_queue_processes = 20 scope = both;

alter system set aq_tm_processes = 6 scope = both;

commit;
quit;