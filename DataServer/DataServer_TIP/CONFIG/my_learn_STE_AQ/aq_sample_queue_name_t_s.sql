DELIMITER $$

DROP TABLE IF EXISTS `sample_queue_name_s` $$


CREATE TABLE `sample_queue_name_s` 
(
	`sub_id` int(5) unsigned NOT NULL,
	`q_name` varchar(30) NOT NULL,
	`sub_name` varchar(80) DEFAULT NULL,
	`sub_address` varchar(128) DEFAULT NULL,
	PRIMARY KEY (`sub_id`),
	KEY `idx_sub_name` (`sub_name`),
	UNIQUE KEY `idx_sub_address` (`sub_address`)
	
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$




DELIMITER ;

