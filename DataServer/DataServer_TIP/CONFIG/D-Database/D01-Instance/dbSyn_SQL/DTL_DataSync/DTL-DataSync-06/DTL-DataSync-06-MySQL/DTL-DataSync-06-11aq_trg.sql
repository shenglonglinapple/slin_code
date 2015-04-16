-- Audit_data_queue
delimiter $$

drop trigger if exists que_enq_adr_trg $$
CREATE TRIGGER que_enq_adr_trg after DELETE
    ON aq_audit_data_queue_t_i FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if old.state = 1 then
    select 1 into lv_cnt from aq_audit_data_queue_t_i where msgid = old.msgid;
    if lv_cnt is null or lv_cnt = '' then
        delete from audit_data_queue_t where msgid = old.msgid;
    else 
	  update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;
END$$


drop trigger if exists que_enq_aur_trg $$
CREATE TRIGGER que_enq_aur_trg after UPDATE
    ON aq_audit_data_queue_t_i FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if new.state = 4 then
    select 1 into lv_cnt from aq_audit_data_queue_t_i where msgid = old.msgid and state<>4;
    if lv_cnt is null or lv_cnt = '' then
       update audit_data_queue_t set state = 4, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

END$$
delimiter ;

-- MMS_data_queue
delimiter $$

drop trigger if exists que_mms_enq_adr_trg $$
CREATE TRIGGER que_mms_enq_adr_trg after DELETE
    ON aq_mms_data_queue_t_i FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if old.state = 1 then
    select 1 into lv_cnt from aq_mms_data_queue_t_i where msgid = old.msgid;
    if lv_cnt is null or lv_cnt = '' then
        delete from mms_data_queue_t where msgid = old.msgid;
    else 
	  update mms_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;
END$$


drop trigger if exists que_mms_enq_aur_trg $$
CREATE TRIGGER que_mms_enq_aur_trg after UPDATE
    ON aq_mms_data_queue_t_i FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if new.state = 4 then
    select 1 into lv_cnt from aq_mms_data_queue_t_i where msgid = old.msgid and state<>4;
    if lv_cnt is null or lv_cnt = '' then
       update mms_data_queue_t set state = 4, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update mms_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

END$$
delimiter ;