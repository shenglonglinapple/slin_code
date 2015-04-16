spool LOG-DTL-DataSync-06-10-Oracle-Main.log

@@DTL-DataSync-06-10-Oracle-prc_log_errors.sql
@@DTL-DataSync-06-10-Oracle-prc_enq_audit_data.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-10-Oracle', sysdate);

commit;

spool off;
quit;