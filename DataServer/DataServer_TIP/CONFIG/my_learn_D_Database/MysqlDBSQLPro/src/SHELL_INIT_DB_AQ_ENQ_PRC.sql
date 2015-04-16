/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_ENQ` $$

CREATE PROCEDURE `PRC_ENQ`(
	  IN p_usr_database_name      VARCHAR(128),
	  IN p_queue_name      VARCHAR(128),
      IN p_message_qualifier     VARCHAR(80),
      IN p_audit_data_Oracle     VARCHAR(2048),
      IN p_audit_data_MySQL      VARCHAR(2048)
)
/*
p_message_qualifier='LOCAL','INSERT', 'UPDATE', 'DELETE', 'GROUP','PUBLIC','TRA_BBS'
CALL PRC_ENQ('AUDIT_DATA_QUEUE', 'PUBLIC', 'p_audit_data_Oracle', 'p_audit_data_MySQL');
*/
BEGIN
	DECLARE str_USR_DATABASE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_QUEUE_TYPE    VARCHAR(256) DEFAULT NULL;
	DECLARE str_OBJECT_NAME    VARCHAR(256) DEFAULT NULL;
	DECLARE str_SEQ_AQ_SAMPLE_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T    VARCHAR(128) DEFAULT NULL;	
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_I    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_S    VARCHAR(128) DEFAULT NULL;
	DECLARE str_CURRENT_DATABASE_NAME    VARCHAR(128) DEFAULT NULL;

	SET str_USR_DATABASE_NAME = p_usr_database_name;
	
	SET str_QUEUE_NAME = p_queue_name;
	SET str_QUEUE_TYPE = CONCAT('SYS.DBMS_AQADM.NORMAL_QUEUE');
	SET str_OBJECT_NAME = CONCAT('AUDIT_DATA_QUEUE_PAYLOAD_TYPE');
	CALL PRC_GET_QUEUE_INFO(str_QUEUE_NAME, str_SEQ_AQ_SAMPLE_QUEUE_NAME, str_AQ_SAMPLE_QUEUE_NAME_T, str_AQ_SAMPLE_QUEUE_NAME_T_I, str_AQ_SAMPLE_QUEUE_NAME_T_S);

	SET	str_CURRENT_DATABASE_NAME = UPPER(DATABASE());

	/*
	p_message_qualifier='LOCAL','INSERT', 'UPDATE', 'DELETE', 'GROUP','PUBLIC','TRA_BBS'
	*/
	IF (p_message_qualifier in ('INSERT', 'UPDATE', 'DELETE', 'LOCAL'))
	THEN
		CALL PRC_ENQ_LOCAL(p_usr_database_name, p_queue_name, p_message_qualifier, p_audit_data_Oracle, p_audit_data_MySQL);
	ELSE
		CALL PRC_ENQ_PEER(p_usr_database_name, p_queue_name, p_message_qualifier, p_audit_data_Oracle, p_audit_data_MySQL);
	END IF;

END $$

DELIMITER ;

/*-----------------------------------------------------------------------------------------------------------*/




/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_ENQ_LOCAL` $$

CREATE PROCEDURE `PRC_ENQ_LOCAL`(
	  IN p_usr_database_name      VARCHAR(128),
	  IN p_QUEUE_NAME      VARCHAR(128),
      IN p_message_qualifier     VARCHAR(80),
      IN p_audit_data_Oracle     VARCHAR(2048),
      IN p_audit_data_MySQL      VARCHAR(2048)
)
/*
p_message_qualifier='LOCAL','INSERT', 'UPDATE', 'DELETE', 'GROUP','PUBLIC','TRA_BBS'
*/
BEGIN
	/* exec mysql sql in local db*/
	CALL PRC_EXEC_MYSQL_SQL(p_audit_data_MySQL);
END $$

DELIMITER ;

/*-----------------------------------------------------------------------------------------------------------*/






