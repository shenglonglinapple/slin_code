DROP TABLE IF EXISTS `tra_occ`.`recipient`;
CREATE TABLE  `tra_occ`.`recipient` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `address` varchar(1024) COLLATE utf8_bin DEFAULT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` decimal(22,0) DEFAULT '0',
  `timeout` decimal(22,0) DEFAULT '0',
  `prop_type` varchar(50) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`pkey`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;