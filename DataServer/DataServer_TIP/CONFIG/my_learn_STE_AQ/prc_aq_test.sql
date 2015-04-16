DELIMITER $$

DROP PROCEDURE IF EXISTS `tra_occ`.`prc_aq_test`$$
CREATE DEFINER=`IT271350_5`@`%` PROCEDURE  `tra_occ`.`prc_aq_test`(
 in p_location varchar(30),
 in p_type varchar(30),
 in p_id_begin int,
 in p_id_end int,
 in p_remark1 varchar(64),
 in p_remark2 varchar(500),
 in p_wait_time float
)
begin

 declare lv_sql_oracle varchar(4000);
 declare lv_sql_mysql varchar(4000);
 declare lv_mark_pkg varchar(256);
 declare i int default p_id_begin;
 declare lv_dl tinyint(1) default 0;

  while i>=p_id_begin and i<=p_id_end do
   begin
    if (p_remark1 <> '' and p_remark2 <> '') then
      set lv_sql_oracle = concat('insert into queue_test(id,location,intime,remark1,remark2) values (',i,',''',p_location,''',systimestamp,','''',p_remark1,''',''',p_remark2,''')');
      set lv_sql_mysql = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',sysdate(),','''',p_remark1,''',''',p_remark2,''')');
    elseif (p_remark1 is null or p_remark1 ='') and (p_remark2 is null or p_remark2 ='') then
      set lv_sql_oracle = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',systimestamp,null,null)');
      set lv_sql_mysql = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',sysdate(),null,null)');
    elseif (p_remark1 is null or p_remark1 ='') and (p_remark2<>'') then
      set lv_sql_oracle = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',systimestamp,null,''',p_remark2,''')');
      set lv_sql_mysql = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',sysdate(),null,''',p_remark2,''')');
    elseif (p_remark2 is null or p_remark2 ='') and (p_remark1<>'') then
      set lv_sql_oracle = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',systimestamp,','''',p_remark1,''',null)');
      set lv_sql_mysql = concat('insert into queue_test(id,location,intime,remark1,remark2)  values (',i,',''',p_location,''',sysdate(),','''',p_remark1,''',null)');
    end if;

  set lv_dl = 0;
  begin
   	DECLARE continue HANDLER FOR SQLSTATE '40001'
          set lv_dl = 1;
   	DECLARE continue HANDLER FOR SQLSTATE 'XA102'
          set lv_dl = 1;

     CALL prc_enqueue_audit_data(p_location,p_type,lv_sql_oracle,lv_sql_mysql);
     
  end;
    
    if mod(i,10000)=0 then
      set lv_mark_pkg = concat(p_location, '_', p_type, '_', p_id_begin, '_', p_id_end);
      INSERT INTO error_log(pkey,sql_statement,error_message,timestamp) VALUES (func_seq_get_next_number('ERRLOG_SEQ'), lv_mark_pkg, i, now());
      select sleep(1) into @sleep;
    end if;

  if lv_dl = 0 then
    
    set i=i+1;
  end if;

    select sleep(p_wait_time) into @sleep;

   end;
  end while;

end $$

DELIMITER ;