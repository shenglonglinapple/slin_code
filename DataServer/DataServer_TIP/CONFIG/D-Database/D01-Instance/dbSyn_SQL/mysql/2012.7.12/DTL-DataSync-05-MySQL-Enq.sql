DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enq_table` $$
CREATE  PROCEDURE `prc_enq_table`(
  IN   p_queue_table     VARCHAR(80),
  IN   p_msgid           VARCHAR(38),
  IN   p_subname         VARCHAR(80),
  IN   p_hid            INT(10) unsigned,
  IN   p_lid            INT(10) unsigned  )
BEGIN
	#DECLARE  v_hid            INT(10) unsigned;
	#DECLARE  v_lid            INT(10) unsigned;
	#DECLARE  v_maxInt       	INT(10) unsigned DEFAULT 4294967290;
	#DECLARE  v_step               TINYINT(1) DEFAULT 1;
	DECLARE  v_sub_id             INT(5) DEFAULT 0;
	DECLARE  v_enq_table          VARCHAR(80) DEFAULT NULL;
	DECLARE  v_sub_table          VARCHAR(80) DEFAULT 'recipient';
	DECLARE  v_aq_prefix          VARCHAR(5) DEFAULT 'aq_';
	DECLARE  v_subname            VARCHAR(80) DEFAULT NULL;
	DECLARE  v_no_more_rows       BOOLEAN DEFAULT FALSE;
	DECLARE  v_bErr               BOOLEAN DEFAULT FALSE;

	DECLARE cu_sub_id CURSOR FOR
    SELECT PKEY FROM recipient_info WHERE UPPER(NAME) = UPPER(p_subname);
# will	SELECT PKEY FROM recipient WHERE UPPER(NAME) = UPPER(p_subname);
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;
# MOVED here --will
	DECLARE CONTINUE HANDLER FOR 1062
		SET v_bErr = TRUE;

	SET v_enq_table = CONCAT(v_aq_prefix, p_queue_table, '_en');
	SET v_subname   = UPPER(p_subname);
#	SET @g_maxtid   = NULL;

	OPEN cu_sub_id;
	FETCH cu_sub_id INTO v_sub_id;
	IF v_no_more_rows THEN
		CLOSE cu_sub_id;
	ELSE
		CLOSE cu_sub_id;
	END IF;

/*
      set v_lid = func_seq_get_next_number('AQ_ENQ_LID_SEQ');
		IF(v_lid = v_maxInt) THEN
			SET v_hid = func_seq_get_next_number('AQ_ENQ_HID_SEQ');
			set v_lid = func_seq_get_next_number('AQ_ENQ_LID_SEQ');
		ELSE
			SET v_hid = func_seq_get_curr_number('AQ_ENQ_HID_SEQ');
		END IF;
*/
  /*
	SET @g_sql = CONCAT('SELECT enq_tid INTO @g_maxtid FROM ', v_enq_table, ' WHERE UPPER(SUB_NAME) = ', '''',v_subname,'''', ' ORDER BY ENQ_TID DESC LIMIT 1' );
	PREPARE stmt2 FROM @g_sql;
	EXECUTE stmt2;
	DEALLOCATE PREPARE stmt2;
  set @g_sql=null;

	IF @g_maxtid IS NULL THEN
		SET v_enq_tid = v_step;
	ELSE
		SET v_enq_tid = @g_maxtid + v_step;
	END IF;
  */
	SET @g_sql = CONCAT('INSERT INTO ', v_enq_table, '(SUB_ID,SUB_NAME,ENQ_HID,ENQ_LID,MSGID,STATE) VALUES (', v_sub_id,',', '''',v_subname,'''', ',',p_hid,',',p_lid,',''',p_msgid,'''',',1)');
	PREPARE stmt3 FROM @g_sql;
	EXECUTE stmt3;
	DEALLOCATE PREPARE stmt3;
  set @g_sql=null;

 END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enq_others` $$
CREATE  PROCEDURE `prc_enq_others`(
	IN   p_location        VARCHAR(80),
  IN   p_queue_table     VARCHAR(80),
  IN   p_msg_identifier  VARCHAR(80),
  IN   p_msgid           VARCHAR(38),
  IN   p_sub_cnt         TINYINT(1),
  IN   p_center_db       VARCHAR(80),
  IN   p_hid           	INT(10) unsigned,
  IN   p_lid           	INT(10) unsigned)