/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_ENQ_PEER` $$

CREATE PROCEDURE `PRC_ENQ_PEER`(
	IN p_usr_database_name      VARCHAR(128),
	IN p_QUEUE_NAME      VARCHAR(128),
    IN p_message_qualifier     VARCHAR(80),
    IN p_audit_data_Oracle     VARCHAR(2048),
    IN p_audit_data_MySQL      VARCHAR(2048)
)
/*
p_message_qualifier='LOCAL','INSERT', 'UPDATE', 'DELETE', 'GROUP','PUBLIC','TRA_BBS'
*/
BEGIN
	DECLARE str_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_QUEUE_TYPE    VARCHAR(256) DEFAULT NULL;
	DECLARE str_OBJECT_NAME    VARCHAR(256) DEFAULT NULL;
	DECLARE str_SEQ_AQ_SAMPLE_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T    VARCHAR(128) DEFAULT NULL;	
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_I    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_S    VARCHAR(128) DEFAULT NULL;
	DECLARE str_DATABASE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE n_SUB_CNT         TINYINT(1) DEFAULT NULL;

	SET str_QUEUE_NAME = p_QUEUE_NAME;
	SET str_QUEUE_TYPE = CONCAT('SYS.DBMS_AQADM.NORMAL_QUEUE');
	SET str_OBJECT_NAME = CONCAT('AUDIT_DATA_QUEUE_PAYLOAD_TYPE');
  
	CALL PRC_GET_QUEUE_INFO(str_QUEUE_NAME, str_SEQ_AQ_SAMPLE_QUEUE_NAME, str_AQ_SAMPLE_QUEUE_NAME_T, str_AQ_SAMPLE_QUEUE_NAME_T_I, str_AQ_SAMPLE_QUEUE_NAME_T_S);

	SET	str_DATABASE_NAME = UPPER(DATABASE());
	SET n_SUB_CNT = 1;
	
	/* exec mysql sql in local db*/
	CALL PRC_EXEC_MYSQL_SQL(p_audit_data_MySQL);

	CALL PRC_AQ_SAMPLE_QUEUE_NAME_T_INSERT(p_usr_database_name, p_QUEUE_NAME, p_message_qualifier, p_audit_data_Oracle, p_audit_data_MySQL, n_SUB_CNT);

END $$

DELIMITER ;

/*-----------------------------------------------------------------------------------------------------------*/















/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_EXEC_MYSQL_SQL` $$

CREATE PROCEDURE `PRC_EXEC_MYSQL_SQL`(
      IN p_audit_data_MySQL      VARCHAR(2048)
)
BEGIN
	DECLARE	str_LOG_LEVEL		VARCHAR(128)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_FUN		VARCHAR(256)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR0	VARCHAR(2048)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR1	VARCHAR(2048)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR2	VARCHAR(2048)	DEFAULT	NULL;	

	/*
		begin  error process
	*/

	/*
	
	*/
	DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
	BEGIN
		ROLLBACK;
		
		START TRANSACTION;
	
		SET str_LOG_LEVEL = CONCAT('ERROR');
		SET str_LOG_MSG_FUN = CONCAT('PRC_EXEC_MYSQL_SQL');
		SET str_LOG_MSG_STR0 = CONCAT('CALL PRC_EXEC_MYSQL_SQL catch SQLEXCEPTION');
		SET str_LOG_MSG_STR1 = CONCAT('p_audit_data_MySQL=', p_audit_data_MySQL);
		SET str_LOG_MSG_STR2 = CONCAT('NULL');
		CALL PRC_MY_LOG_INSERT(str_LOG_LEVEL, str_LOG_MSG_FUN, str_LOG_MSG_STR0, str_LOG_MSG_STR1, str_LOG_MSG_STR2);
		SET str_LOG_LEVEL = NULL;
		SET str_LOG_MSG_FUN = NULL;
		SET str_LOG_MSG_STR0 = NULL;
		SET str_LOG_MSG_STR1 = NULL;
		SET str_LOG_MSG_STR2 = NULL;
		
		COMMIT;
		
		resignal;
    END;

	/*
	end  error process
	*/


	-- exec sql	
	SET @G_SQL = NULL;
	SET @G_SQL = p_audit_data_MySQL;
	PREPARE stmt_SQL FROM @G_SQL;
	EXECUTE stmt_SQL;
	DEALLOCATE PREPARE stmt_SQL;
	set @G_SQL = null;


END $$

DELIMITER ;

/*-----------------------------------------------------------------------------------------------------------*/




