
delimiter $$
drop trigger if exists que_bdr_trg $$

drop trigger if exists que_enq_adr_trg $$
CREATE TRIGGER que_enq_adr_trg after DELETE
    ON aq_audit_data_queue_t_en FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if old.state <> 3 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid;
    if lv_cnt is null or lv_cnt = '' then
        delete from audit_data_queue_t where msgid = old.msgid;
    else 
	  update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;
END$$


drop trigger if exists que_enq_aur_trg $$
CREATE TRIGGER que_enq_aur_trg after UPDATE
    ON aq_audit_data_queue_t_en FOR EACH ROW
BEGIN
  declare lv_cnt int(10) unsigned;
  if new.state = 4 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid and state<>4;
    if lv_cnt is null or lv_cnt = '' then
       update audit_data_queue_t set state = 4, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

  if new.state = 3 then
    select 1 into lv_cnt from aq_audit_data_queue_t_en where msgid = old.msgid and state<>3;
    if lv_cnt is null or lv_cnt = '' then
       update audit_data_queue_t set state = 3, DEQ_TIME = sysdate() where msgid = old.msgid;
    else
       update audit_data_queue_t set state = 2 where msgid = old.msgid;
    end if;
  end if;

END$$
delimiter ;