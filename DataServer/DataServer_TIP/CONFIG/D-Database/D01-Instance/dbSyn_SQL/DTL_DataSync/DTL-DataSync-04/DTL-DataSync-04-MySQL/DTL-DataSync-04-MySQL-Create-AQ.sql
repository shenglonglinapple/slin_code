
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
				`state` tinyint unsigned not null,
        KEY `idx_sub_name` (`sub_name`),
				KEY `idx_enq_hid` (`enq_hid`),
				KEY `idx_enq_lid` (`enq_lid`),
				KEY `idx_enq_msgid` (`msgid`),
				KEY `idx_enq_state` (`state`)
				) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
  set @g_sql = null;

END $$
DELIMITER ;

call prc_drop_queue('audit_data_queue');
call prc_create_queue('audit_data_queue');

delimiter $$

drop trigger if exists que_enq_adr_trg $$
CREATE TRIGGER que_enq_adr_trg after DELETE
    ON aq_audit_data_queue_t_en FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if old.state <> 3 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid;
    if lv_cnt is null or lv_cnt = '' then
        delete from audit_data_queue_t where msgid = old.msgid;
    else 
	  update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;
END$$


drop trigger if exists que_enq_aur_trg $$
CREATE TRIGGER que_enq_aur_trg after UPDATE
    ON aq_audit_data_queue_t_en FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if new.state = 4 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid and state<>4;
    if lv_cnt is null or lv_cnt = '' then
       update audit_data_queue_t set state = 4, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

  if new.state = 3 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid and state<>3;
    if lv_cnt is null or lv_cnt = '' then
       update audit_data_queue_t set state = 3, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

END$$
delimiter ;
