
DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_create_queue` $$
CREATE PROCEDURE `prc_create_queue`(
	IN p_queue_name      VARCHAR(50),
	IN p_qtype           TINYINT(1),
	IN p_payload_type    TINYINT(1),
	IN p_retention		 INT(11))
BEGIN
	DECLARE v_queue_table     VARCHAR(30) DEFAULT NULL;
	DECLARE v_i_table         VARCHAR(30) DEFAULT NULL;
	DECLARE v_s_table         VARCHAR(30) DEFAULT NULL;
	DECLARE v_qman_table      VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_seqadm_table    VARCHAR(30) DEFAULT 'adm_sequence';
	DECLARE v_seqadm_cycle    VARCHAR(1)  DEFAULT 'N';
	DECLARE v_seq_name        VARCHAR(30) DEFAULT NULL;
	DECLARE v_queue_name      VARCHAR(50) DEFAULT UPPER(p_queue_name);
	DECLARE v_seqadm_cnt      INT(10) DEFAULT 0;
	DECLARE v_seqadm_pkey     INT(10) DEFAULT 0;
	DECLARE v_max_bigint      BIGINT(20) UNSIGNED DEFAULT 18446744073709551610;
	
	DECLARE c_seqadm_cnt CURSOR FOR
	SELECT COUNT(*) AS CNT FROM adm_sequence;
	
	DECLARE c_seqadm_maxpkey CURSOR FOR
	SELECT MAX(PKEY) FROM adm_sequence;
	
	DECLARE EXIT HANDLER FOR SQLEXCEPTION	
		ROLLBACK;	

	SET v_queue_table = CONCAT(p_queue_name, '_t');
START TRANSACTION;
	SET @g_sql = CONCAT('CREATE TABLE ', v_queue_table, ' (
				`q_name` varchar(30) DEFAULT NULL,
				`msg_sid` bigint(20) unsigned NOT NULL,
				`msgid` varchar(36) NOT NULL,
				`priority` tinyint(1) unsigned DEFAULT NULL,
				`state` tinyint(1) unsigned NOT NULL,
				`sub_cnt` tinyint(1) unsigned,
				`expiration` datetime DEFAULT NULL,
				`enq_time` datetime NOT NULL,
				`enq_uid` varchar(30) DEFAULT NULL,
				`deq_time` datetime,
				`retry_count` int(5) unsigned DEFAULT NULL,
				`sender_msgid` varchar(36) DEFAULT NULL,
				`sender_name` varchar(30) DEFAULT NULL,
				`sender_addr` varchar(20) DEFAULT NULL,
				`user_data` varchar(8000) DEFAULT NULL,
				PRIMARY KEY (`msgid`),
				UNIQUE KEY `idx_qtab_msg_sid` (`msg_sid`),
				UNIQUE KEY `idx_qtab_sender_msgid` (`sender_msgid`),
				KEY `idx_qtab_state`  (`state`),
				KEY `idx_qtab_sub_cnt`  (`sub_cnt`),
				KEY `idx_qtab_enq_time`  (`enq_time`),
				KEY `idx_qtab_deq_time`  (`deq_time`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt1 FROM @g_sql;
	EXECUTE stmt1;
	DEALLOCATE PREPARE stmt1;
	SET @g_sql = NULL;
-- -------------------------------------------------------------------------
 IF p_qtype = 0 THEN
	SET v_i_table = CONCAT('aq_', v_queue_table, '_i');
	SET @g_sql = CONCAT('CREATE TABLE ', v_i_table, ' (
				`sub_id` int(5) unsigned NOT NULL,
				`sub_name` varchar(30) NOT NULL,
				`msg_sid` bigint(20) unsigned NOT NULL,
				`msgid` varchar(36) NOT NULL,
				`state` tinyint unsigned not null,
				KEY `idx_sub_id` (`sub_id`),
				KEY `idx_sub_name` (`sub_name`),
				KEY `idx_msg_sid` (`msg_sid`),
				KEY `idx_enq_msgid` (`msgid`),
				KEY `idx_enq_state` (`state`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
	SET @g_sql = null;
-- ---------------------------------------------------------------------------
	SET v_s_table = CONCAT('aq_', v_queue_table, '_s');
	SET @g_sql = CONCAT('CREATE TABLE ', v_s_table, ' (
				`sub_id` int(5) unsigned NOT NULL,
				`q_name` varchar(30) NOT NULL,
				`sub_name` varchar(80) DEFAULT NULL,
				`sub_address` varchar(128) DEFAULT NULL,
				PRIMARY KEY (`sub_id`),
				KEY `idx_sub_name` (`sub_name`),
				UNIQUE KEY `idx_sub_address` (`sub_address`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
	SET @g_sql = null;	
 END IF;	
-- ---------------------------------------------------------------------------
	SET @g_sql = CONCAT('INSERT INTO ', v_qman_table, '(q_name, q_type, payload_type, retention ) VALUES (' , 
				'''', v_queue_name, '''', ',', p_qtype,',', p_payload_type,',', p_retention, ')');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
	SET @g_sql = NULL; 
-- ----------------------------------------------------------------------------
	OPEN c_seqadm_cnt;
	FETCH c_seqadm_cnt INTO v_seqadm_cnt;
	CLOSE c_seqadm_cnt;
	IF v_seqadm_cnt = 0 THEN
		SET v_seqadm_pkey = 1;
	ELSE
		OPEN c_seqadm_maxpkey;
		FETCH c_seqadm_maxpkey INTO v_seqadm_pkey;
		CLOSE c_seqadm_maxpkey;
		SET v_seqadm_pkey = v_seqadm_pkey + 1;
	END IF;
	SET v_seq_name = CONCAT('aq_', p_queue_name, '_seq');
	SET v_seq_name = UPPER(v_seq_name);
	SET @g_sql = CONCAT('INSERT INTO ', v_seqadm_table, '(PKEY, NAME, INIT_NUMBER, LAST_NUMBER, MAX_NUMBER, INCREMENT_BY, CYCLE_FLAG) VALUES(',
				v_seqadm_pkey,',','''',v_seq_name,'''',',',1,',',0,',' ,v_max_bigint, ',' ,1, ',' ,'''',v_seqadm_cycle, '''', ')');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
	SET @g_sql = NULL; 
COMMIT;

END $$

DROP PROCEDURE IF EXISTS `prc_drop_queue` $$
CREATE PROCEDURE `prc_drop_queue`(
	IN p_queue_name      VARCHAR(50) )
BEGIN
	DECLARE v_sql                VARCHAR(2000) DEFAULT NULL;
	DECLARE v_qtable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_itable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_stable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_seqadm_table       VARCHAR(30) DEFAULT 'adm_sequence';
	DECLARE v_seqname            VARCHAR(50) DEFAULT NULL;
	
	DECLARE EXIT HANDLER FOR SQLEXCEPTION	
		ROLLBACK;
		
	SET v_qtable = CONCAT(p_queue_name, '_t');
	SET v_itable = CONCAT('aq_', v_qtable, '_i');
	SET v_stable = CONCAT('aq_', v_qtable, '_s');
	SET v_seqname = CONCAT('aq_', p_queue_name, '_seq');
	
START TRANSACTION;	
	SET @g_sql = CONCAT('DELETE FROM ', v_seqadm_table, ' WHERE NAME = UPPER(', '''',v_seqname,'''',')');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DELETE FROM ', v_qman_table, ' WHERE q_name = UPPER(', '''',p_queue_name,'''',')');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_qtable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_itable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_stable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	SET @g_sql = NULL;	
COMMIT;
	
END $$

DROP PROCEDURE IF EXISTS `prc_start_queue` $$
CREATE PROCEDURE `prc_start_queue`(
	IN p_queue_name      VARCHAR(50),
	IN p_queue_option    TINYINT(1) )
-- p_queue_name: the name of the queue
-- p_queue_option: the functionalities options of the queue
-- 0: eable enqueue; 1: enable dequeue; 2; enable both enqueue and dequeue
BEGIN
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_enable_value       TINYINT(1) DEFAULT 0;	

	IF p_queue_option = 0 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 1 THEN
		UPDATE aq_sys_queue_m SET DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 2 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value, DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);	
	END IF;	

END $$

DROP PROCEDURE IF EXISTS `prc_stop_queue` $$
CREATE PROCEDURE `prc_stop_queue`(
	IN p_queue_name      VARCHAR(50),
	IN p_queue_option    TINYINT(1) )
-- p_queue_name: the name of the queue
-- p_queue_option: the functionalities options of the queue
-- 0: disable enqueue; 1: disable dequeue; 2; disable both enqueue and dequeue
BEGIN
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_enable_value       TINYINT(1) DEFAULT 1;	

	IF p_queue_option = 0 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 1 THEN
		UPDATE aq_sys_queue_m SET DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 2 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value, DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);	
	END IF;	

END $$


DROP PROCEDURE IF EXISTS `prc_add_subscriber` $$
CREATE PROCEDURE `prc_add_subscriber`(
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