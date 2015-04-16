delimiter $$
drop event if exists job_analyze_tab_week$$
Create event job_analyze_tab_week
On schedule
Every 1 WEEK
STARTS TIMESTAMP(CASE DAYNAME(NOW())
              WHEN 'Sunday'    THEN curdate()
              WHEN 'Monday'    THEN curdate() + INTERVAL 6 DAY
              WHEN 'Tuesday'   THEN curdate() + INTERVAL 5 DAY
              WHEN 'Wednesday' THEN curdate() + INTERVAL 4 DAY
              WHEN 'Thursday'  THEN curdate() + INTERVAL 3 DAY
              WHEN 'Friday'    THEN curdate() + INTERVAL 2 DAY
              WHEN 'Saturday'  THEN curdate() + INTERVAL 1 DAY
           END)
Do
Begin
analyze table entity;
analyze table entityparameter;
analyze table entityparametervalue;
analyze table audit_data_queue_t;
analyze table aq_audit_data_queue_t_i;
analyze table mms_data_queue_t;
analyze table aq_mms_data_queue_t_i;
End$$
delimiter ; 

delimiter $$
drop event if exists job_analyze_tab_daily$$
Create event job_analyze_tab_daily
On schedule
Every 24 hour
Starts adddate(adddate(curdate(), interval 1 day), interval 10 minute)
Do
Begin

  declare lv_cnt bigint default 0;

  if DAYNAME(NOW()) <> 'Sunday' then
    select count(*) into lv_cnt from audit_data_queue_t;
      if lv_cnt > 100000 then
        analyze table audit_data_queue_t;
      end if;
    set lv_cnt = 0;
    select count(*) into lv_cnt from aq_audit_data_queue_t_i;
      if lv_cnt > 100000 then
        analyze table aq_audit_data_queue_t_i;
      end if;
    set lv_cnt = 0;
    select count(*) into lv_cnt from mms_data_queue_t;
      if lv_cnt > 100000 then
        analyze table mms_data_queue_t;
      end if;
    set lv_cnt = 0;
    select count(*) into lv_cnt from aq_mms_data_queue_t_i;
      if lv_cnt > 100000 then
        analyze table aq_mms_data_queue_t_i;
      end if;
    set lv_cnt = 0;
  end if;

End$$
delimiter ; 