/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_CREATE_QUEUE_RECORD_INSERT` $$

CREATE PROCEDURE `PRC_CREATE_QUEUE_RECORD_INSERT`(
      IN p_QUEUE_NAME VARCHAR(128),
	  IN p_QUEUE_TABLE VARCHAR(128),
	  IN p_QUEUE_TYPE VARCHAR(256),
	  IN p_OBJECT_NAME VARCHAR(256),
	  IN p_SQL_CREATE_QUEUE_TABLES VARCHAR(2048)
)
/*
CALL PRC_CREATE_QUEUE_RECORD_INSERT('AUDIT_DATA_QUEUE', 'AQ_AUDIT_DATA_QUEUE_T', 'SYS.DBMS_AQADM.NORMAL_QUEUE', 'AUDIT_DATA_QUEUE_PAYLOAD_TYPE', 'CREATE TABLE AQ_AUDIT_DATA_QUEUE_T LIKE AQ_SAMPLE_QUEUE_NAME_T;CREATE TABLE AQ_AUDIT_DATA_QUEUE_T_I LIKE AQ_SAMPLE_QUEUE_NAME_T_I;CREATE TABLE AQ_AUDIT_DATA_QUEUE_T_S LIKE AQ_SAMPLE_QUEUE_NAME_T_s');
*/
BEGIN
	DECLARE	str_LOG_LEVEL		VARCHAR(128)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_FUN		VARCHAR(256)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR0	VARCHAR(2048)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR1	VARCHAR(2048)	DEFAULT	NULL;
	DECLARE	str_LOG_MSG_STR2	VARCHAR(2048)	DEFAULT	NULL;	
	
	DECLARE str_TABLE_NAME VARCHAR(256)	DEFAULT	"CREATE_QUEUE_RECORD";
	DECLARE str_COLUMN_NAME VARCHAR(1024)	DEFAULT	"QUEUE_NAME,QUEUE_TABLE,QUEUE_TYPE,OBJECT_NAME,SQL_CREATE_QUEUE_TABLES";
	DECLARE str_COLUMN_VALUE VARCHAR(8192)	DEFAULT	NULL;
	DECLARE str_SQL_INSERT VARCHAR(10240)	DEFAULT	NULL;

	/*
		begin  error process
	*/

	/*
	
	*/
	DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
	BEGIN
		ROLLBACK;
		
		START TRANSACTION;
	
		SET str_LOG_LEVEL = CONCAT('ERROR');
		SET str_LOG_MSG_FUN = CONCAT('PRC_CREATE_QUEUE_RECORD_INSERT');
		SET str_LOG_MSG_STR0 = CONCAT('CALL PRC_CREATE_QUEUE_RECORD_INSERT catch SQLEXCEPTION');
		SET str_LOG_MSG_STR1 = CONCAT('p_QUEUE_NAME=', p_QUEUE_NAME);
		SET str_LOG_MSG_STR2 = CONCAT('NULL');
		CALL PRC_MY_LOG_INSERT(str_LOG_LEVEL, str_LOG_MSG_FUN, str_LOG_MSG_STR0, str_LOG_MSG_STR1, str_LOG_MSG_STR2);
		SET str_LOG_LEVEL = NULL;
		SET str_LOG_MSG_FUN = NULL;
		SET str_LOG_MSG_STR0 = NULL;
		SET str_LOG_MSG_STR1 = NULL;
		SET str_LOG_MSG_STR2 = NULL;
		
		COMMIT;
		
		resignal;
    END;

	/*
	end  error process
	*/

	-- str_COLUMN_NAME="QUEUE_NAME,QUEUE_TABLE,QUEUE_TYPE,OBJECT_NAME,SQL_CREATE_QUEUE_TABLES"
	 SET str_COLUMN_VALUE = CONCAT(
	'''', p_QUEUE_NAME, '''', ',',
	'''', p_QUEUE_TABLE, '''', ',',
	'''', p_QUEUE_TYPE, '''', ',',
	'''', p_OBJECT_NAME, '''', ',',
	'''', p_SQL_CREATE_QUEUE_TABLES, ''''
	);
	
	SET str_SQL_INSERT = FUNC_BASE_BUILD_SQL_INSERT(str_TABLE_NAME, str_COLUMN_NAME, str_COLUMN_VALUE);
	SET @G_SQL = NULL;
	SET @G_SQL = str_SQL_INSERT;
	
	-- insert data  
	PREPARE stmt_SQL FROM @G_SQL;
	EXECUTE stmt_SQL;
	DEALLOCATE PREPARE stmt_SQL;
	set @G_SQL = null;
	
END $$

DELIMITER ;

/*-----------------------------------------------------------------------------------------------------------*/








/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_AQ_SAMPLE_QUEUE_NAME_T_S_INSERT` $$

