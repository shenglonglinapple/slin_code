/**/

DELIMITER $$

DROP FUNCTION IF EXISTS `FUNC_BASE_BUILD_SQL_DELETE` $$

CREATE FUNCTION `FUNC_BASE_BUILD_SQL_DELETE`
(
	p_TABLE_NAME VARCHAR(256),	
	p_WHERE_EXP VARCHAR(8192)
) 
RETURNS VARCHAR(10240)    
BEGIN
	DECLARE str_return_sql  VARCHAR(10240) DEFAULT NULL;
	DECLARE str_key_delete_from  VARCHAR(128) DEFAULT "DELETE FROM";
	DECLARE str_key_WHERE  VARCHAR(128) DEFAULT "WHERE";

	SET str_return_sql = CONCAT(
	' ', str_key_delete_from, ' ',
	' ', p_TABLE_NAME, ' ',
	' ', str_key_WHERE, ' ',
	' ', p_WHERE_EXP, ' '
	);

	RETURN str_return_sql;

END $$

DELIMITER ;

/**/



/**/
DELIMITER $$

DROP FUNCTION IF EXISTS `FUNC_BASE_BUILD_SQL_INSERT` $$

CREATE FUNCTION `FUNC_BASE_BUILD_SQL_INSERT`
(
	p_TABLE_NAME VARCHAR(256),
	p_COLUMN_NAME VARCHAR(1024),
	p_COLUMN_VALUE VARCHAR(8192)
) 
RETURNS VARCHAR(10240)    
BEGIN
	DECLARE str_return_sql  VARCHAR(10240) DEFAULT NULL;
	DECLARE str_key_insert_into  VARCHAR(128) DEFAULT "INSERT INTO";
	DECLARE str_key_VALUES  VARCHAR(128) DEFAULT "VALUES";

	SET str_return_sql = CONCAT(
	' ', str_key_insert_into, ' ',
	' ', p_TABLE_NAME, ' ',
	' ', '(', p_COLUMN_NAME, ')', ' ',
	' ', str_key_VALUES, ' ',
	' ', '(', p_COLUMN_VALUE, ')', ' '
	);

	RETURN str_return_sql;

END $$

DELIMITER ;

/**/






/**/
DELIMITER $$

DROP FUNCTION IF EXISTS `FUNC_BASE_BUILD_SQL_SELECT` $$

CREATE FUNCTION `FUNC_BASE_BUILD_SQL_SELECT`
(
	p_TABLE_NAME VARCHAR(256),
	p_COLUMN_NAME VARCHAR(1024),
	p_WHERE_EXP VARCHAR(8192)
) 
RETURNS VARCHAR(10240)    
BEGIN
	DECLARE str_return_sql  VARCHAR(10240) DEFAULT NULL;
	DECLARE str_key_select  VARCHAR(128) DEFAULT "SELECT";
	DECLARE str_key_from  VARCHAR(128) DEFAULT "FROM";
	DECLARE str_key_where  VARCHAR(128) DEFAULT "WHERE";

	SET str_return_sql = CONCAT(
	' ', str_key_select, ' ',
	' ', p_COLUMN_NAME, ' ',
	' ', str_key_from, ' ',
	' ', p_TABLE_NAME, ' ',
	' ', str_key_where, ' ',
	' ', p_WHERE_EXP, ' '
	);

	RETURN str_return_sql;

END $$

DELIMITER ;


/**/
DELIMITER $$

DROP FUNCTION IF EXISTS `FUNC_BASE_BUILD_SQL_UPDATE` $$

