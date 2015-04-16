spool LOG-DTL-DataSync-06-06-Oracle-Main.txt

@@DTL-DataSync-06-06-Oracle-AQ-PKG.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-06-Oracle', sysdate);

commit;

spool off;
quit;