CREATE OR REPLACE PACKAGE audit_data_queue_pkg
AS
/* ********************************************************************* */
/* Package      : audit_data_queue_pkg                                   */
/* ********************************************************************* */
/* Description  : This package contains procedures to enqueue and        */
/*              : dequeue audit data.                                    */
/* Author       :                                                        */
/* Created Date : 16-Jan-2012         									 */
/* Modified Date: 11-Sep-2012, 05-Feb-2013         						 */
/* ********************************************************************* */

/* Global Constants */
gc_OCC_location                     VARCHAR2(30) := 'TRANSACT';
gc_queue_name                       VARCHAR2(30) := 'AUDIT_DATA_QUEUE';
gc_mms_queue_name                       VARCHAR2(30) := 'MMS_DATA_QUEUE';
gc_halt_dequeue_message             VARCHAR2(30) := 'HALT_DEQUEUE';

PROCEDURE enqueue_audit_data(
    p_location                      IN VARCHAR2,
    p_message_qualifier             IN VARCHAR2,
    p_audit_data_Oracle             IN VARCHAR2,
    p_audit_data_MySQL              IN VARCHAR2 default null
);

PROCEDURE dequeue_audit_data(
    p_location                     IN VARCHAR2
);

PROCEDURE send_halt_dequeue_message(
    p_location                    IN VARCHAR2
);

PROCEDURE dequeue_mms_data(
    p_location                     IN VARCHAR2
);	
	
END audit_data_queue_pkg;
/

CREATE OR REPLACE PACKAGE BODY audit_data_queue_pkg
AS

/*************************************************************************/
/* Procedure    : send_halt_dequeue_message                              */
/*************************************************************************/
/* Description  : This procedure sends a message to a given location     */
/*              : that will stop the dequeue process, which is in a      */
/*              : state where it will wait for a message forever.        */
/* Author       : Kylie Ding                                             */
/* Date         : 23-Jun-2005                                            */
/*************************************************************************/
/* Amendment History:                                                    */
/* ------------------                                                    */
/* Date         Who               Description                            */
/* -----------  ----------------  -------------------------------------- */
/* 23-Jun-2005  Kylie Ding        Original version.  					 */	
/* 11-Sep-2012  Will		      Support MySQL.						 */	
/* 05-Feb-2013	Will			  Adding lock for getting Central Mess ID*/
/*************************************************************************/
PROCEDURE send_halt_dequeue_message(
    p_location                     IN VARCHAR2
)
IS
    v_recipient_address             recipient.address%TYPE;
    v_enqueue_options               dbms_aq.enqueue_options_t;
    v_message_properties            dbms_aq.message_properties_t;
    v_payload                       audit_data_queue_payload_type;
    v_enq_msgid                     RAW(16);
BEGIN
    v_enqueue_options.visibility := dbms_aq.IMMEDIATE;

    /* Get address of the relevant location */
    BEGIN
        SELECT address INTO v_recipient_address FROM recipient WHERE name = p_location;
    EXCEPTION
        WHEN others THEN NULL;
    END;

    /* Get the address of the location */
    v_message_properties.recipient_list(1) := sys.aq$_agent(p_location, v_recipient_address, NULL);

    v_payload := audit_data_queue_payload_type(gc_halt_dequeue_message, NULL,NULL,NULL,NULL);

    /* Enqueue the message */
    dbms_aq.enqueue(
        queue_name => gc_queue_name,
        enqueue_options => v_enqueue_options,
        message_properties => v_message_properties,
        payload => v_payload,
        msgid => v_enq_msgid
    );
END send_halt_dequeue_message;

