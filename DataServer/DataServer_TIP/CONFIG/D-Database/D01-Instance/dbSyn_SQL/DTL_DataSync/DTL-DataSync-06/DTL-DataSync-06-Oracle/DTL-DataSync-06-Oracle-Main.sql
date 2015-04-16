spool LOG-DTL-DataSync-06-Oracle-Main.txt

@@DTL-DataSync-06-Oracle-REC-Tabs.sql
@@DTL-DataSync-06-Oracle-AQ-PKG.sql
@@DTL-DataSync-06-Oracle-Create-MMS-AQ.sql
@@TACOMP.SQL

insert into patch_log values ('DTL-DataSync-06-Oracle', sysdate);

commit;

spool off;
quit;