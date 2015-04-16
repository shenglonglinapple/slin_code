spool LOG-DTL-DataSync-06-05-Oracle.txt

@@DTL-DataSync-06-05-Oracle-Tab.sql

insert into patch_log values ('DTL-DataSync-06-05-Oracle', sysdate);

commit;

spool off;
quit;