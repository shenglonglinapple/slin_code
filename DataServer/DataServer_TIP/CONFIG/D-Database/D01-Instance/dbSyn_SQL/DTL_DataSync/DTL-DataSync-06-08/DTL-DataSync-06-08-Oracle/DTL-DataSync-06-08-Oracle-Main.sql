spool LOG-DTL-DataSync-06-08-Oracle-Main.txt

@@DTL-DataSync-06-08-Oracle-Tab.sql
@@DTL-DataSync-06-08-Oracle-Prc.sql

insert into patch_log values ('DTL-DataSync-06-08-Oracle', sysdate);

commit;

spool off;
quit;