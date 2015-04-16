spool LOG-DTL-DataSync-06-03-Oracle-Main.txt

@@DTL-DataSync-06-03-Oracle-Type-Queue.sql
@@DTL-DataSync-06-03-Oracle-Sequence.sql
@@DTL-DataSync-06-03-Oracle-AQ-PKG.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-03-Oracle', sysdate);

commit;

spool off;
quit;