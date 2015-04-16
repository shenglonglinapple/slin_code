delimiter $$

DROP PROCEDURE IF EXISTS prc_parse_queue_msg $$
CREATE PROCEDURE prc_parse_queue_msg(
	IN      p_msg       VARCHAR(8000)
)
BEGIN
	DECLARE    v_beginPos            INT(10) DEFAULT 0;
	DECLARE    v_endPos              INT(10) DEFAULT 0;
	DECLARE    v_MySQLTagPos         INT(10) DEFAULT 0;
	DECLARE    v_OracleTagPos        INT(10) DEFAULT 0;
	DECLARE    v_equalTagPos         INT(10) DEFAULT 0;
	DECLARE    v_MySQLTagLen         INT(10) DEFAULT 0;
	DECLARE    v_OracleTagLen        INT(10) DEFAULT 0;
	DECLARE    v_sql_len             INT(10) DEFAULT 0;
	DECLARE    v_sql_len_char        VARCHAR(4) DEFAULT NULL;
	DECLARE    v_MySQLTag            VARCHAR(20) DEFAULT 'MySQL';
	DECLARE    v_OracleTag           VARCHAR(20) DEFAULT 'Oracle';
	DECLARE    v_EqualTag            VARCHAR(2)  DEFAULT '=';
	DECLARE    v_sql                 VARCHAR(3500) DEFAULT NULL;
	
	SET  v_MySQLTagLen  = CHAR_LENGTH(v_MySQLTag);
	SET  v_OracleTagLen = CHAR_LENGTH(v_OracleTag);
	SET  v_MySQLTagPos  = INSTR(p_msg, v_MySQLTag);	
	SET  v_OracleTagPos = INSTR(p_msg, v_OracleTag);
	SET  v_equalTagPos  = INSTR(p_msg, v_EqualTag);
	IF v_MySQLTagPos <> 0 AND v_OracleTagPos <> 0 THEN	 
		IF v_MySQLTagPos < v_OracleTagPos THEN 
		-- MySQL statement in front
			SET  v_beginPos = v_MySQLTagPos + v_MySQLTagLen;
			SET  v_sql_len_char = SUBSTR(p_msg, v_beginPos, v_equalTagPos - v_beginPos);
			SET  v_sql_len = CAST(v_sql_len_char AS UNSIGNED);		
			SET  v_sql = SUBSTR(p_msg, v_equalTagPos + 1, v_sql_len);
		ELSE
		-- Oracle statement in front
			SET  v_beginPos = v_OracleTagPos + v_OracleTagLen;
			SET  v_sql_len_char = SUBSTR(p_msg, v_beginPos, v_equalTagPos - v_beginPos);
			SET  v_sql_len = CAST(v_sql_len_char AS UNSIGNED);
			SET  v_beginPos = v_equalTagPos + v_sql_len + 1 + v_MySQLTagLen;
			SET  v_equalTagPos = LOCATE(v_EqualTag, p_msg, v_beginPos);
			SET  v_sql = SUBSTR(p_msg, v_equalTagPos + 1);		
			
		END IF;

    if v_sql is not null and v_sql <> '' then
		SET @g_sql = v_sql;
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
		end if;

	END IF;
	
END $$

delimiter $$

DROP PROCEDURE IF EXISTS prc_dequeue_audit_data $$
CREATE PROCEDURE prc_dequeue_audit_data(
	IN   p_location         VARCHAR(50)
)
 --  p_location : it's the database name of the location
 --  the global queue name for the system
 --  queue table: audit_data_queue
 --  queue name:  audit_data_queue
 --  enq table:  audit_data_queue_en
