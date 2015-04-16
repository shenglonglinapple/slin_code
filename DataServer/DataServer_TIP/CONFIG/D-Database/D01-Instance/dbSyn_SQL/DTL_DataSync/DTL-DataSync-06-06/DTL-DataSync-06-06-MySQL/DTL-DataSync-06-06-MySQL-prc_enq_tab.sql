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

	IF CHAR_LENGTH(v_rec_addr) > 0 THEN
		SET @g_sql = CONCAT('SELECT SUB_ID INTO @sv_sub_id FROM ', v_sub_table, ' WHERE upper(SUB_ADDRESS) = ', '''',upper(p_rec_addr),'''');
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
		SET @g_sql = NULL;
		
		IF @sv_sub_id IS NULL THEN
		
			SET @g_sql = CONCAT('SELECT SUB_ID INTO @sv_sub_id FROM ', v_sub_table, ' WHERE upper(Q_NAME) = ', '''',upper(p_queue),
			''' and upper(SUB_NAME) = ','''',v_rec_name,'''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
			SET @g_sql = NULL;	
				
				if @sv_sub_id is not null then
						SET @g_sql = CONCAT('UPDATE ', v_sub_table,' set SUB_ADDRESS = ','''',p_rec_addr,''' where SUB_ID = ',@sv_sub_id);
						PREPARE stmt FROM @g_sql;
						EXECUTE stmt;
						DEALLOCATE PREPARE stmt;
						SET @g_sql = NULL;
						-- SET v_sub_id = @sv_sub_id;						
					
				else
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
						-- SET v_sub_id = @sv_sub_id;
						
						OPEN c_sub_cnt;
						FETCH c_sub_cnt INTO v_sub_cnt;
						CLOSE c_sub_cnt;
						SET v_sub_cnt = v_sub_cnt + 1;
						UPDATE aq_sys_queue_m SET SUB_COUNT = v_sub_cnt WHERE Q_NAME = p_queue;
				end if;
		END IF;	
			SET v_sub_id = @sv_sub_id;		
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

DELIMITER ;