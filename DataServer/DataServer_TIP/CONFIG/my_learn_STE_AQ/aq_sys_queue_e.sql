DELIMITER $$

DROP TABLE IF EXISTS  `aq_sys_queue_e` $$

CREATE TABLE   `aq_sys_queue_e` (
  `q_name` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `msg_sid` bigint(20) unsigned NOT NULL,
  `msgid` varchar(36) COLLATE utf8_bin NOT NULL,
  `priority` tinyint(1) unsigned DEFAULT NULL,
  `expiration` datetime DEFAULT NULL,
  `enq_time` datetime NOT NULL,
  `enq_uid` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `deq_time` datetime DEFAULT NULL,
  `retry_count` int(5) unsigned DEFAULT NULL,
  `sender_msgid` varchar(36) COLLATE utf8_bin DEFAULT NULL,
  `sender_name` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `sender_addr` varchar(20) COLLATE utf8_bin DEFAULT NULL,
  `user_data` varchar(8000) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`msgid`),
  UNIQUE KEY `idx_qtab_sender_msgid` (`sender_msgid`),
  UNIQUE KEY `idx_qtab_sid` (`msg_sid`),
  KEY `idx_qtab_enq_time` (`enq_time`),
  KEY `idx_qtab_deq_time` (`deq_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

$$

DELIMITER ;

