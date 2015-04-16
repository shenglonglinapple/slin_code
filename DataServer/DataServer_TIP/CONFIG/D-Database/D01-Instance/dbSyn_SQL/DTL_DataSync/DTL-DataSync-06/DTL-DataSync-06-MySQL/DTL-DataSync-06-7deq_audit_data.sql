DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_deq_audit_data_queue` $$
CREATE PROCEDURE `prc_deq_audit_data_queue`(
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
	DECLARE v_min_sid BIGINT(20) default 0;
	DECLARE v_max_sid BIGINT(20) default 0;
	DECLARE v_msg_sid BIGINT(20) default 0;
	DECLARE gc_halt_dequeue_message VARCHAR(30) default 'HALT_DEQUEUE';
	DECLARE v_halt_dequeue_message VARCHAR(30) default null;	
	DECLARE v_sleep_foo INT;
	DECLARE i INT(5) default 1;
	DECLARE v_db_name varchar(100) default upper(database());	
	DECLARE	v_lock_min_sid BIGINT(20);
	declare v_deq_state TINYINT(1);
	
	DECLARE cu_deq_data  CURSOR FOR
	SELECT MSGID, MSG_SID, USER_DATA FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 and msg_sid between v_min_sid and v_max_sid ORDER BY msg_sid ASC;

	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;
		
	DECLARE CONTINUE HANDLER FOR 1062 begin end;
	
	DECLARE EXIT HANDLER FOR SQLSTATE '40001'
    BEGIN
		ROLLBACK;
		INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
			VALUES(func_seq_get_next_number('ERRLOG_SEQ'), concat(v_queue,'@msg_sid',ifnull(v_msg_sid,''),'of',ifnull(v_min_sid,''),'~',ifnull(v_max_sid,''),':',substr(ifnull(v_deq_msg,''),1,3500)),
				concat('ERROR 1213 (40001): Deadlock found of prc_deq_audit_data_queue at: ', DATABASE() ),SYSDATE());
		select sleep(2) into v_sleep_foo;
    END;
	
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
      ROLLBACK;
	  RESIGNAL;
	END;

 B1_Start: Begin
  select deq_state into v_deq_state from aq_sys_queue_m where upper(q_name) = upper(v_queue);
 IF 	v_deq_state = 1 then
		SIGNAL SQLSTATE '46001'
			SET MESSAGE_TEXT = 'The dequeue is disable.';
 ELSEIF v_deq_state = 0 then 
  IF trim(v_db_name) = trim(upper(p_location)) then
	

	SELECT MIN(t1.MSG_SID), MAX(t1.MSG_SID) into v_min_sid, v_max_sid 
		FROM (select msg_sid from audit_data_queue_t WHERE state = 1 and sub_cnt = 0 order by msg_sid ASC limit 5000) t1;
		
	Start transaction;  
	SELECT msg_sid into v_lock_min_sid from audit_data_queue_t where msg_sid=v_min_sid for update;
	
	set v_no_more_rows = FALSE;
	OPEN cu_deq_data;
	the_deq_msg_loop: LOOP

		FETCH cu_deq_data INTO v_msgid, v_msg_sid, v_deq_msg;				
		
		IF v_no_more_rows THEN
			CLOSE cu_deq_data;
			-- select sleep(2) as event_mon_only_for_audit_data_queue into v_sleep_foo;
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
		  elseif v_attribute_name = 'MESSAGE_QUALIFIER' then
			set v_halt_dequeue_message = substr(v_deq_msg,v_locate_deli+1,v_len);
			set v_deq_msg = substr(v_deq_msg,v_locate_deli+v_len+1);
		  else
		  	set v_deq_msg = substr(v_deq_msg,v_locate_deli+v_len+1);
		  end if;
		  
		  set i = i+1;
    end while;
	
	IF v_halt_dequeue_message = gc_halt_dequeue_message THEN
		DELETE FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 and msg_sid <= v_msg_sid;
		Leave B1_Start;
	END IF;

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
	DELETE FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 and msg_sid between v_min_sid and v_max_sid;
	COMMIT;

   END IF;
 END IF;  
 END;
 COMMIT;

END $$

DELIMITER ;