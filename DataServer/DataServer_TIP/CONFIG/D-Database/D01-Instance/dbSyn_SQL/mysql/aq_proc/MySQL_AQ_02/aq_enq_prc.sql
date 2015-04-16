DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enq_table` $$
CREATE PROCEDURE `prc_enq_table`(
	IN p_queue              VARCHAR(80),
	IN p_msgid              VARCHAR(38),
	IN p_rec_name           VARCHAR(80),
	IN p_rec_addr           VARCHAR(128),
	IN p_sid                BIGINT(20) UNSIGNED )
BEGIN
	DECLARE v_sub_id            INT(5) DEFAULT 0;
	DECLARE v_sub_cnt           INT(9) DEFAULT 0;
	DECLARE v_sub_table         VARCHAR(50) DEFAULT NULL;
	DECLARE v_dis_table         VARCHAR(50) DEFAULT NULL;
	DECLARE v_rec_name          VARCHAR(80) DEFAULT NULL;
	DECLARE v_rec_addr          VARCHAR(128) DEFAULT NULL;
	
	DECLARE c_sub_cnt  CURSOR FOR
	SELECT SUB_COUNT FROM aq_sys_queue_m WHERE Q_NAME = p_queue;
	
	SET v_sub_table = CONCAT('AQ_', p_queue, '_T_S');
	SET v_dis_table = CONCAT('AQ_', p_queue, '_T_I');
	SET v_rec_name  = UPPER(p_rec_name);
	SET v_rec_addr  = TRIM(p_rec_addr);

	SET @sv_sub_id = NULL;
--	IF CHAR_LENGTH(v_rec_addr) > 1 THEN
	IF CHAR_LENGTH(v_rec_addr) > 0 THEN
		SET @g_sql = CONCAT('SELECT SUB_ID INTO @sv_sub_id FROM ', v_sub_table, ' WHERE SUB_ADDRESS = ', '''',p_rec_addr,'''');
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
		SET @g_sql = NULL;
		
		IF @sv_sub_id IS NULL THEN
		
				SET @g_sql = CONCAT('SELECT ifnull(max(sub_id),0)+1 INTO @sv_sub_id FROM ', v_sub_table);
				PREPARE stmt FROM @g_sql;
				EXECUTE stmt;
				DEALLOCATE PREPARE stmt;
				SET @g_sql = NULL;
				
			SET @g_sql = CONCAT('INSERT INTO ',v_sub_table, '(SUB_ID, Q_NAME, SUB_NAME, SUB_ADDRESS) VALUES (',
								@sv_sub_id,',''',p_queue,'''',',','''',v_rec_name,'''',',','''',p_rec_addr,'''', ')');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
			SET @g_sql = NULL;
			SET v_sub_id = @sv_sub_id;
			
			OPEN c_sub_cnt;
			FETCH c_sub_cnt INTO v_sub_cnt;
			CLOSE c_sub_cnt;
			SET v_sub_cnt = v_sub_cnt + 1;
			UPDATE aq_sys_queue_m SET SUB_COUNT = v_sub_cnt WHERE Q_NAME = p_queue;
		ELSE
			SET v_sub_id = @sv_sub_id;			
		END IF;		
	END IF;
	IF v_sub_id <> 0 THEN
		SET @g_sql = CONCAT('INSERT INTO ',v_dis_table, '(SUB_ID,SUB_NAME,MSG_SID,MSGID,STATE) VALUES (',
							v_sub_id,',','''',0,'''',',','''',p_sid,'''',',','''',p_msgid,'''',',','1)');
	ELSE
		SET @g_sql = CONCAT('INSERT INTO ',v_dis_table, '(SUB_ID,SUB_NAME,MSG_SID,MSGID,STATE) VALUES (',
							v_sub_id,',','''',v_rec_name,'''',',','''',p_sid,'''',',','''',p_msgid,'''',',','1)');
	END IF;
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	SET @g_sql = NULL;
	
END $$

DROP PROCEDURE IF EXISTS `prc_enq_others` $$
CREATE PROCEDURE `prc_enq_others`(
	IN p_queue              VARCHAR(80),
	IN p_msgid              VARCHAR(38),
	IN p_sid                BIGINT(20) UNSIGNED,
	IN p_recipient          VARCHAR(4000) )
BEGIN
	DECLARE v_rec_name           VARCHAR(80) DEFAULT NULL;
	DECLARE v_rec_addr           VARCHAR(128) DEFAULT NULL;	
	DECLARE v_rec_nameaddr       VARCHAR(256) DEFAULT NULL;
	DECLARE v_recipient          VARCHAR(4000) DEFAULT NULL;
	DECLARE v_nameaddr_demli     VARCHAR(3) DEFAULT ',';
	DECLARE v_pairend_demli      VARCHAR(3) DEFAULT ';';
	DECLARE v_pairend_pos        INT(9) DEFAULT 0;
	DECLARE v_nameaddr_pos       INT(5) DEFAULT 0;
	
	SET v_recipient = p_recipient;
	the_parse_loop: LOOP
		SET v_rec_name = NULL;
		SET v_rec_addr = NULL;
		SET v_pairend_pos = INSTR(v_recipient, v_pairend_demli);	
		IF v_pairend_pos = 0 THEN
			LEAVE the_parse_loop;
		END IF;
		SET v_rec_nameaddr = LEFT(v_recipient, v_pairend_pos - 1);		
		SET v_recipient = SUBSTR(v_recipient, v_pairend_pos + 1);
		SET v_nameaddr_pos = INSTR(v_rec_nameaddr, v_nameaddr_demli);
		IF v_nameaddr_pos > 1 THEN
			SET v_rec_name = TRIM(LEFT(v_rec_nameaddr, v_nameaddr_pos - 1));
			SET v_rec_addr = TRIM(SUBSTR(v_rec_nameaddr, v_nameaddr_pos + 1));			
		END IF;
		IF (v_rec_name <> '') OR (v_rec_addr <> '') THEN
			CALL prc_enq_table(p_queue, p_msgid, v_rec_name, v_rec_addr, p_sid);
		END IF;
	END LOOP the_parse_loop;
--  The last one pair
	SET v_nameaddr_pos = INSTR(v_recipient, v_nameaddr_demli);

	IF v_nameaddr_pos > 1 THEN
	  if v_nameaddr_pos > 1 then
		SET v_rec_name = LEFT(v_recipient, v_nameaddr_pos - 1);
		SET v_rec_addr = SUBSTR(v_recipient, v_nameaddr_pos + 1);
	  elseif v_nameaddr_pos = 0 then
		SET v_rec_name = v_recipient;
	  end if;
		-- select concat('CALL prc_enq_table(',p_queue,',', p_msgid,',', v_rec_name,',', v_rec_addr,',', p_sid,');');
		CALL prc_enq_table(p_queue, p_msgid, v_rec_name, v_rec_addr, p_sid);
	END IF;

END $$
	

DROP PROCEDURE IF EXISTS `prc_enqueue` $$
CREATE PROCEDURE `prc_enqueue`(
	IN p_queue            VARCHAR(50),
	IN p_payload          VARCHAR(8080),
    IN p_msgid            VARCHAR(38),
    IN p_sub_cnt          TINYINT(1),
    IN p_recipient        VARCHAR(4000)	)
BEGIN
	DECLARE v_q_type			  TINYINT(1);	# 0:multi-comsumer; 1:single
	DECLARE v_enq_opt             TINYINT(1) DEFAULT 2;	 # 0: enable; 1: disable
	DECLARE v_sid                 BIGINT(20) DEFAULT 0;
	DECLARE v_priority     	  	  TINYINT(1) DEFAULT 1;
	DECLARE v_state        	  	  TINYINT(1) DEFAULT 1;  # 1: ready; 2: processing; 3: remove_delay 4: done
	DECLARE v_no_more_rows        BOOLEAN DEFAULT FALSE;
	DECLARE v_bWarn               BOOLEAN DEFAULT FALSE;
	DECLARE v_seq_name            VARCHAR(128) DEFAULT NULL;
	DECLARE v_queue_name          VARCHAR(50) DEFAULT UPPER(p_queue);
	DECLARE v_queue_tab           VARCHAR(55) DEFAULT NULL;
	DECLARE v_msgid               VARCHAR(38) DEFAULT NULL;
	DECLARE v_payload             VARCHAR(8080) DEFAULT NULL;
	DECLARE v_curuser_deli        VARCHAR(3) DEFAULT '@';


	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;
	DECLARE EXIT HANDLER FOR SQLSTATE '40001'
    BEGIN
		ROLLBACK;
		resignal;
    END;
	
	DECLARE EXIT HANDLER FOR SQLSTATE 'XA102'
    BEGIN
		ROLLBACK;
		resignal;
    END;

	DECLARE EXIT HANDLER FOR SQLSTATE '45001'
    BEGIN
		ROLLBACK;
		resignal;
    END;
	
	DECLARE EXIT HANDLER FOR SQLSTATE '45002'
    BEGIN
		ROLLBACK;
		resignal;
    END;
		
		DECLARE EXIT HANDLER FOR SQLSTATE '45003'
    BEGIN
		ROLLBACK;
		resignal;
    END;
	
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
      ROLLBACK;
      INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
      VALUES(func_seq_get_next_number('ERRLOG_SEQ'), concat(p_queue,'@',substr(p_payload,1,3500)),concat('Exception! SQLEXCEPTION of prc_enqueue at: ', DATABASE() ),SYSDATE());
    END;

	DECLARE CONTINUE HANDLER FOR SQLWARNING
		SET v_bWarn = TRUE;
	DECLARE CONTINUE HANDLER FOR 1062 BEGIN  END;
	
-- check enqueue option enable or not
	SELECT q_type, enq_state INTO v_q_type, v_enq_opt FROM aq_sys_queue_m WHERE q_name = v_queue_name;

	IF v_q_type = 1 and (p_recipient <> '' or p_sub_cnt <> 0) THEN
		SIGNAL SQLSTATE '45001'
			SET MESSAGE_TEXT = 'Single-consumer AQ doesn''t allow recipient and p_sub_cnt must be 0.';
	END IF;
	
	IF  p_sub_cnt = 1 and (p_recipient is null or p_recipient = '') THEN
		SIGNAL SQLSTATE '45002'
			SET MESSAGE_TEXT = 'The p_recipient can not be null if p_sub_cnt = 1.';
	END IF;

	IF p_sub_cnt = 0 and p_recipient <> '' and upper(p_recipient) <> upper(database()) THEN
		SIGNAL SQLSTATE '45003'
			SET MESSAGE_TEXT = 'It''s not my message.';
	END IF;
	
--  IF v_enq_opt = 0 and p_queue <> '' and p_recipient <> '' then
    IF v_enq_opt = 0 and p_queue <> '' then
      -- main function
      	SET v_msgid     = UUID();
      	SET v_seq_name  = CONCAT('AQ_', v_queue_name, '_SEQ');
      	SET v_queue_tab = CONCAT(v_queue_name, '_T');
      	SET v_payload   = REPLACE(p_payload, '''', '''''');

      START TRANSACTION;
      	SET v_sid = func_seq_get_next_number(v_seq_name);
      	-- IF p_sub_cnt <> 0 THEN
		-- IF p_sub_cnt <> 0 or (p_sub_cnt = 0 and p_recipient <> '') THEN
		IF p_sub_cnt <> 0 THEN
      		CALL prc_enq_others(v_queue_name, v_msgid, v_sid, p_recipient);
      	END IF;
      	
      	IF p_msgid = '' OR p_msgid IS NULL THEN
              SET @g_sql = CONCAT('INSERT INTO ', v_queue_tab, '(Q_NAME, MSG_SID, MSGID, PRIORITY, STATE, SUB_CNT, ENQ_TIME, ENQ_UID, SENDER_MSGID, USER_DATA) VALUES (',
      							'''', v_queue_name, '''', ',', v_sid, ',','''',v_msgid,'''' ,',', v_priority, ',', v_state,',', p_sub_cnt, ', sysdate(),SUBSTRING_INDEX(CURRENT_USER, ', '''',v_curuser_deli,'''', ',1),',
      							'NULL',',' ,'''', v_payload, '''',')');
          ELSE
      		SET @g_sql = CONCAT('INSERT INTO ', v_queue_tab, '(Q_NAME, MSG_SID, MSGID, PRIORITY, STATE, SUB_CNT, ENQ_TIME, ENQ_UID, SENDER_MSGID, USER_DATA) VALUES (',
      							'''', v_queue_name, '''', ',', v_sid, ',','''',v_msgid,'''' ,',', v_priority, ',', v_state,',', p_sub_cnt, ', sysdate(),SUBSTRING_INDEX(CURRENT_USER, ', '''',v_curuser_deli,'''', ',1),',
      							'''', p_msgid,'''',',' ,'''', v_payload, '''',')');
          END IF;
      
      	PREPARE stmt FROM @g_sql;
      	EXECUTE stmt;
      	DEALLOCATE PREPARE stmt;
          SET @g_sql = NULL;
      COMMIT;

  END IF;

END $$


DELIMITER ;