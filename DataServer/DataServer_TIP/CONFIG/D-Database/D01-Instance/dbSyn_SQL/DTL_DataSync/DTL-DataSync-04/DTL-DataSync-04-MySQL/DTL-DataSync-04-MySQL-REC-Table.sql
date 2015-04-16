ALTER TABLE RECIPIENT
 ADD (prop_type  VARCHAR(50));
ALTER TABLE RECIPIENT_GROUP
 ADD (prop_type  VARCHAR(50));
ALTER TABLE RECIPIENT_INFO
 ADD (db_type  VARCHAR(50));

update recipient set prop_type = 'MYSQL' where upper(name) <>'TRANSACT';
update recipient set prop_type = 'ORACLE' where upper(name) ='TRANSACT';

ALTER TABLE recipient MODIFY COLUMN `prop_type` VARCHAR(50) NOT NULL;


update recipient_group set prop_type = 'MYSQL' where upper(member) <>'TRANSACT';
update recipient_group set prop_type = 'ORACLE' where upper(member) ='TRANSACT';

ALTER TABLE recipient_group MODIFY COLUMN `prop_type` VARCHAR(50) NOT NULL;

update recipient_info set db_type = 'MYSQL' where upper(name) <>'TRANSACT';
update recipient_info set db_type = 'ORACLE' where upper(name) ='TRANSACT';

ALTER TABLE recipient_info MODIFY COLUMN `db_type` VARCHAR(50) NOT NULL;