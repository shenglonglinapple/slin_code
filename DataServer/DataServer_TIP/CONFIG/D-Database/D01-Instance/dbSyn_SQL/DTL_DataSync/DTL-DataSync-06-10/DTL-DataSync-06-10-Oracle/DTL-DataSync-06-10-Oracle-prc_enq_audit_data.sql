CREATE OR REPLACE PROCEDURE prc_enq_audit_data(
    p_mixed_message_qualifier       IN VARCHAR2,
    p_audit_data_Oracle             IN VARCHAR2,
    p_audit_data_MySQL              IN VARCHAR2 default null
)
IS
    CURSOR cu_recipient(c_src_location VARCHAR2) IS
    select name, address, prop_type from recipient where name != c_src_location;

    lv_queue_name                   VARCHAR2(30) := 'AUDIT_DATA_QUEUE';
    v_enqueue_options               dbms_aq.enqueue_options_t;
    v_enq_msg_properties            dbms_aq.message_properties_t;
    v_enq_msgid                     RAW(16);
    v_start                         number(2) := 0;
    v_recipient_id                  number(3) := 0;
    v_error_message                 VARCHAR2(4000);
    v_qualifier                     VARCHAR2(30) := '';
    v_src_location                  varchar2(30) := '';
    v_payload                       audit_data_queue_payload_type;
    lv_lockstatus int;
    lv_lock_rel_stat int;
    v_cen_sid        int;
BEGIN
    -- set enqueue option
    v_enqueue_options.visibility := dbms_aq.IMMEDIATE;

            --get qualifier and location
            v_start := instr(p_mixed_message_qualifier, ':');
            if v_start != 0 then
                -- get source location of aq message
                v_src_location := substr(p_mixed_message_qualifier, v_start + 1);
                v_qualifier := substr(p_mixed_message_qualifier, 1, v_start - 1);
            end if;

            if v_qualifier not in ('INSERT', 'UPDATE', 'DELETE', 'PUBLIC', 'GROUP', 'MMS') then
              prc_log_errors('Not in the five words','then how???');
              Return;
            end if;

            -- for central db, if public then propagate to all other stations
            if v_qualifier = 'PUBLIC' then
                -- propagate to all other station except source station
                for c_recipient_rec in cu_recipient(v_src_location) loop
                    if c_recipient_rec.address is not null then
                        v_recipient_id := v_recipient_id + 1;
                       if upper(c_recipient_rec.prop_type) = 'ORACLE' then
                        v_enq_msg_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, c_recipient_rec.address, NULL);
                       elsif upper(c_recipient_rec.prop_type) = 'MYSQL' then
                        v_enq_msg_properties.recipient_list(v_recipient_id) := sys.aq$_agent(c_recipient_rec.name, null, NULL);
                       end if;

                    end if;
                end loop;
            end if;
            begin
                EXECUTE IMMEDIATE p_audit_data_Oracle;
                exception
                  when others then
                   begin
                    v_error_message := SUBSTR(SQLERRM, 1, 4000);
                    prc_log_errors('Enqueue-Directly::' || v_qualifier || '@' || v_src_location || '==>'|| SUBSTR(p_audit_data_Oracle, 1, 3500),v_error_message);
                    if lower(v_error_message) like '%shutdown in progress%'
                       or lower(v_error_message) like '%instance terminated%'
                       or lower(v_error_message) like '%unable to extend%'
                       or lower(v_error_message) like '%timeout%'
                       or lower(v_error_message) like '%resource busy%'
                    then
                       raise;
                    end if;
                   end;
            end;

        if upper(p_audit_data_Oracle) like upper('%TA_SESSION%') THEN
                insert into ta_session_log(pkey,  fromwhere, start_location,en_de_q, qualifier, SQL_STATEMENT )  values (ta_session_log_seq.nextval , (select name from v$database) ,v_src_location, 0,  v_qualifier ,p_audit_data_Oracle );
        end if;

            -- enqueue the AQ message
            if v_recipient_id > 0 then

              -- (ENQ) Use lock to keep the order of aq_cen_sid equal to the order of enq time. Will
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
                v_payload := audit_data_queue_payload_type(p_mixed_message_qualifier,0,v_cen_sid,p_audit_data_Oracle,p_audit_data_MySQL);
              begin
                dbms_aq.enqueue(
                    queue_name => lv_queue_name,
                    enqueue_options => v_enqueue_options,
                    message_properties => v_enq_msg_properties,
                    payload => v_payload,
                        msgid => v_enq_msgid
                    );
                lv_lock_rel_stat := dbms_lock.release(id => 271350);
               EXCEPTION
                WHEN OTHERS THEN
                 v_error_message := SUBSTR(SQLERRM, 1, 4000);
                 prc_log_errors('Enqueue-Directly::' || v_qualifier || '@' || v_src_location || '==>'|| SUBSTR(p_audit_data_Oracle, 1, 3500),v_error_message);
                 raise;
               end;
            end if;

END;
/