BEGIN	
	DECLARE  v_local_db           VARCHAR(80) DEFAULT NULL;
#	DECLARE  v_bErr               BOOLEAN DEFAULT FALSE;
#	DECLARE  v_center_tag         VARCHAR(30) DEFAULT  'CENTER';
#	DECLARE  v_subtypelocal 	  TINYINT(1) DEFAULT 1;
	DECLARE  v_no_more_row        BOOLEAN DEFAULT FALSE;
	DECLARE  v_group_mem          VARCHAR(80) DEFAULT NULL;

# will
	DECLARE  v_public_mem          VARCHAR(80) DEFAULT NULL;
	DECLARE  v_other_mem          VARCHAR(80) DEFAULT NULL;
	DECLARE  v_other_location     VARCHAR(80) DEFAULT NULL;

	DECLARE c_public_mem  CURSOR FOR
	SELECT DISTINCT name FROM recipient WHERE address is not null and status = 0;

#  DECLARE c_group_mem  CURSOR FOR
#	SELECT DISTINCT MEMBER FROM recipient_group WHERE UPPER(NAME) = UPPER(DATABASE()) AND UPPER(NAME) <> UPPER(MEMBER);
  DECLARE c_group_mem  CURSOR FOR
	SELECT DISTINCT MEMBER FROM recipient_group WHERE UPPER(NAME) = UPPER(p_location) AND UPPER(member) <> UPPER(database()) and status = 0;

	DECLARE c_other_mem  CURSOR FOR
	SELECT DISTINCT name FROM recipient WHERE upper(name) = v_other_location and address is not null and status = 0;

