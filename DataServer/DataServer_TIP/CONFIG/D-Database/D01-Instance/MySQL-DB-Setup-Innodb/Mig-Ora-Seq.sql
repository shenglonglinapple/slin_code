set pagesize 5000
set heading off
set linesize 1000
set feedback off
spool Mig-MySQL-Seq.sql

select 'insert into adm_sequence values ('||rownum||','||''''||t.sequence_name||''','||t.min_value||','||t.last_number||','
 ||t.max_value||','||t.increment_by||','''||t.cycle_flag||''');' from
 (select sequence_name,min_value,last_number,max_value,increment_by,cycle_flag
  from user_sequences where sequence_name not like 'AQ$_%'order by sequence_name) t;

spool off;