DROP TABLE IF EXISTS `tra_occ`.`recipient_info`;
CREATE TABLE  `tra_occ`.`recipient_info` (
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