DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dequeue` $$
CREATE PROCEDURE  `prc_dequeue`(
	IN      	      p_queue             VARCHAR(80),
	IN      	      p_consumer      	  VARCHAR(80),
	IN      	      p_deqmode       	  TINYINT(1),
	IN      	      p_deqnavigation     TINYINT(1),
  INOUT           p_msgid             VARCHAR(38),
  OUT             p_payload           VARCHAR(8080) )

BEGIN

  DECLARE v_queue_name VARCHAR(50) DEFAULT UPPER(p_queue);
  declare v_sub_table VARCHAR(80) DEFAULT NULL;
  declare v_dis_table VARCHAR(80) DEFAULT NULL;
  declare v_queue_table VARCHAR(80) DEFAULT NULL;

	SET v_sub_table = CONCAT('AQ_', v_queue_name, '_T_S');
	SET v_dis_table = CONCAT('AQ_', v_queue_name, '_T_I');
  SET v_queue_table = CONCAT(v_queue_name, '_T');
  SET @sv_user_data = null;
  SET @sv_msgid = null;
  SET @sv_msg_sid = null;

  -- SET @sv_next_mess_sid = null; This user variable need to be init to 'null' at the above level of this procedure.

  -- First, get value.
  IF p_msgid is not null then

      SET @g_sql = CONCAT('SELECT USER_DATA into @sv_user_data FROM ', v_queue_table,
       ' WHERE MSGID = (SELECT MSGID FROM ', v_dis_table, ' WHERE SUB_NAME = UPPER(''' ,p_consumer,
       ''')  AND state = 1 AND MSGID = ''',p_msgid,''')');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;

      set p_payload = @sv_user_data;
  ELSE

 --   IF p_deqnavigation = 1 then


      SET @g_sql = CONCAT('SELECT MSG_SID, MSGID, USER_DATA into @sv_msg_sid, @sv_msgid, @sv_user_data FROM ',
      v_queue_table,' WHERE MSGID = (SELECT MSGID FROM ',v_dis_table, ' WHERE SUB_NAME = UPPER(''' ,p_consumer,
       ''')  AND state = 1 ORDER BY MSG_SID ASC LIMIT 1)');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;

    IF p_deqnavigation = 2 then
      if @sv_next_mess_sid is null then
        set @sv_next_mess_sid = @sv_msg_sid;
      else
        SET @sv_next_mess_sid=@sv_next_mess_sid+1;
      end if;
	  
      SET @g_sql = CONCAT('SELECT MSGID, USER_DATA into @sv_msgid, @sv_user_data FROM ',
      v_queue_table,' WHERE msg_sid = ',@sv_next_mess_sid);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
	  
    END IF;

      set p_msgid = @sv_msgid;
      set p_payload = @sv_user_data;
  END iF;

  -- Then, 'remove/update'.

  Start transaction;

    IF p_deqmode = 3 then

      SET @g_sql = CONCAT('UPDATE ', v_dis_table, ' SET STATE = 4 WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;

/*
      SET @g_sql = CONCAT('UPDATE ', v_queue_table, ' SET STATE = 4 WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
*/
    ELSEIF p_deqmode = 1 then

      SET @g_sql = CONCAT('DELETE FROM ', v_dis_table, ' WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
/*
      SET @g_sql = CONCAT('DELETE FROM ', v_queue_table, ' WHERE msgid = ''', p_msgid, '''');
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
*/
    END IF;

END $$

DELIMITER ;