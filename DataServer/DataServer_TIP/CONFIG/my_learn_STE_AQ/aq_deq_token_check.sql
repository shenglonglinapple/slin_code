DROP TABLE IF EXISTS `tra_occ`.`aq_deq_token_check`;
CREATE TABLE  `tra_occ`.`aq_deq_token_check` (
  `PKEY` int(10) NOT NULL,
  `LOCATION` varchar(80) COLLATE utf8_bin NOT NULL,
  `SRV_ID` int(5) DEFAULT '0',
  `Q_NAME` varchar(80) COLLATE utf8_bin NOT NULL,
  `UPD_TIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  UNIQUE KEY `AQ_DEQ_TOKEN_CHECK_U01` (`LOCATION`,`SRV_ID`,`Q_NAME`),
  KEY `Index_pk` (`PKEY`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;