/*************************************************************************/
/* Procedure    : enqueue_audit_data                                     */
/*************************************************************************/
/* Description  : This procedure enqueues audit data.                    */
/* Author       : Sui Zhao                                               */
/* Date         : 05-Oct-2007                                            */
/*************************************************************************/
/* Amendment History:                                                    */
/* ------------------                                                    */
/* Date         Who               Description                            */
/* -----------  ----------------  -------------------------------------- */
/* 05-Oct-2007  Sui Zhao          Modified version.                      */
/*************************************************************************/
PROCEDURE enqueue_audit_data(
    p_location                      IN VARCHAR2,
    p_message_qualifier             IN VARCHAR2,
    p_audit_data_Oracle             IN VARCHAR2,
    p_audit_data_MySQL              IN VARCHAR2 default null
)
IS
    CURSOR cu_recipient IS
           select name, address,db_link_name,prop_type from recipient where db_link_name is not null and status = 0 ;
    CURSOR cu_grp (c_str_location VARCHAR2, c_str_member VARCHAR2) IS
           select member, db_link_name,prop_type from recipient_group where name = c_str_location and member <> c_str_member and status = 0;
    CURSOR cu_recipient_other (c_location VARCHAR2) IS
           select name, db_link_name, address,prop_type from recipient where name =c_location and db_link_name is not null and status = 0;

    v_enqueue_options               dbms_aq.enqueue_options_t;
    v_message_properties            dbms_aq.message_properties_t;
    v_payload                       audit_data_queue_payload_type;
    v_enq_msgid                     RAW(16);
    v_recipient_id                  number(3) := 0;
    v_error_message                 VARCHAR2(4000);
    v_address                       varchar2(60) := null;
    --add by suiqi to warn p_location <> instance name
    v_instance_name                 varchar2(30) := null;
    v_location                      varchar2(30) := null;
    still_error_sql EXCEPTION;
    v_other_location                varchar2(30) := null;
	v_queue_name					VARCHAR2(30) default gc_queue_name;
	--Added by will 31Oct2012 for generate central sequence id of datasync
	v_cen_sid						number;
	/*
    v_pref_audit_data_Oracle        VARCHAR2(4000) default length(p_audit_data_Oracle)||'AUDIT_DATA_ORACLE'||'='||p_audit_data_Oracle;
    v_pref_audit_data_MySQL         VARCHAR2(4000) default length(p_audit_data_MySQL)||'AUDIT_DATA_MYSQL'||'='||p_audit_data_MySQL;
	v_message_qualifier				VARCHAR2(100) default null;
	*/
/*
    v_MySQLTagLen                   number(5) := 0;
    v_OracleTagLen                  number(5) := 0;
    v_beginPos                      number(5) := 0;
    v_endPos                        number(5) := 0;
    v_MySQLTagPos                   number(5) := 0;
    v_OracleTagPos                  number(5) := 0;
    v_MySQLTag                      varchar2(30) := 'MySQL=';
    v_OracleTag                     varchar2(30) := 'Oracle=';
    v_sql                           varchar2(7000) := null;
*/
-- (ENQ) Use lock to keep the order of aq_cen_sid equal to the order of enq time. Will 01/Feb/2013
        lv_lockstatus int;
        lv_lock_rel_stat int;
