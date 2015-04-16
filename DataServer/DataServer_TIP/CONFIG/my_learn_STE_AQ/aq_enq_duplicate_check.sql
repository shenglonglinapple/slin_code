DROP TABLE IF EXISTS `tra_occ`.`aq_enq_duplicate_check`;
CREATE TABLE  `tra_occ`.`aq_enq_duplicate_check` (
  `PKEY` int(10) NOT NULL,
  `LOCATION` varchar(80) COLLATE utf8_bin NOT NULL,
  `SRV_ID` int(5) DEFAULT '0',
  `Q_NAME` varchar(80) COLLATE utf8_bin NOT NULL,
  `MSG_SID` bigint(20) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;