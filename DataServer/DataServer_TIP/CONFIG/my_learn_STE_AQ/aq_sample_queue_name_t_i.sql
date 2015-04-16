DELIMITER $$

DROP TABLE IF EXISTS `sample_queue_name_i` $$


CREATE TABLE `sample_queue_name_i` 
(
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
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$




DELIMITER ;

