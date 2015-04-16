spool LOG-DTL-DataSync-06-04-Oracle-Main.txt

@@DTL-DataSync-06-04-Oracle-AQ-PKG.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-04-Oracle', sysdate);

commit;

spool off;
quit;