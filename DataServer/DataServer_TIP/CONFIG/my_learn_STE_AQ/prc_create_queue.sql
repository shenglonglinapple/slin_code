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

DELIMITER ;