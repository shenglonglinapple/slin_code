
create table recipient_info (
  pkey number NOT NULL,
  name varchar2(30)  NOT NULL,
  hostname varchar2(128)  NOT NULL,
  address varchar2(128)  NOT NULL,
  db_link_name varchar2(40)  DEFAULT NULL,
  status number(1) NOT NULL)
  TABLESPACE CONFIG_DATA;
  
ALTER TABLE RECIPIENT_INFO
 ADD CONSTRAINT RECIPIENT_INFO_PK
 PRIMARY KEY
 (PKEY)
 using index
 tablespace CONFIG_INDX;

ALTER TABLE RECIPIENT_INFO
 ADD CONSTRAINT RECIPIENT_INFO_U_NAME_HOSTNAME
 UNIQUE (NAME, HOSTNAME)
 using index
 tablespace CONFIG_INDX;

update recipient set address=name where name<>'TRANSACT';

ALTER TABLE RECIPIENT_GROUP
  DROP CONSTRAINT RECIPIENT_GROUP_UNIQUE;
alter table recipient_group drop column address;
ALTER TABLE RECIPIENT_GROUP ADD 
  CONSTRAINT RECIPIENT_GROUP_UNIQUE
 UNIQUE (NAME, MEMBER)
 using index
 tablespace CONFIG_INDX;

ALTER TABLE RECIPIENT_ALL
  DROP CONSTRAINT RECIPIENT_ALL_UNIQUE;
alter table recipient_all drop column address;
ALTER TABLE RECIPIENT_ALL ADD 
  CONSTRAINT RECIPIENT_ALL_UNIQUE
 UNIQUE (NAME, MEMBER)
 using index
 tablespace CONFIG_INDX;

insert into recipient_info values (1,'TRANSACT','occ-dbs-01','192.168.0.3:2005',null,0);
insert into recipient_info values (2,'TRA_OCC','occ-cms-02','192.168.0.2:5001',null,0);
insert into recipient_info values (3,'TRA_DT17','dt17-sms-01','192.168.0.171:5002',null,0);
insert into recipient_info values (4,'TRA_DT18','dt18-sms-01','192.168.0.181:5003',null,0);

truncate table recipient_group;
declare lv_int int default 1;
begin
 for cu in (select name from recipient_info where name <> 'TRANSACT') LOOP
    insert into recipient_group (pkey,name,member,status) values (lv_int,cu.name,cu.name,0);
    lv_int := lv_int+1;
 end loop;
end;
/  
