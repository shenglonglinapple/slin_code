DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enqueue_audit_data` $$
CREATE PROCEDURE `prc_enqueue_audit_data`(
	IN p_location              VARCHAR(80),
	IN p_message_qualifier     VARCHAR(80),
	IN p_audit_data_Oracle     VARCHAR(4000),
  IN p_audit_data_MySQL      VARCHAR(4000) )
BEGIN

	DECLARE    gc_queue_name         VARCHAR(30) DEFAULT  'AUDIT_DATA_QUEUE';
	DECLARE    gc_mms_queue_name     VARCHAR(30) DEFAULT  'MMS_DATA_QUEUE';
	DECLARE    gc_OCC_location       VARCHAR(80) DEFAULT  'TRANSACT';
	DECLARE    v_queue_name          VARCHAR(30) DEFAULT  gc_queue_name;
	
	DECLARE    v_recipient   		VARCHAR(4000) DEFAULT NULL;
	DECLARE    v_address   			VARCHAR(128) DEFAULT NULL;
	DECLARE		v_instance_name		VARCHAR(30) default null;
	DECLARE		v_location			VARCHAR(30) default null;
	DECLARE    v_payload             VARCHAR(7000) DEFAULT NULL;
	DECLARE    v_audit_data_Oracle   VARCHAR(4000) DEFAULT NULL;
	DECLARE    v_audit_data_MySQL    VARCHAR(4000) DEFAULT NULL;
	DECLARE    v_message_qualifier   VARCHAR(100) DEFAULT NULL;
	DECLARE    v_oracle_dml_len      INT(5) DEFAULT 0;
	DECLARE    v_mysql_dml_len       INT(5) DEFAULT 0;
	DECLARE    v_mess_qualifier_len  INT(5) DEFAULT 0;	
	
	DECLARE  v_no_more_row        BOOLEAN DEFAULT FALSE;
	DECLARE  v_group_mem          VARCHAR(80) DEFAULT NULL;	
	DECLARE  v_public_mem          VARCHAR(80) DEFAULT NULL;
	DECLARE  v_other_mem          VARCHAR(80) DEFAULT NULL;
	DECLARE  v_other_location     VARCHAR(80) DEFAULT NULL;	

	DECLARE cu_recipient  CURSOR FOR
	SELECT DISTINCT name FROM recipient WHERE address is not null and status = 0;
	
	DECLARE cu_grp  CURSOR FOR
	SELECT DISTINCT MEMBER FROM recipient_group WHERE NAME = p_location AND member <> v_instance_name and status = 0;

	DECLARE cu_recipient_other  CURSOR FOR
	SELECT DISTINCT name FROM recipient WHERE name = v_other_location and address is not null and status = 0;

	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_row = TRUE;
		
	DECLARE CONTINUE HANDLER FOR 1062 begin end;

Start Transaction;	

	set v_instance_name = upper(database());

	if upper(p_audit_data_MySQL) like upper('%TA_SESSION%') THEN
		begin
			DECLARE CONTINUE HANDLER FOR SQLEXCEPTION 
				begin 
					insert into ta_error_log(pkey,sql_statement,error_message,timestamp)
						values (func_seq_get_next_number('errlog_seq'),concat('Enqueue:',p_message_qualifier,'@',database(),'::::',p_location,
								substr(p_audit_data_MySQL,1,3500)),'==>TA-SESSION-ERRORS',now());
					COMMIT;
				end;
			insert into ta_session_log (pkey,  fromwhere, start_location,en_de_q, qualifier, SQL_STATEMENT )
                        values (func_seq_get_next_number('ta_session_log_seq'),v_instance_name,p_location,1,p_message_qualifier,p_audit_data_MySQL);
			end;
	end if;

	IF p_message_qualifier = 'GROUP' THEN
		set v_location = p_location;
		OPEN cu_grp;
		the_group_mem_loop: LOOP
			FETCH cu_grp INTO v_group_mem;
			IF v_no_more_row THEN
				CLOSE cu_grp ;
			  	LEAVE the_group_mem_loop ;
			END IF;
			select address into v_address from recipient_info where upper(name) = upper(v_group_mem);
			IF v_recipient <> '' THEN
				set v_recipient = concat(v_recipient,';',v_group_mem,',',v_address);
			ELSE
				set v_recipient = concat(v_group_mem,',',v_address);
			END IF;
		 END LOOP the_group_mem_loop;
	ELSEIF p_message_qualifier = 'PUBLIC' THEN
		set v_location = v_instance_name;
		OPEN cu_recipient;
		the_public_mem_loop: LOOP
			FETCH cu_recipient INTO v_public_mem;
			IF v_no_more_row THEN
				CLOSE cu_recipient ;
			  	LEAVE the_public_mem_loop ;
			END IF;
			select address into v_address from recipient_info where upper(name) = upper(v_public_mem);
			IF v_recipient <> '' THEN
				set v_recipient = concat(v_recipient,';',v_public_mem,',',v_address);
			ELSE
				set v_recipient = concat(v_public_mem,',',v_address);
			END IF;			
		END LOOP the_public_mem_loop;	
	ELSEIF p_message_qualifier in ('INSERT', 'UPDATE', 'DELETE') THEN
			set v_location = p_location;	
			IF v_instance_name = gc_OCC_location THEN
				set v_other_location = p_location;
			ELSE
				set v_other_location = gc_OCC_location;
			END IF;

			OPEN cu_recipient_other;
			the_other_mem_loop: LOOP
				FETCH cu_recipient_other INTO v_other_mem;
			  	IF v_no_more_row THEN
			  		CLOSE cu_recipient_other ;
			  		LEAVE the_other_mem_loop ;
			  	END IF;
			select address into v_address from recipient_info where upper(name) = upper(v_other_mem);
			IF v_recipient <> '' THEN
				set v_recipient = concat(v_recipient,';',v_other_mem,',',v_address);
			ELSE
				set v_recipient = concat(v_other_mem,',',v_address);
			END IF;		
		  	END LOOP the_other_mem_loop;

	ELSEIF upper(p_message_qualifier) = 'MMS' THEN
			set v_queue_name = gc_mms_queue_name;
			IF v_instance_name <> gc_OCC_location then
				select address into v_address from recipient_info where upper(name) = upper(gc_OCC_location);
				set v_recipient = concat(gc_OCC_location,',',v_address);
			END IF;
	ELSE
			INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
				VALUES(func_seq_get_next_number('errlog_seq'),concat(p_message_qualifier,'@',substr(p_audit_data_MySQL,1,3500)), 
						concat('WARNING! Unknown qualifier at: ',v_instance_name,', and para is: ',p_location),now());
	END IF;		
 
	-- Need to continue the execute error after test finished.
  IF p_message_qualifier <> 'MMS' or v_instance_name = gc_OCC_location THEN
 		SET @g_sql = p_audit_data_MySQL;
		PREPARE stmt FROM @g_sql;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
	END IF;
	
  IF v_recipient <> '' then

	SET  v_audit_data_Oracle = CONCAT(CHAR_LENGTH(p_audit_data_Oracle),'AUDIT_DATA_ORACLE' ,'=', p_audit_data_Oracle);
	SET  v_audit_data_MySQL  = CONCAT(CHAR_LENGTH(p_audit_data_MySQL),'AUDIT_DATA_MYSQL', '=', p_audit_data_MySQL);
	
	SET	 v_message_qualifier = CONCAT(p_message_qualifier,':',p_location);
	SET  v_message_qualifier = CONCAT(CHAR_LENGTH(v_message_qualifier),'MESSAGE_QUALIFIER','=',v_message_qualifier);
	
	SET  v_payload = CONCAT(v_message_qualifier, v_audit_data_Oracle, v_audit_data_MySQL);

	CALL prc_enqueue(v_queue_name, v_payload, null, 1, v_recipient);



  END IF;

 COMMIT;
END $$

DELIMITER ;