/* will
	DECLARE CONTINUE HANDLER FOR 1062
		SET v_bErr = TRUE;
*/
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_row = TRUE;

	IF(p_sub_cnt = 0) THEN
	-- the message received from remote and the receiver is the local self.
	-- enq one message only
		SET v_local_db = DATABASE();
		CALL prc_enq_table(p_queue_table, p_msgid, v_local_db, p_hid, p_lid);
	ELSE
	-- the local apps enq message and need to send to remote location(s)
	-- check the msg_identifier, should only be (INSERT OR GROUP)

      IF upper(p_msg_identifier) = 'GROUP' THEN
			  OPEN c_group_mem;
			  the_group_mem_loop: LOOP
			  	FETCH c_group_mem INTO v_group_mem;
			  	-- break out of the loop if
			  	-- 1) there were no records, or
			  	-- 2) we've processed them all
			  	IF v_no_more_row THEN
			  		CLOSE c_group_mem ;
			  		LEAVE the_group_mem_loop ;
			  	END IF;
			  	CALL prc_enq_table(p_queue_table, p_msgid, v_group_mem, p_hid, p_lid);
		  	END LOOP the_group_mem_loop;

      ELSEIF upper(p_msg_identifier) = 'PUBLIC' THEN
			  OPEN c_public_mem;
			  the_public_mem_loop: LOOP
			  	FETCH c_public_mem INTO v_public_mem;
			  	IF v_no_more_row THEN
			  		CLOSE c_public_mem ;
			  		LEAVE the_public_mem_loop ;
			  	END IF;
  			CALL prc_enq_table(p_queue_table, p_msgid, v_public_mem, p_hid, p_lid);
		  	END LOOP the_public_mem_loop;

      ELSEIF upper(p_msg_identifier) in ('INSERT', 'UPDATE', 'DELETE') THEN
          IF v_local_db = p_center_db THEN
             set v_other_location = p_location;
          ELSE
             set v_other_location = p_center_db;
          END IF;

			  OPEN c_other_mem;
			  the_other_mem_loop: LOOP
			  	FETCH c_other_mem INTO v_other_mem;
			  	IF v_no_more_row THEN
			  		CLOSE c_other_mem ;
			  		LEAVE the_other_mem_loop ;
			  	END IF;
  			CALL prc_enq_table(p_queue_table, p_msgid, v_other_mem, p_hid, p_lid);
		  	END LOOP the_other_mem_loop;

      ELSEIF upper(p_msg_identifier) = 'MMS' THEN
  			CALL prc_enq_table(p_queue_table, p_msgid, p_center_db, p_hid, p_lid);

      END IF;


		/*IF (STRCMP(p_msg_identifier, v_center_tag) = 0) THEN

		-- only propagate to center database
			CALL prc_enq_table(p_queue_table, p_msgid, p_center_db);
		ELSE

		-- PUBLIC propagate only can distrubuted by center Oracle database.
			OPEN c_group_mem;
			the_group_mem_loop: LOOP
				FETCH c_group_mem INTO v_group_mem;
				-- break out of the loop if
				-- 1) there were no records, or
				-- 2) we've processed them all
				IF v_no_more_row THEN
					CLOSE c_group_mem ;
					LEAVE the_group_mem_loop ;
				END IF;
				CALL prc_enq_table(p_queue_table, p_msgid, v_group_mem);
			END LOOP the_group_mem_loop;
		END IF;*/
	END IF;
	
  END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enqueue` $$
CREATE  PROCEDURE `prc_enqueue`(
	IN   p_location        VARCHAR(80),
  IN   p_queue           VARCHAR(80),
  IN   p_msg_identifier  VARCHAR(80),
  IN   p_payload         VARCHAR(7000),
  IN   p_msgid           VARCHAR(38),
  #IN   p_subtype         TINYINT(1),
  IN   p_center_db       VARCHAR(80),
  IN   p_sub_cnt         TINYINT(1)  )
BEGIN

	DECLARE  v_hid          	INT(10) unsigned;
	DECLARE  v_lid          	INT(10) unsigned;
	#DECLARE  v_hlid          	BIGINT(20) unsigned;
	DECLARE  v_step         	TINYINT(1) DEFAULT 1;
	DECLARE  v_priority     	TINYINT(1) DEFAULT 1;
	DECLARE  v_state        	TINYINT(1) DEFAULT 1;         # 1: ready; 2: processing; 3: remove_delay 4: done
	DECLARE  v_maxInt       	INT(10) unsigned DEFAULT 4294967290;
	DECLARE  v_msgid        	VARCHAR(38) DEFAULT NULL;
	DECLARE  v_queue_name   	VARCHAR(80) DEFAULT NULL;
	DECLARE  v_queue_table      VARCHAR(80) DEFAULT NULL;
	DECLARE  v_curuser_deli     VARCHAR(3) DEFAULT '@';
	DECLARE  v_sender_msgid     VARCHAR(38) DEFAULT NULL;
	DECLARE  v_no_more_rows    	BOOLEAN  DEFAULT FALSE;
	DECLARE  v_bWarn            BOOLEAN  DEFAULT FALSE;
	DECLARE  v_bTempTable       BOOLEAN  DEFAULT FALSE;
	DECLARE  v_msg_data         VARCHAR(7000) DEFAULT NULL;

	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;
	DECLARE EXIT HANDLER FOR SQLSTATE '40001'
    Begin
      ROLLBACK;
      resignal;
    end;
	DECLARE EXIT HANDLER FOR SQLSTATE 'XA102'
    Begin
      ROLLBACK;
      resignal;
    end;

	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    Begin
      ROLLBACK;
      INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
      VALUES(func_seq_get_next_number('ERRLOG_SEQ'), concat(p_msg_identifier,'@',substr(p_payload,1,3500)),concat('Exception! SQLEXCEPTION of prc_enqueue at: ',DATABASE(), ', and para is: ',p_location),SYSDATE());
    end;


	DECLARE CONTINUE HANDLER FOR SQLWARNING
		SET v_bWarn = TRUE;
	DECLARE CONTINUE HANDLER FOR 1062 begin end;


/*
	SET @g_sender_msgid = NULL;
	IF CHAR_LENGTH(p_msgid) > 0 THEN
		SET @g_sql = CONCAT('SELECT DISTINCT SENDER_MSGID INTO @g_sender_msgid FROM ', p_queue_table, ' WHERE SENDER_MSGID = ', '''',p_msgid,'''');
		PREPARE stmt2 FROM @g_sql;
		EXECUTE stmt2;
		DEALLOCATE PREPARE stmt2;
	END IF;
*/
#	IF @g_sender_msgid IS NULL THEN
/*
		SET @g_maxhid = NULL;
		SET @g_maxlid = NULL;
		SET @g_sql = CONCAT('SELECT enq_hid INTO @g_maxhid FROM ', p_queue_table, ' ORDER BY ENQ_HID DESC LIMIT 1');
		PREPARE stmt1 FROM @g_sql;
		EXECUTE stmt1;
		DEALLOCATE PREPARE stmt1;
		SET @g_sql = CONCAT('SELECT enq_lid INTO @g_maxlid FROM ', p_queue_table, ' WHERE enq_hid = @g_maxhid ORDER BY ENQ_LID DESC LIMIT 1');
		PREPARE stmt2 FROM @g_sql;
		EXECUTE stmt2;
		DEALLOCATE PREPARE stmt2;

		IF @g_maxhid IS NULL OR @g_maxlid IS NULL THEN
			SET @g_maxhid = 0;
			SET @g_maxlid = 0;
		END IF;
*/
start transaction;
    set v_lid = func_seq_get_next_number('AQ_LID_SEQ');
		IF(v_lid = v_maxInt) THEN
			SET v_hid = func_seq_get_next_number('AQ_HID_SEQ');
			set v_lid = func_seq_get_next_number('AQ_LID_SEQ');
		ELSE
			SET v_hid = func_seq_get_curr_number('AQ_HID_SEQ');
		END IF;

		SET v_queue_name = upper(p_queue);
		SET v_queue_table = concat(v_queue_name,'_t');
		SET v_msgid      = UUID();
		SET v_msg_data   = REPLACE(p_payload, '''', '''''');

    #SET v_hlid = concat(v_hid,v_lid);
		CALL prc_enq_others(p_location, v_queue_table, p_msg_identifier, v_msgid, p_sub_cnt, p_center_db, v_hid, v_lid);


    if p_msgid = '' or p_msgid is null then
        SET @g_sql = CONCAT('INSERT INTO ', v_queue_table, '(Q_NAME, ENQ_HID, ENQ_LID, MSGID, PRIORITY, STATE, SUB_CNT, ENQ_TIME, ENQ_UID, SENDER_MSGID, USER_DATA) VALUES (',
							'''', v_queue_name, '''', ',', v_hid, ',', v_lid, ',','''',v_msgid,'''' ,',', v_priority, ',', v_state,',', p_sub_cnt, ', sysdate(),SUBSTRING_INDEX(CURRENT_USER, ', '''',v_curuser_deli,'''', ',1),',
							'NULL',',' ,'''', v_msg_data, '''',')');
    else
		    SET @g_sql = CONCAT('INSERT INTO ', v_queue_table, '(Q_NAME, ENQ_HID, ENQ_LID, MSGID, PRIORITY, STATE, SUB_CNT, ENQ_TIME, ENQ_UID, SENDER_MSGID, USER_DATA) VALUES (',
							'''', v_queue_name, '''', ',', v_hid, ',', v_lid, ',','''',v_msgid,'''' ,',', v_priority, ',', v_state,',', p_sub_cnt, ', sysdate(),SUBSTRING_INDEX(CURRENT_USER, ', '''',v_curuser_deli,'''', ',1),',
							'''', p_msgid,'''',',' ,'''', v_msg_data, '''',')');
    end if;

		PREPARE stmt3 FROM @g_sql;
		EXECUTE stmt3;
		DEALLOCATE PREPARE stmt3;
    set @g_sql = null;

#	END IF;
	
	COMMIT;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enqueue_audit_data` $$