CREATE FUNCTION `FUNC_BASE_BUILD_SQL_UPDATE`
(
	p_TABLE_NAME VARCHAR(256),
	p_UPDATE_EXP VARCHAR(8192),
	p_WHERE_EXP VARCHAR(8192)
) 
RETURNS VARCHAR(10240)    
BEGIN
	DECLARE str_return_sql  VARCHAR(10240) DEFAULT NULL;
	DECLARE str_key_update  VARCHAR(128) DEFAULT "UPDATE";
	DECLARE str_key_set  VARCHAR(128) DEFAULT "SET";
	DECLARE str_key_where  VARCHAR(128) DEFAULT "WHERE";

	SET str_return_sql = CONCAT(
	' ', str_key_update, ' ',
	' ', p_TABLE_NAME, ' ',
	' ', str_key_set, ' ',
	' ', p_UPDATE_EXP, ' ',
	' ', str_key_where, ' ',
	' ', p_WHERE_EXP, ' '
	);

	RETURN str_return_sql;

END $$

DELIMITER ;


/**/













/**/
DELIMITER $$

DROP FUNCTION IF EXISTS `FUNC_SEQ_GET_NEXT_NUMBER` $$

CREATE FUNCTION `FUNC_SEQ_GET_NEXT_NUMBER`(
	p_SEQ_NAME VARCHAR(128)
) RETURNS DECIMAL(30,0)
    DETERMINISTIC
BEGIN
	/*
	FUNC_SEQ_GET_NEXT_NUMBER('MY_LOG_SEQ');
	FUNC_SEQ_GET_NEXT_NUMBER('AQ_AUDIT_DATA_QUEUE_SEQ');
	*/

	DECLARE n_SEQ_PKEY  INT(11);
	DECLARE str_SEQ_NAME  VARCHAR(30);
	DECLARE n_INIT_NUMBER  BIGINT(20);
	DECLARE n_LAST_NUMBER  DECIMAL(30,0);
	DECLARE n_MAX_NUMBER  DECIMAL(30,0);
	DECLARE n_INCREMENT_BY  INT(11);
	DECLARE ch_CYCLE_FLAG  VARCHAR(1);
	DECLARE n_RETURN_VALUE  DECIMAL(30,0);


    DECLARE cu_select_table CURSOR FOR
      SELECT SEQ_PKEY, SEQ_NAME, INIT_NUMBER, LAST_NUMBER, MAX_NUMBER, INCREMENT_BY, CYCLE_FLAG
        FROM ADM_SEQUENCE
       WHERE SEQ_NAME = TRIM(UPPER(p_SEQ_NAME));

	/*
	if CURSOR cu_select_table no data, open ok, fetch will throw exception.
	*/
    OPEN cu_select_table;
    FETCH cu_select_table
      INTO n_SEQ_PKEY, str_SEQ_NAME, n_INIT_NUMBER, n_LAST_NUMBER, n_MAX_NUMBER, n_INCREMENT_BY, ch_CYCLE_FLAG;
    CLOSE cu_select_table;



	UPDATE ADM_SEQUENCE
        SET LAST_NUMBER = last_insert_id(LAST_NUMBER + (INCREMENT_BY))
      WHERE SEQ_NAME = TRIM(UPPER(p_SEQ_NAME));

    SET n_LAST_NUMBER = last_insert_id();

    IF (
		(n_INCREMENT_BY > 0 AND n_LAST_NUMBER <= n_MAX_NUMBER) 
		OR (n_INCREMENT_BY < 0 AND n_LAST_NUMBER >= n_MAX_NUMBER) 
	   )
	THEN
		SET n_RETURN_VALUE = n_LAST_NUMBER;
		RETURN n_RETURN_VALUE;
    ELSEIF (UPPER(ch_CYCLE_FLAG) ='Y') 
	THEN
		UPDATE ADM_SEQUENCE SET LAST_NUMBER=n_INIT_NUMBER WHERE SEQ_NAME = TRIM(UPPER(p_SEQ_NAME));
		SET n_RETURN_VALUE = n_INIT_NUMBER;
		RETURN n_RETURN_VALUE;
    ELSE
	  /*
		throw one exception
	  */
      SELECT 1 INTO @1 FROM ERROR_TABLE_FOR_THORW_MY_EXCEPTION_func_seq_get_next_number;
    END if;


END $$

DELIMITER ;


/**/









