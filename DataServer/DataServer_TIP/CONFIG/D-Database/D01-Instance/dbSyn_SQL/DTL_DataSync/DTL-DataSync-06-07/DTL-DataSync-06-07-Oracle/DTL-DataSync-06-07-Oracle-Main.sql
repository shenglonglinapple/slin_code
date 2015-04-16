spool LOG-DTL-DataSync-06-07-Oracle-Main.txt

@@DTL-DataSync-06-07-Oracle-AQ-Check.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-07-Oracle', sysdate);

commit;

spool off;
quit;