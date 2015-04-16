DELIMITER $$

DROP TABLE IF EXISTS `error_log` $$


CREATE TABLE `error_log` 
(
  `pkey` int(9) NOT NULL,
  `sql_statement` varchar(2000) NOT NULL,
  `error_message` varchar(2000) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`pkey`),
  KEY `ERRORLOG_TIMESTAMP_IDX` (`timestamp`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$




DELIMITER ;

