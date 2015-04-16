DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_create_queue` $$
CREATE PROCEDURE `prc_create_queue`(
	IN p_queue_name      VARCHAR(50))
BEGIN
	DECLARE v_queue_table     VARCHAR(30) DEFAULT NULL;
	DECLARE v_enq_table       VARCHAR(30) DEFAULT NULL;
	DECLARE v_deq_table       VARCHAR(30) DEFAULT NULL;

	SET v_queue_table = CONCAT(p_queue_name, '_t');
	SET @g_sql = CONCAT('CREATE TABLE ', v_queue_table, ' (
				`q_name` varchar(30) DEFAULT NULL,
				`enq_hid` int(10) unsigned NOT NULL,
				`enq_lid` int(10) unsigned NOT NULL,
				`msgid` varchar(36) NOT NULL,
				`priority` tinyint(1) unsigned DEFAULT NULL,
				`state` tinyint(1) unsigned NOT NULL,
				`sub_cnt` tinyint(1) unsigned,
				`expiration` datetime DEFAULT NULL,
				`enq_time` datetime NOT NULL,
				`enq_uid` varchar(30) DEFAULT NULL,
				`deq_time` datetime,
				`retry_count` int(5) unsigned DEFAULT NULL,
				`sender_msgid` varchar(36),
				`sender_name` varchar(30) DEFAULT NULL,
				`sender_addr` varchar(20) DEFAULT NULL,
				`user_data` varchar(4000) DEFAULT NULL,
				PRIMARY KEY (`msgid`),
				KEY `idx_qtab_hid` (`enq_hid`),
				KEY `idx_qtab_lid` (`enq_lid`),
				UNIQUE KEY `idx_qtab_sender_msgid` (`sender_msgid`),
				KEY `idx_qtab_state`  (`state`),
				KEY `idx_qtab_sub_cnt`  (`sub_cnt`),
				KEY `idx_qtab_enq_time`  (`enq_time`),
				KEY `idx_qtab_deq_time`  (`deq_time`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt1 FROM @g_sql;
	EXECUTE stmt1;
	DEALLOCATE PREPARE stmt1;
  set @g_sql = null;
-- -------------------------------------------------------------------------
	SET v_enq_table = CONCAT('aq_', v_queue_table, '_en');
	#SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_enq_table);
	#PREPARE stmt2 FROM @g_sql;
	#EXECUTE stmt2;
	#DEALLOCATE PREPARE stmt2;
	SET @g_sql = CONCAT('CREATE TABLE ', v_enq_table, ' (
				`sub_id` int(10) unsigned NOT NULL,
				`sub_name` varchar(30) NOT NULL,
				`enq_hid` int(10) unsigned NOT NULL,
				`enq_lid` int(10) unsigned NOT NULL,
				`msgid` varchar(36) NOT NULL,
        KEY `idx_sub_name` (`sub_name`),
				KEY `idx_enq_hid` (`enq_hid`),
				KEY `idx_enq_lid` (`enq_lid`),
				KEY `idx_msgid` (`msgid`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
  set @g_sql = null;

END $$

DROP PROCEDURE IF EXISTS `prc_drop_queue` $$
CREATE PROCEDURE `prc_drop_queue`(
	IN p_queue_name      VARCHAR(50))
BEGIN
	DECLARE v_sql             VARCHAR(2000);
	DECLARE v_queue_table     VARCHAR(30) DEFAULT NULL;
	DECLARE v_enq_table       VARCHAR(30) DEFAULT NULL;
	DECLARE v_deq_table       VARCHAR(30) DEFAULT NULL;
	DECLARE v_sub_table       VARCHAR(30) DEFAULT NULL;
	
	SET v_queue_table = CONCAT(p_queue_name, '_t');
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_queue_table);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET v_enq_table = CONCAT('aq_', v_queue_table, '_en');
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_enq_table);
	PREPARE stmt2 FROM @g_sql;
	EXECUTE stmt2;
	DEALLOCATE PREPARE stmt2;

	DROP TRIGGER IF EXISTS que_bdr_trg;

	COMMIT;

END $$

delimiter ;

call prc_drop_queue('audit_data_queue');
call prc_create_queue('audit_data_queue');
delimiter $$
CREATE TRIGGER que_bdr_trg BEFORE DELETE
    ON audit_data_queue_t FOR EACH ROW
BEGIN

       delete from aq_audit_data_queue_t_en where msgid = old.msgid;

END$$
delimiter ;