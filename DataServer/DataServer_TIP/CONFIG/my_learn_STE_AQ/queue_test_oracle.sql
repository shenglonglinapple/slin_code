DROP TABLE IF EXISTS `tra_occ`.`queue_test_oracle`;
CREATE TABLE  `tra_occ`.`queue_test_oracle` (
  `id` int(11) DEFAULT NULL,
  `name` varchar(2000) COLLATE utf8_bin DEFAULT NULL,
  `timestamp` datetime DEFAULT NULL,
  `location` varchar(2000) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;