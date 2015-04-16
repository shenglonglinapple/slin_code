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
# 07June2012 will for handling duplicate entry error.
	DECLARE CONTINUE HANDLER FOR 1062 begin end;
	
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

delimiter ;

DELIMITER $$
DROP PROCEDURE IF EXISTS prc_dequeue $$
CREATE PROCEDURE prc_dequeue(
	IN   p_queue_table   VARCHAR(50),
	IN   p_msgid         VARCHAR(40),
  IN   p_hid           INT(10) unsigned,
  IN   p_lid_begin           INT(10) unsigned,
  IN   p_lid_end       INT(10) unsigned,
	IN   p_deq_options   TINYINT(1),
	IN   p_delay_time    INT(10),
  IN   p_sub_cnt       TINYINT(1),
  IN   p_subscriber    VARCHAR(30)
)

BEGIN
--  p_deq_options: 1 -- REMOVE_DATA;  2 -- REMOVE_NO_DATA;
--			       3 -- REMOVE_DELAY; 4 -- REMOVE_FIXED_TIME
--  p_delay_time: The message retention time, (in second).
	DECLARE   v_enq_table        VARCHAR(80) DEFAULT NULL;	
	DECLARE   v_msg_state        TINYINT(1);   -- 1: ready; 2: processing; 3: remove_delay 4: done
  #DECLARE   v_hlid_begin       BIGINT(20);
  #DECLARE   v_hlid_end         BIGINT(20);

	SET v_enq_table = CONCAT('aq_', p_queue_table, '_en');
  #SET v_hlid_begin = CONCAT(p_hid,p_lid_begin);
  #SET v_hlid_end = CONCAT(p_hid,p_lid_end);
/*
	SET @g_sql = CONCAT('DELETE FROM ', v_enq_table, ' WHERE MSGID = ', '''', p_msgid, '''');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
*/
#Start transaction;



	IF p_deq_options = 1 THEN
    IF p_sub_cnt >= 1 then
			SET @g_sql = CONCAT('DELETE FROM ', v_enq_table, ' WHERE sub_name = ''', p_subscriber,
                   ''' and enq_hid = ', p_hid, ' and enq_lid between ', p_lid_begin, ' and ',p_lid_end);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    else
			SET @g_sql = CONCAT('DELETE FROM ', v_enq_table, ' WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    end if;


	ELSEIF p_deq_options = 2 THEN
    IF p_sub_cnt >= 1 then
      SET @g_sql = CONCAT('UPDATE ', v_enq_table, ' SET STATE = 4  WHERE sub_name = ''', p_subscriber,
                   ''' and enq_hid = ', p_hid, ' and enq_lid between ', p_lid_begin, ' and ',p_lid_end);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    else
      SET @g_sql = CONCAT('UPDATE ', v_enq_table, ' SET STATE = 4 WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    end if;

	ELSEIF p_deq_options = 3 AND p_delay_time > 0 THEN
    IF p_sub_cnt >= 1 then
			SET @g_sql = CONCAT('UPDATE ', v_enq_table, ' SET STATE = 3 WHERE sub_name = ''', p_subscriber,
                   ''' and enq_hid = ', p_hid, ' and enq_lid between ', p_lid_begin, ' and ',p_lid_end);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    else
			SET @g_sql = CONCAT('UPDATE ', v_enq_table, ' SET STATE = 3 WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
    end if;

  END IF;

#	COMMIT;
	
END $$

delimiter ;

