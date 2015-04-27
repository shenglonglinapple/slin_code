
DELIMITER $$

DROP FUNCTION IF EXISTS `func_seq_get_next_number` $$
CREATE FUNCTION `func_seq_get_next_number`(
p_name varchar(100)) RETURNS int(38)
    DETERMINISTIC
BEGIN
    declare lv_lastn  decimal(30,0);
    declare lv_limit  decimal(30,0);
    declare lv_inc_by int(11);
    declare lv_cycle  varchar(1);
    declare lv_init   bigint(20);


    declare cu_lastn cursor for
      select MAX_NUMBER,increment_by,init_number,cycle_flag
        from adm_sequence
       where name = trim(upper(p_name));


    open cu_lastn;
    fetch cu_lastn
      into lv_limit,lv_inc_by,lv_init,lv_cycle;
    close cu_lastn;



      update adm_sequence
        set last_number = last_insert_id(last_number + (increment_by))
      where name = trim(upper(p_name));

    set lv_lastn = last_insert_id();

    if (lv_inc_by > 0 and lv_lastn <= lv_limit) or
       (lv_inc_by < 0 and lv_lastn >= lv_limit) then

      return lv_lastn;
    elseif upper(lv_cycle)='Y' then
      update adm_sequence set last_number=lv_init where name = trim(upper(p_name));
      return lv_init;
    else
      select 1 into @1 from Err_The_NextVal_Exceed_MaxValue;
    end if;


  end $$

DELIMITER ;