BEGIN
	
	DECLARE  v_no_more_rows        BOOLEAN  DEFAULT FALSE;
	DECLARE  v_msgid               VARCHAR(40) DEFAULT NULL;
	DECLARE  v_deq_msg             VARCHAR(8000) DEFAULT NULL;
	DECLARE  v_queue_table         VARCHAR(80) DEFAULT 'audit_data_queue_t';
	DECLARE  v_deq_options         TINYINT(1) DEFAULT 1;
	-- v_deq_options: 1 -- REMOVE_DATA;  2 -- REMOVE_NO_DATA;
	--                3 -- REMOVE_DELAY; 4 -- REMOVE_FIXED_TIME
	DECLARE  v_deq_delay_time      INT(10) DEFAULT 0;
  -- v_deq_delay_time: The message retention time, (in second).


	DECLARE cu_deq_data  CURSOR FOR
	SELECT MSGID, USER_DATA FROM audit_data_queue_t WHERE state = 1 and sub_cnt = 0 ORDER BY ENQ_HID, ENQ_LID ASC LIMIT 20000;

	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;

	#SET v_deq_options = 3;
	#SET v_deq_delay_time = 86400;

	OPEN cu_deq_data;
	the_deq_msg_loop: LOOP
		FETCH cu_deq_data INTO v_msgid, v_deq_msg;
		-- break out of the loop if
		-- 1) there were no records, or
		-- 2) we've processed them all
		IF v_no_more_rows THEN
			CLOSE cu_deq_data;
			LEAVE the_deq_msg_loop;
		END IF;
		
		#IF v_deq_msg IS NOT NULL AND v_msgid IS NOT NULL THEN
			CALL prc_parse_queue_msg(v_deq_msg);
      CALL prc_dequeue(v_queue_table, v_msgid, v_deq_options, v_deq_delay_time);
		#END IF;
	END LOOP the_deq_msg_loop;

  /*Usually.the p_deq_options will be set to 3 for debugging or test. So the sql of remove them have been
   put in the switch 'if then end if;' for avoiding to affect the performance. And there will be some delay and some trash data
   need to be removed manually after test.
  */
    IF v_deq_options = 3 then
        SET @g_sql = CONCAT('DELETE FROM ', v_queue_table, ' WHERE DEQ_TIME <= subdate(now(), interval ',v_deq_delay_time,' second) AND STATE = 3');
		    PREPARE stmt FROM @g_sql;
		    EXECUTE stmt;
		    DEALLOCATE PREPARE stmt;
        set @g_sql = null;
    END IF;

END $$

delimiter ;

delimiter $$

DROP PROCEDURE IF EXISTS prc_dequeue $$
CREATE PROCEDURE prc_dequeue(
	IN   p_queue_table   VARCHAR(50),
	IN   p_msgid         VARCHAR(40),
	IN   p_deq_options   TINYINT(1),
	IN   p_delay_time    INT(10)
)
--  p_deq_options: 1 -- REMOVE_DATA;  2 -- REMOVE_NO_DATA;
--			       3 -- REMOVE_DELAY; 4 -- REMOVE_FIXED_TIME
--  p_delay_time: The message retention time, (in second).
BEGIN

	DECLARE   v_enq_table        VARCHAR(80) DEFAULT NULL;	
	DECLARE   v_msg_state        TINYINT(1);   -- 1: ready; 2: processing; 3: remove_delay 4: done

	SET v_enq_table = CONCAT('aq_', p_queue_table, '_en');

/*
	SET @g_sql = CONCAT('DELETE FROM ', v_enq_table, ' WHERE MSGID = ', '''', p_msgid, '''');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
*/
Start transaction;
# the data of v_enq_table will be deleted by trigger 'que_bdr_trg' of queue_table
	IF p_deq_options = 1 THEN
			SET @g_sql = CONCAT('DELETE FROM ', p_queue_table, ' WHERE MSGID = ', '''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;


	ELSEIF p_deq_options = 2 THEN
      SET @g_sql = CONCAT('UPDATE ', p_queue_table, ' SET STATE = 4, DEQ_TIME = sysdate() WHERE MSGID = ', '''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;

	ELSEIF p_deq_options = 3 AND p_delay_time > 0 THEN
			SET @g_sql = CONCAT('UPDATE ', p_queue_table, ' SET STATE = 3, DEQ_TIME = sysdate() WHERE MSGID = ', '''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
  END IF;

	COMMIT;
	
END $$

delimiter ;