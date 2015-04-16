DROP TABLE IF EXISTS `tra_occ`.`recipient_group`;
CREATE TABLE  `tra_occ`.`recipient_group` (
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