DROP TABLE IF EXISTS `recipient_all`;
CREATE TABLE  `recipient_all` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `member` varchar(30) COLLATE utf8_bin NOT NULL,
  `address` varchar(128) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `RECIPIENT_UNIQUE` (`name`,`member`,`address`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `recipient_group`;
CREATE TABLE  `recipient_group` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `member` varchar(30) COLLATE utf8_bin NOT NULL,
  `address` varchar(128) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT '0',
  PRIMARY KEY (`pkey`),
  UNIQUE KEY (`name`,`member`,`address`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (6, 'TRA_DT18', 'TRANSACT', '192.168.0.3:2005', 0);
Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (5, 'TRA_DT17', 'TRANSACT', '192.168.0.3:2005', 0);
Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (4, 'TRA_OCC', 'TRANSACT', '192.168.0.3:2005', 0);
Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (3, 'TRANSACT', 'TRA_DT18', '192.168.0.181:5003', 0);
Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (2, 'TRANSACT', 'TRA_DT17', '192.168.0.171:5002', 0);
Insert into RECIPIENT_ALL
   (PKEY, NAME, MEMBER, ADDRESS, STATUS)
 Values
   (1, 'TRANSACT', 'TRA_OCC', '192.168.0.2:5001', 0);

insert into recipient_group(pkey,name,member,address,status)
  (select 1,name,member,address,0 from recipient_all
    where name = upper(database()) and member='TRANSACT');

truncate table recipient;

insert into recipient(pkey,name,address,status)
  (select 1,member,address,0 from recipient_all
    where name = upper(database()) and member='TRANSACT');