BEGIN
    begin
        --add by suiqi to warn p_location <> instance name
        select name into v_instance_name from v$database;
        /*if p_location <> v_instance_name then
            INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
              VALUES(errlog_seq.NEXTVAL, p_message_qualifier||'@'||substr(p_audit_data_dml,1,3500),'WARNING! Enqueue Invoked at: '||v_instance_name || ', but para is: '||p_location,SYSDATE);
        end if;*/
        /*  try to log the ta_session info if passed in*/
        if upper(p_audit_data_Oracle) like upper('%TA_SESSION%') THEN
            begin
                insert into ta_session_log  (pkey,  fromwhere, start_location,en_de_q, qualifier, SQL_STATEMENT )  values (ta_session_log_seq.nextval ,  v_instance_name  ,p_location, 1,  p_message_qualifier,p_audit_data_Oracle );
                exception
                when others  then
                    v_error_message := SUBSTR(SQLERRM, 1, 4000);
                INSERT INTO ta_error_log(pkey,sql_statement,error_message,timestamp)
                    VALUES(errlog_seq.NEXTVAL,'Enqueue::' || p_message_qualifier || '@' || v_instance_name  || '::::' ||p_location || '==>'|| SUBSTR(p_audit_data_Oracle, 1, 3500),v_error_message,SYSDATE);
                    COMMIT;
                    null;
            end;
        end if;

        /*  try to log the ta_session info if passed in*/
        if p_message_qualifier = 'GROUP' then
            v_location := p_location;
            --Group to all member of p_location except local db
            for c_rec in cu_grp(p_location, trim(v_instance_name)) loop
                v_recipient_id := v_recipient_id + 1;

            -- Both support Oracle and MySQL. 'DB_LINK_NAME is not null' means the message is an Oracle propagate message,
            -- otherwise it means the message is a Normal message without any recipient address. 08/06/2012 will
               if upper(c_rec.prop_type) = 'ORACLE' then
                v_address := USER || '.'||gc_queue_name||'@' || c_rec.db_link_name;
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_rec.member, v_address, NULL);
               elsif upper(c_rec.prop_type) = 'MYSQL' then
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_rec.member, null, NULL);
               end if;
            end loop;
        elsif p_message_qualifier = 'PUBLIC' then
            --if Public then p_loction is invaild,
            v_location := v_instance_name;
            -- propagate to all other station
            for c_recipient_rec in cu_recipient loop
                v_recipient_id := v_recipient_id + 1;
               if upper(c_recipient_rec.prop_type) = 'ORACLE' then
                v_address := USER || '.'|| gc_queue_name || '@' || c_recipient_rec.db_link_name;
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, v_address, NULL);
               elsif upper(c_recipient_rec.prop_type) = 'MYSQL' then
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, null, NULL);
               end if;
            end loop;
        elsif p_message_qualifier in ('INSERT', 'UPDATE', 'DELETE') then
            v_location := p_location;
            --if at central then send to p_location except central
            if v_instance_name = gc_OCC_location then
                v_other_location := p_location;
            --if at station then send to central
            else
                v_other_location := gc_OCC_location;
            end if;
            for c_recipient_other in cu_recipient_other(v_other_location) loop
                v_recipient_id := v_recipient_id + 1;
               if upper(c_recipient_other.prop_type) = 'ORACLE' then
                v_address := USER || '.'||gc_queue_name||'@' || c_recipient_other.db_link_name;
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_other.name, v_address, NULL);
               elsif upper(c_recipient_other.prop_type) = 'MYSQL' then
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_other.name, null, NULL);
               end if;
            end loop;
        -- New Message type 'MMS' for MMS message.
        elsif p_message_qualifier = 'MMS' then
			v_queue_name := gc_mms_queue_name;
        -- if at station then send to central
            if v_instance_name <> gc_OCC_location then
            for c_recipient_other in cu_recipient_other(gc_OCC_location) loop
                v_recipient_id := v_recipient_id + 1;
               if upper(c_recipient_other.prop_type) = 'ORACLE' then
                v_address := USER || '.'||gc_mms_queue_name||'@' || c_recipient_other.db_link_name;
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_other.name, v_address, NULL);
               elsif upper(c_recipient_other.prop_type) = 'MYSQL' then
                v_message_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_other.name, null, NULL);
               end if;
            end loop;
            end if;
        else
            INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
              VALUES(errlog_seq.NEXTVAL, p_message_qualifier||'@'||substr(p_audit_data_Oracle,1,3500),'WARNING! Unknown qualifier at: '||v_instance_name || ', and para is: '||p_location,SYSDATE);
        end if;

        /*
        v_MySQLTagLen  := LENGTH(v_MySQLTag);
        v_OracleTagLen := LENGTH(v_OracleTag);
        v_MySQLTagPos  := INSTR(p_audit_data_dml, v_MySQLTag);
        v_OracleTagPos := INSTR(p_audit_data_dml, v_OracleTag);
        IF (v_MySQLTagPos <> 0 AND v_OracleTagPos <> 0) THEN
            IF (v_OracleTagPos > v_MySQLTagPos) THEN
                v_beginPos := v_OracleTagPos + v_OracleTagLen;
                v_sql := SUBSTR(p_audit_data_dml, v_beginPos);
            ELSE
                v_beginPos := v_OracleTagPos + v_OracleTagLen;
                v_endPos   := v_MySQLTagPos;
                v_sql := SUBSTR(p_audit_data_dml, v_beginPos, v_endPos - v_beginPos);
            END IF;
        ELSE
            v_sql := p_audit_data_dml;
        END IF;
        */

        -- execute sql statement in the message except (p_message_qualifier = 'MMS' and v_instance_name <> gc_OCC_location)
        if p_message_qualifier <> 'MMS' or v_instance_name = gc_OCC_location then
        EXECUTE IMMEDIATE p_audit_data_Oracle;
        end if;

        if v_recipient_id > 0 then
            -- set AQ message variable
            v_enqueue_options.visibility := dbms_aq.IMMEDIATE;
            --noticed: load compressed sql
			/*
			v_message_qualifier := p_message_qualifier||':'||p_location;
			v_message_qualifier := length(v_message_qualifier)||'MESSAGE_QUALIFIER'||'='||v_message_qualifier;
			*/
            -- v_payload := audit_data_queue_payload_type(p_message_qualifier||':'||v_location, compress_sql(p_audit_data_dml));
			-- Added by will 31Oct2012 for generate central sequence id of datasync.
			  -- (ENQ) Use lock to keep the order of aq_cen_sid equal to the order of enq time. Will 01/Feb/2013 
			  -- lv_lockstatus: 0-Success 1-Timeout 2-Deadlock 3-Parameter error 4-Don't own lock specified by id or lockhandle 5-Illegal lock handle   
			 loop  
			  lv_lockstatus := dbms_lock.request
			  (id => 271350,
			   lockmode   => dbms_lock.x_mode,
			   timeout    => 5,
			   release_on_commit => true);
			   
			   if lv_lockstatus = 0 then
				  exit;
			   elsif lv_lockstatus in (1,2) then
				  null;
			   else 
				  RAISE_APPLICATION_ERROR (20010, 'dbms_lock.request return status not in (0,1,2). Enqueue failed');
			   end if;
			 end loop;
						
			select aq_cen_sid.NEXTVAL into v_cen_sid from dual;
            v_payload := audit_data_queue_payload_type(p_message_qualifier||':'||v_location,0,v_cen_sid,p_audit_data_Oracle,p_audit_data_MySQL);
            -- enqueue the AQ message
			dbms_aq.enqueue(
                queue_name => v_queue_name,
                enqueue_options => v_enqueue_options,
                message_properties => v_message_properties,
                payload => v_payload,
                msgid => v_enq_msgid
            );
			
			lv_lock_rel_stat := dbms_lock.release(id => 271350);   			
			/*
            dbms_aq.enqueue(
                queue_name => gc_queue_name,
                enqueue_options => v_enqueue_options,
                message_properties => v_message_properties,
                payload => v_payload,
                msgid => v_enq_msgid
            );
			*/
			
        end if;
    EXCEPTION
        WHEN OTHERS THEN
        begin
            v_error_message := SUBSTR(SQLERRM, 1, 4000);
            INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                VALUES(errlog_seq.NEXTVAL,v_location || '<>Enqueue::'||p_message_qualifier ||'@'|| p_location || '==>'  || SUBSTR(p_audit_data_Oracle, 1, 3500),v_error_message,SYSDATE);
            COMMIT;

            RAISE still_error_sql;
        --EXCEPTION
        --    WHEN OTHERS THEN NULL;
        end;
    end;
    commit;
