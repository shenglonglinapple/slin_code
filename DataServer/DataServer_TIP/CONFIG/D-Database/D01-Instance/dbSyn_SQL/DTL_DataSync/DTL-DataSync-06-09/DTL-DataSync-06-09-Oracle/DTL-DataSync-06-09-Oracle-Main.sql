spool LOG-DTL-DataSync-06-09-Oracle-Main.txt

@@DTL-DataSync-06-09-Oracle-Trg-EnqMode.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-09-Oracle', sysdate);

commit;

spool off;
quit;