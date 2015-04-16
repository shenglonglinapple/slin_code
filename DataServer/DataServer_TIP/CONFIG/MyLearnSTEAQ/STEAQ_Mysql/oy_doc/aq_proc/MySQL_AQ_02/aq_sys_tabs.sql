
DROP TABLE IF EXISTS  `aq_sys_queue_e`;
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


DROP TABLE IF EXISTS  `aq_sys_queue_m`;
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


DROP TABLE IF EXISTS `adm_sequence`;
CREATE TABLE   `adm_sequence` (
  `PKEY` int(10) NOT NULL,
  `NAME` varchar(30) COLLATE utf8_bin NOT NULL,
  `INIT_NUMBER` bigint(20) NOT NULL,
  `LAST_NUMBER` decimal(30,0) NOT NULL,
  `MAX_NUMBER` decimal(30,0) NOT NULL,
  `INCREMENT_BY` int(11) NOT NULL,
  `CYCLE_FLAG` varchar(1) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`PKEY`),
  UNIQUE KEY `idx_adm_seq_name` (`NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

INSERT INTO adm_sequence(PKEY,NAME,INIT_NUMBER,LAST_NUMBER,MAX_NUMBER,INCREMENT_BY,CYCLE_FLAG) 
     VALUES (1,'ERRLOG_SEQ',0,0,18446744073709551610,1,'N');