END enqueue_audit_data;

/*************************************************************************/
/* Procedure    : dequeue_audit_data                                     */
/*************************************************************************/
/* Description  : This procedure dequeues audit data.                    */
/* Author       : Sui Zhao                                               */
/* Date         : 05-Oct-2007                                            */
/*************************************************************************/
/* Amendment History:                                                    */
/* ------------------                                                    */
/* Date         Who               Description                            */
/* -----------  ----------------  -------------------------------------- */
/* 05-Oct-2007  Sui Zhao          Modified version.                      */
/*************************************************************************/
PROCEDURE dequeue_audit_data(
    p_location                     IN VARCHAR2)
IS

--	support MMS and Audit 23/01/2012 will
/*
    CURSOR cu_recipient(c_src_location VARCHAR2) IS
    select name, address, prop_type from recipient where name != c_src_location;
*/
    CURSOR cu_recipient(c_src_location VARCHAR2) IS
    select name, address, prop_type, db_link_name from recipient where name != c_src_location;
    -- enqueue option
    v_enqueue_options               dbms_aq.enqueue_options_t;
    v_enq_msg_properties            dbms_aq.message_properties_t;
    v_enq_msgid                     RAW(16);
    v_start                         number(2) := 0;
    v_recipient_id                  number(3) := 0;
    v_enq_null                          dbms_aq.message_properties_t;
	v_cen_sid						number;	

    -- dequeue option
    v_dequeue_options                dbms_aq.dequeue_options_t;
    v_deq_msg_properties            dbms_aq.message_properties_t;
    v_recipients                    dbms_aq.aq$_recipient_list_t;
    v_payload                        audit_data_queue_payload_type;
    v_deq_msgid                        RAW(16);
    v_error_message                    VARCHAR2(4000);
    v_qualifier                     VARCHAR2(30) := '';
    v_src_location                  varchar2(30) := '';
    v_origin_sql                    varchar2(4000) := '';
	
    v_address                       varchar2(60) := null;

