DELIMITER $$

DROP TABLE IF EXISTS  `aq_sys_queue_m` $$

CREATE TABLE   `aq_sys_queue_m` (
  `q_name` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `q_type` tinyint(1) unsigned NOT NULL,
  `sub_count` int(5) unsigned DEFAULT 0,
  `enq_state` tinyint(1) unsigned DEFAULT 0,
  `deq_state` tinyint(1) unsigned DEFAULT 0,
  `payload_type` tinyint(1) unsigned NOT NULL,	
  `retention` int(11) unsigned DEFAULT 0,
  `remark` varchar(512) COLLATE utf8_bin DEFAULT NULL,
  UNIQUE KEY `idx_mqtab_qname` (`q_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin  $$

$$

DELIMITER ;


