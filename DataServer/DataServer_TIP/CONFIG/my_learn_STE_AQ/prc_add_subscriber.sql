DELIMITER $$
DROP PROCEDURE IF EXISTS `prc_add_subscriber` $$
CREATE PROCEDURE `prc_add_subscriber`
(
	IN p_queue_name      VARCHAR(50),
	IN p_sub_name        VARCHAR(80),
	IN p_sub_addr        VARCHAR(128) )
PRC_LABEL: BEGIN
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_stable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_delim_char         VARCHAR(2) DEFAULT '@';
	DECLARE v_delim_pos          INT(5) DEFAULT 0;
	DECLARE v_sub_cnt            INT(5) DEFAULT 0;
	DECLARE v_queue_name         VARCHAR(50) DEFAULT UPPER(p_queue_name);
	DECLARE v_sub_name           VARCHAR(50) DEFAULT UPPER(p_sub_name);

	DECLARE c_sub_cnt CURSOR FOR
	SELECT SUB_COUNT FROM aq_sys_queue_m WHERE Q_NAME = v_queue_name;

	DECLARE EXIT HANDLER FOR SQLEXCEPTION	
		ROLLBACK;	
	
	IF p_queue_name IS NULL OR CHAR_LENGTH(p_queue_name) = 0 THEN
		LEAVE PRC_LABEL;
	END IF;
	
	SET v_stable = CONCAT('aq_', p_queue_name, '_t_s');
	
	IF 	p_sub_name IS NULL AND p_sub_addr IS NULL THEN
		LEAVE PRC_LABEL;
	END IF;
	
	IF CHAR_LENGTH(p_sub_name) <> 0 OR CHAR_LENGTH(p_sub_addr) <> 0 THEN
		IF p_sub_addr IS NOT NULL AND CHAR_LENGTH(p_sub_addr) <> 0 THEN
			SET v_delim_pos = INSTR(p_sub_addr, v_delim_char);
			IF v_delim_pos < 2 THEN
				LEAVE PRC_LABEL ;
			END IF;
		END IF;
		
		OPEN c_sub_cnt;
		FETCH c_sub_cnt INTO v_sub_cnt;
		CLOSE c_sub_cnt;
		SET v_sub_cnt = v_sub_cnt + 1;
		
		IF p_sub_addr = '' OR p_sub_addr IS NULL THEN
			SET @g_sql = CONCAT('INSERT INTO ', v_stable, '(Q_NAME, SUB_NAME, SUB_ADDRESS) VALUES (',
						'''',v_queue_name, '''', ',', '''',v_sub_name, '''', ',', 'NULL', ')');
		ELSE
			SET @g_sql = CONCAT('INSERT INTO ', v_stable, '(Q_NAME, SUB_NAME, SUB_ADDRESS) VALUES (',
						'''',v_queue_name, '''', ',', '''',v_sub_name, '''', ',', '''',p_sub_addr, '''', ')');
		END IF;
		
	START TRANSACTION;
		UPDATE aq_sys_queue_m SET SUB_COUNT = v_sub_cnt WHERE Q_NAME = v_queue_name;
		
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;						
	COMMIT;

	END IF;

END $$

DELIMITER ;