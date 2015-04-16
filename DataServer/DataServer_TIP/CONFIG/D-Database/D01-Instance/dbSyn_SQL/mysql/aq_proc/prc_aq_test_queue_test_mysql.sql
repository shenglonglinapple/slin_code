DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_aq_test_queue_test_mysql` $$
CREATE PROCEDURE `prc_aq_test_queue_test_mysql`(
 in p_location varchar(30),
 in p_type varchar(30),
 in p_id_begin int,
 in p_id_end   int,
 in p_remark1 varchar(1024)
 )
begin

 declare lv_sql_oracle varchar(4000);
 declare lv_sql_mysql varchar(4000);
 declare i int default p_id_begin;

  while i>=p_id_begin and i<=p_id_end do
   begin

     set lv_sql_oracle = concat('insert into queue_test_mysql(ID, NAME, TIMESTAMP) values (', i, ',','''', p_remark1, '''', ',', 'sysdate)');
     set lv_sql_mysql = concat('insert into queue_test_mysql(ID, NAME, TIMESTAMP) values (', i, ',','''', p_remark1, '''', ',', 'sysdate())');

     CALL prc_enqueue_audit_data(p_location, p_type, lv_sql_oracle, lv_sql_mysql);

    set i=i+1;
   end;
  end while;

end $$

DELIMITER ;