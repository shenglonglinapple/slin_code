DROP TABLE IF EXISTS `recipient`;
CREATE TABLE  `recipient` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `address` varchar(1024) COLLATE utf8_bin DEFAULT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` decimal(22,0) DEFAULT '0',
  `timeout` decimal(22,0) DEFAULT '0',
  `prop_type` varchar(50) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`pkey`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `recipient_all`;
CREATE TABLE  `recipient_all` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `member` varchar(30) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `RECIPIENT_UNIQUE` (`name`,`member`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `recipient_group`;
CREATE TABLE  `recipient_group` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `member` varchar(30) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT '0',
  `prop_type` varchar(50) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `name` (`name`,`member`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `recipient_info`;
CREATE TABLE  `recipient_info` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `hostname` varchar(128) COLLATE utf8_bin NOT NULL,
  `address` varchar(128) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` int(1) NOT NULL,
  `db_type` varchar(50) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `RECIPIENT_UNIQUE` (`name`,`hostname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;