-- (DEQ) Use lock to keep the order of aq_cen_sid equal to the order of enq time. Will 01/Feb/2013
	lv_lockstatus int;
	lv_lock_rel_stat int;	
BEGIN
     -- We want to dequeue a message immediately, so the wait option is set to FOREVER.
    -- To halt the dequeue a halt message will have to be dequeued.
    v_dequeue_options.wait := DBMS_AQ.FOREVER;
    v_dequeue_options.consumer_name := p_location;
    v_dequeue_options.navigation := DBMS_AQ.FIRST_MESSAGE;
    v_dequeue_options.dequeue_mode := DBMS_AQ.REMOVE;
    -- set enqueue option
    v_enqueue_options.visibility := dbms_aq.IMMEDIATE;

    LOOP
        BEGIN
            -- init recipient_list
            <<L_start>>
            v_recipient_id := 0;
            v_enq_msg_properties := v_enq_null;

            begin
                -- dequeue message
                dbms_aq.dequeue(
                    queue_name        => gc_queue_name,
                    dequeue_options        => v_dequeue_options,
                    message_properties    => v_deq_msg_properties,
                    payload         => v_payload,
                    msgid             => v_deq_msgid);
                --get origin sql to be executed and loged
                -- v_origin_sql := uncompress_sql(v_payload.audit_data_dml);
                v_origin_sql := v_payload.audit_data_Oracle;
                -- remove the prefix of SQL audit_data_Oracle
                --v_origin_sql := substr(v_origin_sql,instr(v_origin_sql,'=')+1);
            exception
                WHEN OTHERS THEN
                begin
                    --if dequeue error then log it and exit
                    v_error_message := SUBSTR(SQLERRM, 1, 4000);
                    INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                        VALUES(errlog_seq.NEXTVAL,'Dequeue error ' || v_payload.message_qualifier || '@' || v_src_location ||  '==>'|| SUBSTR(v_origin_sql, 1, 3500),v_error_message,SYSDATE);
                exception
                    WHEN OTHERS THEN null;
                end;
                exit;
            end;

            if v_payload.message_qualifier = gc_halt_dequeue_message then
                exit;
            end if;

            --get qualifier and location
            v_start := instr(v_payload.message_qualifier, ':');
            if v_start != 0 then
                -- get source location of aq message
                v_src_location := substr(v_payload.message_qualifier, v_start + 1);
                v_qualifier := substr(v_payload.message_qualifier, 1, v_start - 1);
            end if;

            if v_qualifier not in ('INSERT', 'UPDATE', 'DELETE', 'PUBLIC', 'GROUP', 'MMS') then
                            INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                            VALUES(errlog_seq.NEXTVAL,'Not in the five words','then how???',SYSDATE);
                goto L_start ;
            end if;

            -- for central db, if public then propagate to all other stations
            if p_location = gc_OCC_location and v_qualifier = 'PUBLIC' then
                -- propagate to all other station except source station
                for c_recipient_rec in cu_recipient(v_src_location) loop
                    if c_recipient_rec.db_link_name is not null then
                        v_recipient_id := v_recipient_id + 1;
                       if upper(c_recipient_rec.prop_type) = 'ORACLE' then
					   -- will for support MMS and Audit 23/01/2013
						v_address := USER || '.'|| gc_queue_name || '@' || c_recipient_rec.db_link_name;					   
                        v_enq_msg_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, v_address, NULL);
                       elsif upper(c_recipient_rec.prop_type) = 'MYSQL' then
                        v_enq_msg_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, null, NULL);
                       end if;

                    end if;
                end loop;
            end if;

            -- execute sql statement in the message except (p_message_qualifier = 'MMS' and v_instance_name <> gc_OCC_location)
            if v_qualifier <> 'MMS' or p_location = gc_OCC_location then
            begin
                EXECUTE IMMEDIATE v_origin_sql;
            EXCEPTION
                WHEN OTHERS THEN
                BEGIN
                    v_error_message := SUBSTR(SQLERRM, 1, 4000);
                    INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                    VALUES(errlog_seq.NEXTVAL,SUBSTR(v_payload.audit_data_oracle, 1, 4000),v_error_message,SYSDATE);
                    COMMIT;
                end;
            end;
            end if;

        if upper(v_origin_sql) like upper('%TA_SESSION%') THEN
            begin
                insert into ta_session_log  (pkey,  fromwhere, start_location,en_de_q, qualifier, SQL_STATEMENT )  values (ta_session_log_seq.nextval ,  p_location  ,v_src_location, 0,  v_qualifier ,v_origin_sql );
                exception
                when others  then

                                v_error_message := SUBSTR(SQLERRM, 1, 4000);
                INSERT INTO ta_error_log(pkey,sql_statement,error_message,timestamp)
                    VALUES(errlog_seq.NEXTVAL,'Dequeue::' || v_payload.message_qualifier || '@' || v_src_location || '==>'|| SUBSTR(v_origin_sql, 1, 3500),v_error_message,SYSDATE);
                    COMMIT;

                    null;
            end;
        end if;


            -- enqueue the AQ message
            if v_recipient_id > 0 then
			-- add by will for supporting cen_sid when enqueue into central db. 4Dec2012      
			  -- (Deq) Use lock to keep the order of aq_cen_sid equal to the order of enq time. Will 01/Feb/2013 
			  -- lv_lockstatus: 0-Success 1-Timeout 2-Deadlock 3-Parameter error 4-Don't own lock specified by id or lockhandle 5-Illegal lock handle   
			 loop  
			  lv_lockstatus := dbms_lock.request
			  (id => 271350,
			   lockmode   => dbms_lock.x_mode,
			   timeout    => 5,
			   release_on_commit => true);
			   
			   if lv_lockstatus = 0 then
				  exit;
			   elsif lv_lockstatus in (1,2) then
				  null;
			   else 
				  RAISE_APPLICATION_ERROR (20010, 'dbms_lock.request return status not in (0,1,2). Enqueue failed');
			   end if;
			 end loop;
							
			select aq_cen_sid.NEXTVAL into v_cen_sid from dual;
			v_payload.central_sid := v_cen_sid;
                dbms_aq.enqueue(
                    queue_name => gc_queue_name,
                    enqueue_options => v_enqueue_options,
                    message_properties => v_enq_msg_properties,
                    payload => v_payload,
                        msgid => v_enq_msgid
                    );
					
			lv_lock_rel_stat := dbms_lock.release(id => 271350); 
	   
            end if;
        EXCEPTION
            WHEN OTHERS THEN
            begin
                v_error_message := SUBSTR(SQLERRM, 1, 4000);
                INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                    VALUES(errlog_seq.NEXTVAL,'Dequeue::' || v_payload.message_qualifier || '@' || v_src_location || '==>'|| SUBSTR(v_origin_sql, 1, 3500),v_error_message,SYSDATE);
                    COMMIT;
            exception
                WHEN OTHERS THEN null;
            end;
        END;
        COMMIT;
    END LOOP;
    --final commit
    commit;
