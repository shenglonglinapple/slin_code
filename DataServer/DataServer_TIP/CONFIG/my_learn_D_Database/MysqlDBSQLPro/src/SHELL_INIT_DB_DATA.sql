
/*
init ADM_SEQUENCE
*/
TRUNCATE TABLE  ADM_SEQUENCE;
-- INSERT INTO ADM_SEQUENCE(SEQ_NAME, INIT_NUMBER, LAST_NUMBER, MAX_NUMBER, INCREMENT_BY, CYCLE_FLAG) VALUES('MY_LOG_SEQ', 0, 0, 18446744073709551610, 1, 'Y');
INSERT INTO ADM_SEQUENCE(SEQ_NAME, INIT_NUMBER, LAST_NUMBER, MAX_NUMBER, INCREMENT_BY, CYCLE_FLAG) VALUES('MY_LOG_SEQ', 0, 0, 2000000000, 1, 'Y');



/*
init MY_LOG
*/
TRUNCATE TABLE   MY_LOG;
INSERT INTO MY_LOG (LOG_PKEY, LOG_TIMESTAMP, LOG_LEVEL, LOG_MSG_FUN, LOG_MSG_STR0, LOG_MSG_STR1, LOG_MSG_STR2) VALUES(-1, now(), CONCAT('INFO'),CONCAT('LOG_MSG_FUN'), CONCAT('LOG_MSG_STR0'),CONCAT('LOG_MSG_STR1'),CONCAT('LOG_MSG_STR2'));
INSERT INTO MY_LOG (LOG_PKEY, LOG_TIMESTAMP, LOG_LEVEL, LOG_MSG_FUN, LOG_MSG_STR0, LOG_MSG_STR1, LOG_MSG_STR2) VALUES(-2, now(), CONCAT('DEBUG'),CONCAT('LOG_MSG_FUN'), CONCAT('LOG_MSG_STR0'),CONCAT('LOG_MSG_STR1'),CONCAT('LOG_MSG_STR2'));
INSERT INTO MY_LOG (LOG_PKEY, LOG_TIMESTAMP, LOG_LEVEL, LOG_MSG_FUN, LOG_MSG_STR0, LOG_MSG_STR1, LOG_MSG_STR2) VALUES(-3, now(), CONCAT('TRACE'),CONCAT('LOG_MSG_FUN'), CONCAT('LOG_MSG_STR0'),CONCAT('LOG_MSG_STR1'),CONCAT('LOG_MSG_STR2'));
INSERT INTO MY_LOG (LOG_PKEY, LOG_TIMESTAMP, LOG_LEVEL, LOG_MSG_FUN, LOG_MSG_STR0, LOG_MSG_STR1, LOG_MSG_STR2) VALUES(-4, now(), CONCAT('WARNING'),CONCAT('LOG_MSG_FUN'), CONCAT('LOG_MSG_STR0'),CONCAT('LOG_MSG_STR1'),CONCAT('LOG_MSG_STR2'));
INSERT INTO MY_LOG (LOG_PKEY, LOG_TIMESTAMP, LOG_LEVEL, LOG_MSG_FUN, LOG_MSG_STR0, LOG_MSG_STR1, LOG_MSG_STR2) VALUES(-5, now(), CONCAT('ERROR'),CONCAT('LOG_MSG_FUN'), CONCAT('LOG_MSG_STR0'),CONCAT('LOG_MSG_STR1'),CONCAT('LOG_MSG_STR2'));



/*
init CREATE_TYPE_AS_OBJECT
*/
TRUNCATE TABLE  CREATE_TYPE_AS_OBJECT;
INSERT INTO CREATE_TYPE_AS_OBJECT(OBJECT_NAME, QUEUE_NAME, OBJECT_MSG) VALUES('AUDIT_DATA_QUEUE_PAYLOAD_TYPE', 'AUDIT_DATA_QUEUE', 'MESSAGE_QUALIFIER  VARCHAR(100), AUDIT_DATA_ORACLE VARCHAR(4000),  AUDIT_DATA_MYSQL VARCHAR(4000)');





/*
init CREATE_QUEUE_RECORD
*/
ALTER TABLE CREATE_QUEUE_RECORD AUTO_INCREMENT=0;
TRUNCATE TABLE  CREATE_QUEUE_RECORD;




/*
init CREATE_QUEUE
*/
CALL PRC_DBMS_AQADM_CREATE_QUEUE('AUDIT_DATA_QUEUE');


