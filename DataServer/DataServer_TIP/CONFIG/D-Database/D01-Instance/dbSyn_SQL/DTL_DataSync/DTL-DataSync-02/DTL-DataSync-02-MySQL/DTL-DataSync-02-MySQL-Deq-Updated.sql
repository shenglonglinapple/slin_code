delimiter $$

DROP PROCEDURE IF EXISTS prc_dequeue_delay $$
CREATE PROCEDURE prc_dequeue_delay(p_queue_table VARCHAR(80),
                                   p_enq_table VARCHAR(80),
                                   p_deq_delay_time INT(10))
BEGIN

declare lv_deq_exp_time datetime;

        set lv_deq_exp_time = subdate(now(),interval p_deq_delay_time second);
  /*Usually.the p_deq_options will be set to 3 only for debugging or test. So the removing sql have been
   put in the switch 'if then end if;' for avoiding to affect the performance. 
  */
        SET @g_sql = CONCAT('DELETE FROM ', p_enq_table, ' WHERE MSGID in (select msgid from ',p_queue_table,
                           ' where DEQ_TIME <= str_to_date(''',lv_deq_exp_time,''',''%Y-%m-%d %H:%i:%s'') AND STATE = 3)');
		    PREPARE stmt FROM @g_sql;
		    EXECUTE stmt;
		    DEALLOCATE PREPARE stmt;
        set @g_sql = null;

        SET @g_sql = CONCAT('DELETE FROM ', p_queue_table, ' where DEQ_TIME <= str_to_date(''',lv_deq_exp_time,''',''%Y-%m-%d %H:%i:%s'') AND STATE = 3');
		    PREPARE stmt FROM @g_sql;
		    EXECUTE stmt;
		    DEALLOCATE PREPARE stmt;
        set @g_sql = null;

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
  DECLARE   v_hlid_begin       BIGINT(20);
  DECLARE   v_hlid_end         BIGINT(20);

	SET v_enq_table = CONCAT('aq_', p_queue_table, '_en');
  SET v_hlid_begin = CONCAT(p_hid,p_lid_begin);
  SET v_hlid_end = CONCAT(p_hid,p_lid_end);
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
                   ''' and enq_hlid between ', v_hlid_begin, ' and ',v_hlid_end);
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
                   ''' and enq_hlid between ', v_hlid_begin, ' and ',v_hlid_end);
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
                   ''' and enq_hlid between ', v_hlid_begin, ' and ',v_hlid_end);
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
	DECLARE  v_enq_table		 VARCHAR(80) DEFAULT CONCAT('aq_', v_queue_table, '_en');
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
      #CALL prc_dequeue(v_queue_table, v_msgid, v_deq_options, v_deq_delay_time);
      CALL prc_dequeue(v_queue_table, v_msgid, null, null, null, v_deq_options, v_deq_delay_time, 0, null);

		#END IF;
	END LOOP the_deq_msg_loop;

  if v_deq_options = 3 then
 	  call prc_dequeue_delay(v_queue_table, v_enq_table, v_deq_delay_time);
  end if;

END $$

delimiter ;
