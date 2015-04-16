DELIMITER $$

DROP TABLE IF EXISTS `sample_queue_name_t` $$


CREATE TABLE `sample_queue_name_t` 
(
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
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$

DELIMITER ;

