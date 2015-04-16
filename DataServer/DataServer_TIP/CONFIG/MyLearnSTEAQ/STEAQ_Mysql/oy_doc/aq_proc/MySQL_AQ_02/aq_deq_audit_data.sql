DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dequeue_audit_data` $$
CREATE PROCEDURE `prc_dequeue_audit_data`(
	IN   p_location         VARCHAR(50)
)
BEGIN
	
	DECLARE  v_no_more_rows        BOOLEAN  DEFAULT FALSE;
	DECLARE  v_msgid               VARCHAR(40) DEFAULT NULL;
	DECLARE  v_deq_msg             VARCHAR(8080) DEFAULT NULL;
	DECLARE  v_queue         VARCHAR(80) DEFAULT 'audit_data_queue';
	DECLARE  v_queue_table   VARCHAR(80) DEFAULT CONCAT(v_queue,'_t');
	DECLARE  v_deq_options         TINYINT(1) DEFAULT 1;
	declare v_dis_table VARCHAR(80) DEFAULT CONCAT('aq_', v_queue, '_t_i');
	
	DECLARE  v_deq_delay_time      INT(10) DEFAULT 0;
    
	DECLARE v_locate_notnum INT(11) default 0;
	DECLARE v_len INT(11) default 0;
	DECLARE v_attribute_name varchar(50) default null;
	DECLARE v_locate_deli	INT(11) default 0;
	DECLARE v_sql	varchar(4000) default null;
	
	DECLARE i INT(5) default 1;
  DECLARE v_db_name varchar(100) default upper(database());


	DECLARE cu_deq_data  CURSOR FOR
	SELECT MSGID, USER_DATA FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 ORDER BY msg_sid ASC LIMIT 20000;

	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;
		
	DECLARE CONTINUE HANDLER FOR 1062 begin end;

 IF trim(v_db_name) = trim(upper(p_location)) then

 start transaction;
	OPEN cu_deq_data;
	the_deq_msg_loop: LOOP
		FETCH cu_deq_data INTO v_msgid, v_deq_msg;
		
		
		
		IF v_no_more_rows THEN
			CLOSE cu_deq_data;
			LEAVE the_deq_msg_loop;
		END IF;
		
		
	  loop2: while i >= 1 and i <= 5 do
		  set v_locate_notnum = func_locate_isnotnum(v_deq_msg);
		  set v_len = substr(v_deq_msg,1,v_locate_notnum-1);
		  set v_locate_deli = instr(v_deq_msg,'=');
		  set v_attribute_name = substr(v_deq_msg,v_locate_notnum,v_locate_deli-v_locate_notnum);
		
		  if v_attribute_name = 'AUDIT_DATA_MYSQL' then
		  	set v_sql = substr(v_deq_msg,v_locate_deli+1,v_len);
		  	leave loop2;
		  else
		  	set v_deq_msg = substr(v_deq_msg,v_locate_deli+v_len+1);
		  end if;
    end while;


     # CALL prc_dequeue(v_queue, v_msgid, null, null, null, v_deq_options, v_deq_delay_time, 0, null);
	 	set @g_sql = v_sql;
      	PREPARE stmt FROM @g_sql;
      	EXECUTE stmt;
      	DEALLOCATE PREPARE stmt;
        SET @g_sql = NULL;
		
	END LOOP the_deq_msg_loop;
/*
  if v_deq_options = 3 then
 	  call prc_dequeue_delay(v_queue_table, v_enq_table, v_deq_delay_time);
  end if;
*/
 DELETE FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 ORDER BY msg_sid ASC LIMIT 20000;
 
 COMMIT;
 END IF;

END $$

DELIMITER ;