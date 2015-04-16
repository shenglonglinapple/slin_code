ALTER TABLE RECIPIENT
 ADD (PROP_TYPE  VARCHAR2(50));
ALTER TABLE RECIPIENT_GROUP
 ADD (PROP_TYPE  VARCHAR2(50));
ALTER TABLE RECIPIENT_INFO
 ADD (DB_TYPE  VARCHAR2(50));

update recipient set prop_type = 'MYSQL' where upper(name) <>'TRANSACT';
update recipient set prop_type = 'ORACLE' where upper(name) ='TRANSACT';
 
ALTER TABLE RECIPIENT
MODIFY(prop_type  NOT NULL);

update recipient_group set prop_type = 'MYSQL' where upper(member) <>'TRANSACT';
update recipient_group set prop_type = 'ORACLE' where upper(member) ='TRANSACT';
 
ALTER TABLE RECIPIENT_GROUP
MODIFY(prop_type  NOT NULL);

update recipient_info set db_type = 'MYSQL' where upper(name) <>'TRANSACT';
update recipient_info set db_type = 'ORACLE' where upper(name) ='TRANSACT';
 
ALTER TABLE RECIPIENT_INFO
MODIFY(db_type  NOT NULL);