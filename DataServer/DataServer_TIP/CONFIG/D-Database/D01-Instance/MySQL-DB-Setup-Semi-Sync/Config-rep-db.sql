
DROP TABLE IF EXISTS `rep`.`adm_rep_gtid_log`;
CREATE TABLE  `rep`.`adm_rep_gtid_log` (
  `last_rec_gtid` varchar(200) COLLATE utf8_bin,
  `last_exec_gtid` varchar(200) COLLATE utf8_bin,
  `sourcetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `rep`.`adm_rep_mon`;
CREATE TABLE  `rep`.`adm_rep_mon` (
  `status` varchar(10) COLLATE utf8_bin NOT NULL,
  `times` int(11) DEFAULT '0',
  `updtime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


DROP TABLE IF EXISTS `rep`.`adm_rep_variables`;
CREATE TABLE  `rep`.`adm_rep_variables` (
  `name` varchar(64) COLLATE utf8_bin NOT NULL,
  `value` varchar(1024) COLLATE utf8_bin DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

/*
DROP TABLE IF EXISTS `rep`.`adm_rep_status`;
CREATE TABLE  `rep`.`adm_rep_status` (
  `name` varchar(64) NOT NULL,
  `value` varchar(512) DEFAULT NULL,
  UNIQUE KEY `idx_adm_rep_status_name` (`NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
*/

-- insert into rep.adm_rep_sign values (0);
insert into `rep`.`adm_rep_variables` values ('IsFromRWtoRO','0');
insert into rep.adm_rep_mon(status) values ('READ'), ('WRITE');
insert into rep.adm_rep_variables(name) values ('LAST_RETRIEVED_GTID'),('LAST_EXECUTED_GTID');