CREATE PROCEDURE `PRC_AQ_SAMPLE_QUEUE_NAME_T_S_INSERT`
(
	  IN p_QUEUE_NAME VARCHAR(256),
	  IN SUB_ID INT(5),
	  IN Q_NAME VARCHAR(128),
	  IN SUB_NAME VARCHAR(128),
	  IN SUB_ADDRESS VARCHAR(256)
)
/*
CALL PRC_AQ_SAMPLE_QUEUE_NAME_T_S_INSERT('AQ_SAMPLE_QUEUE_NAME', 2, 'SAMPLE_QUEUE_NAME', 'TRANSACT', 'TRANSACT_ADDRESS');
*/
BEGIN
	DECLARE str_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_SEQ_AQ_SAMPLE_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T    VARCHAR(128) DEFAULT NULL;	
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_I    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_S    VARCHAR(128) DEFAULT NULL;
	DECLARE str_DATABASE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_TABLE_NAME VARCHAR(256)	DEFAULT	NULL;
	DECLARE str_COLUMN_NAME VARCHAR(1024)	DEFAULT	"SUB_ID, Q_NAME, SUB_NAME, SUB_ADDRESS";
	DECLARE str_COLUMN_VALUE VARCHAR(8192)	DEFAULT	NULL;
	DECLARE str_SQL_INSERT VARCHAR(10240)	DEFAULT	NULL;
	
	SET str_QUEUE_NAME = p_QUEUE_NAME;
	CALL PRC_GET_QUEUE_INFO(str_QUEUE_NAME, str_SEQ_AQ_SAMPLE_QUEUE_NAME, str_AQ_SAMPLE_QUEUE_NAME_T, str_AQ_SAMPLE_QUEUE_NAME_T_I, str_AQ_SAMPLE_QUEUE_NAME_T_S);

	SET	str_DATABASE_NAME = UPPER(DATABASE());
	
	SET str_TABLE_NAME = str_AQ_SAMPLE_QUEUE_NAME_T_S;

	SET str_COLUMN_VALUE = CONCAT(
	SUB_ID, ',',
	'''', Q_NAME, '''', ',',
	'''', SUB_NAME, '''', ',',
	'''', SUB_ADDRESS, ''''
	);
	
	SET str_SQL_INSERT = FUNC_BASE_BUILD_SQL_INSERT(str_TABLE_NAME, str_COLUMN_NAME, str_COLUMN_VALUE);
	SET @G_SQL=NULL;
	SET @G_SQL=str_SQL_INSERT;
	
	-- insert data  
	PREPARE stmt_SQL FROM @G_SQL;
	EXECUTE stmt_SQL;
	DEALLOCATE PREPARE stmt_SQL;
	set @G_SQL = null;

END $$

DELIMITER ;
/*-----------------------------------------------------------------------------------------------------------*/





/*-----------------------------------------------------------------------------------------------------------*/
DELIMITER $$

DROP PROCEDURE IF EXISTS `PRC_AQ_SAMPLE_QUEUE_NAME_T_INSERT` $$

