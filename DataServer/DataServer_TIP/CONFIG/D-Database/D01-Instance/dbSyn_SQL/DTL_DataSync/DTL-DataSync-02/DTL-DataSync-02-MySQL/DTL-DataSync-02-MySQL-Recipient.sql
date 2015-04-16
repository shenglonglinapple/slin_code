
create table recipient_info (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) COLLATE utf8_bin NOT NULL,
  `hostname` varchar(128) COLLATE utf8_bin NOT NULL,
  `address` varchar(128) COLLATE utf8_bin NOT NULL,
  `db_link_name` varchar(40) COLLATE utf8_bin DEFAULT NULL,
  `status` int(1) NOT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `RECIPIENT_UNIQUE` (`name`,`hostname`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

update recipient set address=name where name <> database();
alter table recipient_group drop column `address`;
alter table recipient_all drop column `address`;

insert into recipient_info values (1,'TRANSACT','occ-dbs-01','192.168.0.3:2005',null,0);
insert into recipient_info values (2,'TRA_OCC','occ-cms-02','192.168.0.2:5001',null,0);
insert into recipient_info values (3,'TRA_DT17','dt17-sms-01','192.168.0.171:5002',null,0);
insert into recipient_info values (4,'TRA_DT18','dt18-sms-01','192.168.0.181:5003',null,0);