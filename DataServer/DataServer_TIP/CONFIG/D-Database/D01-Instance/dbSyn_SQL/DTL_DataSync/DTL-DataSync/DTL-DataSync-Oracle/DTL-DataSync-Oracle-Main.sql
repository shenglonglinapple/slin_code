spool LOG-DTL-DataSync-Oracle-Main.txt

@DTL-DataSync-enq_proc_orc.sql

insert into patch_log values ('DTL-DataSync-Oracle-Main',sysdate);

commit;

spool off;
quit;