CREATE PROCEDURE `PRC_AQ_SAMPLE_QUEUE_NAME_T_INSERT`
(
	  IN p_usr_database_name      VARCHAR(128),
	  IN p_QUEUE_NAME VARCHAR(256),
      IN p_message_qualifier     VARCHAR(80),
      IN p_audit_data_Oracle     VARCHAR(2048),
      IN p_audit_data_MySQL      VARCHAR(2048),
      IN p_SUB_CNT         TINYINT(1)
)
/*
CALL PRC_AQ_SAMPLE_QUEUE_NAME_T_INSERT('AUDIT_DATA_QUEUE', 'PUBLIC', 'p_audit_data_Oracle', 'p_audit_data_MySQL', 1);
*/
BEGIN
	DECLARE str_USR_DATABASE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_SEQ_AQ_SAMPLE_QUEUE_NAME    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T    VARCHAR(128) DEFAULT NULL;	
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_I    VARCHAR(128) DEFAULT NULL;
	DECLARE str_AQ_SAMPLE_QUEUE_NAME_T_S    VARCHAR(128) DEFAULT NULL;
	DECLARE str_DATABASE_NAME VARCHAR(128) DEFAULT NULL;
	DECLARE str_TABLE_NAME VARCHAR(256)	DEFAULT	NULL;
	DECLARE str_COLUMN_NAME VARCHAR(1024)	DEFAULT	"Q_NAME,MSG_SEQ_ID,MSG_UUID,ENQ_TIME,ENQ_UID,SUB_CNT,DEQ_TIME,MSG_QUALIFER,ORALCE_SQL,MYSQL_SQL";
	DECLARE str_COLUMN_VALUE VARCHAR(8192)	DEFAULT	NULL;
	DECLARE str_SQL_INSERT VARCHAR(10240)	DEFAULT	NULL;
	
	DECLARE str_VALUE_Q_NAME VARCHAR(128) DEFAULT NULL;
	DECLARE n_VALUE_MSG_SEQ_ID DECIMAL(30,0) DEFAULT NULL;
	DECLARE str_VALUE_ENQ_UID VARCHAR(64)	DEFAULT	NULL;
	DECLARE n_VALUE_SUB_CNT tinyint(1) DEFAULT	NULL;
	DECLARE str_UUID_UP VARCHAR(128) DEFAULT NULL;
	
	DECLARE str_MESSAGE_QUALIFIER_VALUE     VARCHAR(80) DEFAULT NULL;
    DECLARE str_AUDIT_DATA_ORACLE_VALUE     VARCHAR(2048) DEFAULT NULL;
    DECLARE str_AUDIT_DATA_MYSQL_VALUE      VARCHAR(2048) DEFAULT NULL;
	
	SET str_QUEUE_NAME = p_QUEUE_NAME;
	SET	str_DATABASE_NAME = UPPER(DATABASE());
	CALL PRC_GET_QUEUE_INFO(str_QUEUE_NAME, str_SEQ_AQ_SAMPLE_QUEUE_NAME, str_AQ_SAMPLE_QUEUE_NAME_T, str_AQ_SAMPLE_QUEUE_NAME_T_I, str_AQ_SAMPLE_QUEUE_NAME_T_S);
	
	SET str_TABLE_NAME = str_AQ_SAMPLE_QUEUE_NAME_T;	
	SET str_VALUE_Q_NAME = str_QUEUE_NAME;
	SET n_VALUE_MSG_SEQ_ID = FUNC_SEQ_GET_NEXT_NUMBER(str_SEQ_AQ_SAMPLE_QUEUE_NAME);
	SET str_VALUE_ENQ_UID = str_DATABASE_NAME;
	SET n_VALUE_SUB_CNT = p_SUB_CNT;
	
	SET str_UUID_UP = CONCAT(UUID());
	SET str_UUID_UP = UCASE(str_UUID_UP);

	/*
	prcess   aaa'bbbb  aaa''bbbb 
	eg. select REPLACE('aaa''bbbb', '''', '''''') from dual;
	*/
	SET str_MESSAGE_QUALIFIER_VALUE = REPLACE(p_message_qualifier, '''', '''''');
	SET str_AUDIT_DATA_ORACLE_VALUE = REPLACE(p_audit_data_Oracle, '''', '''''');
	SET str_AUDIT_DATA_MYSQL_VALUE = REPLACE(p_audit_data_MySQL, '''', '''''');

	SET str_COLUMN_VALUE = CONCAT(
		'''', str_VALUE_Q_NAME, '''', ',',
		n_VALUE_MSG_SEQ_ID, ',',
		'''', str_UUID_UP, '''', ',',
		'''', now(), '''', ',',
		'''', str_VALUE_ENQ_UID, '''', ',',
		n_VALUE_SUB_CNT, ',',
		'NULL', ',',
		'''', str_MESSAGE_QUALIFIER_VALUE, '''', ',',
		'''', str_AUDIT_DATA_ORACLE_VALUE, '''', ',',
		'''', str_AUDIT_DATA_MYSQL_VALUE, ''''
		);
	
	SET str_SQL_INSERT = FUNC_BASE_BUILD_SQL_INSERT(str_TABLE_NAME, str_COLUMN_NAME, str_COLUMN_VALUE);
	SET @G_SQL = NULL;
	SET @G_SQL = str_SQL_INSERT;
	
	-- insert data  
	PREPARE stmt_SQL FROM @G_SQL;
	EXECUTE stmt_SQL;
	DEALLOCATE PREPARE stmt_SQL;
	set @G_SQL = null;

END $$

DELIMITER ;
/*-----------------------------------------------------------------------------------------------------------*/


