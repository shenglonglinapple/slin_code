
DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dequeue` $$
CREATE PROCEDURE  `prc_dequeue`(
	IN      	      p_queue             VARCHAR(80),
	IN      	      p_consumer      	  VARCHAR(80),
	IN      	      p_deqmode       	  TINYINT(1),
	IN      	      p_deqnavigation     TINYINT(1),
  INOUT           p_msgid             VARCHAR(38),
  OUT             p_payload_1           VARCHAR(4000),
  OUT             p_payload_2           VARCHAR(4000),
  OUT             p_payload_3           VARCHAR(4000)
  )

BEGIN

	DECLARE v_queue_name VARCHAR(50) DEFAULT UPPER(p_queue);
	declare v_sub_table VARCHAR(80) DEFAULT NULL;
	declare v_dis_table VARCHAR(80) DEFAULT NULL;
	declare v_queue_table VARCHAR(80) DEFAULT NULL;
	declare v_deq_state TINYINT(1);
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
      ROLLBACK;
	  resignal;
	END;  

	select deq_state into v_deq_state from aq_sys_queue_m where upper(q_name) = v_queue_name;
	
IF 	v_deq_state = 1 then
		SIGNAL SQLSTATE '46001'
			SET MESSAGE_TEXT = 'The dequeue is disable.';
ELSEIF v_deq_state = 0 then
	SET v_sub_table = CONCAT('AQ_', v_queue_name, '_T_S');
	SET v_dis_table = CONCAT('AQ_', v_queue_name, '_T_I');
	SET v_queue_table = CONCAT(v_queue_name, '_T');
	SET @sv_user_data = null;
	SET @sv_msgid = null;
	SET @sv_msg_sid = null;

  -- SET @sv_next_mess_sid = null; This user variable need to be init to 'null' at the above level of this procedure.

  -- First, get value.
  IF p_msgid <> '' then

	  if p_consumer <> '' then
	  	SET @g_sql = CONCAT('SELECT USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ', v_queue_table,
         ' WHERE MSGID = (SELECT MSGID FROM ', v_dis_table, ' WHERE SUB_NAME = UPPER(''' ,p_consumer,
         ''')  AND state = 1 AND MSGID = ''',p_msgid,''')');
			    PREPARE stmt FROM @g_sql;
			    EXECUTE stmt;
			    DEALLOCATE PREPARE stmt;
      set @g_sql = null;
	  else
      SET @g_sql = CONCAT('SELECT USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ', v_queue_table,
         ' WHERE sub_cnt = 0 and state=1 and MSGID = ''',p_msgid,'''');
		    	PREPARE stmt FROM @g_sql;
		    	EXECUTE stmt;
			    DEALLOCATE PREPARE stmt;
		  set @g_sql = null;
  	end if;
		
		set p_payload_1 = @sv_user_data_1;
		set p_payload_2 = @sv_user_data_2;
		set p_payload_3 = @sv_user_data_3;

  ELSE

     --   IF p_deqnavigation = 1 then
    
    	if p_consumer <> '' then
    		SET @g_sql = CONCAT('SELECT MSG_SID, MSGID, USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_msg_sid, @sv_msgid, @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ',
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
    
    /*	
    			SET @g_sql = CONCAT('SELECT MSGID, USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_msgid, @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ',
    			v_queue_table,' WHERE msg_sid = ',@sv_next_mess_sid);
    */
    			SET @g_sql = CONCAT('SELECT MSG_SID, MSGID, USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_msg_sid, @sv_msgid, @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ',
    			v_queue_table,' WHERE MSGID = (SELECT MSGID FROM ',v_dis_table, ' WHERE SUB_NAME = UPPER(''' ,p_consumer,
    			''')  AND state = 1 and msg_id > @sv_next_mess_sid ORDER BY MSG_SID ASC LIMIT 1)');	  
    				PREPARE stmt FROM @g_sql;
    				EXECUTE stmt;
    				DEALLOCATE PREPARE stmt;
    				set @g_sql = null;
    
    		END IF;
    
    	else
    
    		SET @g_sql = CONCAT('SELECT MSG_SID, MSGID, USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_msg_sid, @sv_msgid, @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ',
    		v_queue_table,' WHERE sub_cnt = 0 AND state = 1 ORDER BY MSG_SID ASC LIMIT 1');
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
    	
    			SET @g_sql = CONCAT('SELECT MSG_SID, MSGID, USER_DATA_1, USER_DATA_2, USER_DATA_3 into @sv_msg_sid, @sv_msgid, @sv_user_data_1,@sv_user_data_2,@sv_user_data_3 FROM ',
    			v_queue_table,' WHERE sub_cnt = 0 AND state = 1 and msg_id > @sv_next_mess_sid ORDER BY MSG_SID ASC LIMIT 1');	  
    				PREPARE stmt FROM @g_sql;
    				EXECUTE stmt;
    				DEALLOCATE PREPARE stmt;
    				set @g_sql = null;
    	  
    		END IF;
    	end if;
	
      set p_msgid = @sv_msgid;
      set p_payload_1 = @sv_user_data_1;
	  set p_payload_2 = @sv_user_data_2;
	  set p_payload_3 = @sv_user_data_3;
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
END if; -- v_deq_state 0 or 1
END $$

DELIMITER ;