END dequeue_audit_data;

PROCEDURE dequeue_mms_data(
    p_location                     IN VARCHAR2)
IS
    -- enqueue option
    v_enqueue_options               dbms_aq.enqueue_options_t;
    v_enq_msg_properties            dbms_aq.message_properties_t;
    v_enq_msgid                     RAW(16);
    v_start                         number(2) := 0;
    v_recipient_id                  number(3) := 0;
    v_enq_null                          dbms_aq.message_properties_t;

    -- dequeue option
    v_dequeue_options                dbms_aq.dequeue_options_t;
    v_deq_msg_properties            dbms_aq.message_properties_t;
    v_recipients                    dbms_aq.aq$_recipient_list_t;
    v_payload                        audit_data_queue_payload_type;
    v_deq_msgid                        RAW(16);
    v_error_message                    VARCHAR2(4000);
    v_qualifier                     VARCHAR2(30) := '';
    v_src_location                  varchar2(30) := '';
    v_origin_sql                    varchar2(4000) := '';

BEGIN
     -- We want to dequeue a message immediately, so the wait option is set to FOREVER.
    -- To halt the dequeue a halt message will have to be dequeued.
    v_dequeue_options.wait := DBMS_AQ.FOREVER;
    v_dequeue_options.consumer_name := p_location;
    v_dequeue_options.navigation := DBMS_AQ.FIRST_MESSAGE;
    v_dequeue_options.dequeue_mode := DBMS_AQ.REMOVE;
    -- set enqueue option
    v_enqueue_options.visibility := dbms_aq.IMMEDIATE;

    LOOP
        BEGIN
            -- init recipient_list
            <<L_start>>
            v_recipient_id := 0;
            v_enq_msg_properties := v_enq_null;

            begin
                -- dequeue message
                dbms_aq.dequeue(
                    queue_name        => gc_mms_queue_name,
                    dequeue_options        => v_dequeue_options,
                    message_properties    => v_deq_msg_properties,
                    payload         => v_payload,
                    msgid             => v_deq_msgid);
                --get origin sql to be executed and loged
                -- v_origin_sql := uncompress_sql(v_payload.audit_data_dml);
                v_origin_sql := v_payload.audit_data_Oracle;
                -- remove the prefix of SQL audit_data_Oracle
                --v_origin_sql := substr(v_origin_sql,instr(v_origin_sql,'=')+1);
            exception
                WHEN OTHERS THEN
                begin
                    --if dequeue error then log it and exit
                    v_error_message := SUBSTR(SQLERRM, 1, 4000);
                    INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                        VALUES(errlog_seq.NEXTVAL,'Dequeue error ' || v_payload.message_qualifier || '@' || v_src_location ||  '==>'|| SUBSTR(v_origin_sql, 1, 3500),v_error_message,SYSDATE);
                exception
                    WHEN OTHERS THEN null;
                end;
                exit;
            end;

            if v_payload.message_qualifier = gc_halt_dequeue_message then
                exit;
            end if;

            --get qualifier and location
            v_start := instr(v_payload.message_qualifier, ':');
            if v_start != 0 then
                -- get source location of aq message
                v_src_location := substr(v_payload.message_qualifier, v_start + 1);
                v_qualifier := substr(v_payload.message_qualifier, 1, v_start - 1);
            end if;

            if v_qualifier <> 'MMS' then
                            INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                            VALUES(errlog_seq.NEXTVAL,'Not MMS Message','then how???',SYSDATE);
                goto L_start ;
			elsif v_qualifier ='MMS' and p_location = gc_OCC_location then
				begin
					EXECUTE IMMEDIATE v_origin_sql;
					EXCEPTION
					WHEN OTHERS THEN
						BEGIN
							v_error_message := SUBSTR(SQLERRM, 1, 4000);
							INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
								VALUES(errlog_seq.NEXTVAL,SUBSTR(v_payload.audit_data_oracle, 1, 4000),v_error_message,SYSDATE);
							COMMIT;
						END;
				end;
            end if;

        EXCEPTION
            WHEN OTHERS THEN
            begin
                v_error_message := SUBSTR(SQLERRM, 1, 4000);
                INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
                    VALUES(errlog_seq.NEXTVAL,'Dequeue::' || v_payload.message_qualifier || '@' || v_src_location || '==>'|| SUBSTR(v_origin_sql, 1, 3500),v_error_message,SYSDATE);
                    COMMIT;
            exception
                WHEN OTHERS THEN null;
            end;
        END;
        COMMIT;
    END LOOP;
    --final commit
    commit;
END dequeue_mms_data;

END audit_data_queue_pkg;
/