CREATE  PROCEDURE `prc_enqueue_audit_data`(
	IN p_location              VARCHAR(80),
	IN p_message_qualifier     VARCHAR(80),
	IN p_audit_data_Oracle     VARCHAR(4000),
  IN p_audit_data_MySQL      VARCHAR(4000) )
BEGIN

	DECLARE    v_queue         VARCHAR(30) DEFAULT  'audit_data_queue';
/*  DECLARE    v_mms_queue   VARCHAR(30) DEFAULT  'mms_data_queue';
  DECLARE    v_que_name      VARCHAR(30);
*/
	DECLARE    v_centre_db           VARCHAR(80) DEFAULT  'TRANSACT';
	#DECLARE    v_subType             TINYINT(1) DEFAULT  2;
	DECLARE    v_payload             VARCHAR(7000) DEFAULT NULL;
	DECLARE    v_audit_data_Oracle   VARCHAR(4000) DEFAULT NULL;
	DECLARE    v_audit_data_MySQL    VARCHAR(4000) DEFAULT NULL;
	DECLARE    v_message_qualifier   VARCHAR(80) DEFAULT NULL;
	DECLARE    v_oracle_dml_len      INT(5) DEFAULT 0;
	DECLARE    v_mysql_dml_len       INT(5) DEFAULT 0;
	DECLARE    v_pub_cnt             INT(5) DEFAULT 1;
	DECLARE    v_grp_cnt             INT(5) DEFAULT 1;
	DECLARE    v_oth_cnt             INT(5) DEFAULT 1;
	DECLARE    v_qua_chk             TINYINT(1) DEFAULT 1;
	DECLARE    v_sub_cnt             TINYINT(1) DEFAULT 1;
	#DECLARE    v_sub_mem             VARCHAR(80) DEFAULT NULL;

	DECLARE CONTINUE HANDLER FOR 1062 begin end;

  if  upper(p_message_qualifier) = 'PUBLIC' then
    select count(*) into v_pub_cnt from recipient where address is not null and name <> database() and status = 0;
      if v_pub_cnt > 1 THEN
         set v_sub_cnt = 2;
      end if;
  elseif upper(p_message_qualifier) = 'GROUP' then
    select count(*) into v_grp_cnt from recipient_group where UPPER(NAME) = UPPER(p_location) AND UPPER(member) <> UPPER(database()) and status = 0;
      if v_grp_cnt > 1 THEN
         set v_sub_cnt = 2;
      end if;
  elseif upper(p_message_qualifier) in ('INSERT', 'UPDATE', 'DELETE') then
    select count(*) into v_oth_cnt from recipient WHERE address is not null and name <> database() and status = 0;
      if v_oth_cnt > 1 THEN
         set v_sub_cnt = 2;
      end if;
  elseif upper(p_message_qualifier) in ('MMS') then
      begin end;

  ELSE
    set v_qua_chk = 0;
    INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
      VALUES(func_seq_get_next_number('ERRLOG_SEQ'), concat(p_message_qualifier,'@',substr(p_audit_data_MySQL,1,3500)),concat('WARNING! Unknown qualifier at: ',DATABASE(), ', and para is: ',p_location),SYSDATE());
  end if;

  if upper(p_audit_data_MySQL) like upper('%TA_SESSION%') THEN

     insert into ta_session_log (pkey,  fromwhere, start_location,en_de_q, qualifier, SQL_STATEMENT )
                        values (func_seq_get_next_number('ta_session_log_seq'),database(),p_location,1,p_message_qualifier,p_audit_data_MySQL);

  end if;


  IF     (p_audit_data_MySQL IS NOT NULL and p_audit_data_MySQL <> '')
    and  (p_message_qualifier <> 'MMS' or upper(database())=v_centre_db) THEN
		SET @g_sql = p_audit_data_MySQL;
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
	END IF;

  IF v_qua_chk = 1 and v_pub_cnt > 0 and v_grp_cnt > 0 and v_oth_cnt > 0 then

	SET  v_oracle_dml_len = CHAR_LENGTH(p_audit_data_Oracle);
	SET  v_mysql_dml_len  = CHAR_LENGTH(p_audit_data_MySQL);
	SET  v_audit_data_Oracle = CONCAT('Oracle', v_oracle_dml_len ,'=', p_audit_data_Oracle);
	SET  v_audit_data_MySQL  = CONCAT('MySQL', v_mysql_dml_len, '=', p_audit_data_MySQL);
	SET  v_payload = CONCAT(p_message_qualifier, ':', p_location, ',', v_audit_data_MySQL, v_audit_data_Oracle)
 ;

	#CALL prc_enqueue(p_location, v_queue_table, p_message_qualifier, v_payload, '', v_subType, v_centre_db, v_sub_cnt);

/*
  if p_message_qualifier in ('PUBLIC','GROUP','INSERT', 'UPDATE', 'DELETE') then
      set v_que_name = v_queue;
  elseif p_message_qualifier = 'MMS' then
      set v_que_name = v_mms_queue;
  end if;
*/

  CALL prc_enqueue(p_location, v_queue, p_message_qualifier, v_payload, '', v_centre_db, v_sub_cnt);

  END IF;

END $$

DELIMITER ;