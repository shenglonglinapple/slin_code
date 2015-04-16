CREATE TABLE  `aq_deq_token_check` (
  `PKEY` int(10) NOT NULL,
  `LOCATION` varchar(80) COLLATE utf8_bin NOT NULL,
  `SRV_ID` int(5) DEFAULT 0,
  `Q_NAME` varchar(80) COLLATE utf8_bin NOT NULL,
  `UPD_TIME` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`PKEY`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

CREATE TABLE  `aq_enq_duplicate_check` (
  `PKEY` int(10) NOT NULL,
  `LOCATION` varchar(80) COLLATE utf8_bin NOT NULL,
  `SRV_ID` int(5) DEFAULT 0,
  `Q_NAME` varchar(80) COLLATE utf8_bin NOT NULL,
  `MSG_SID` bigint(20) DEFAULT 0,
  PRIMARY KEY (`PKEY`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;