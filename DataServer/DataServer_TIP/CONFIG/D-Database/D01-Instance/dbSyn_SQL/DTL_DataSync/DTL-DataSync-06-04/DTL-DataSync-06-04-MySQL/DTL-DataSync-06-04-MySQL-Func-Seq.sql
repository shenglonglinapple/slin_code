
DELIMITER $$

DROP FUNCTION IF EXISTS `func_seq_get_next_number` $$
CREATE FUNCTION `func_seq_get_next_number`(
p_name varchar(100)) RETURNS decimal(30,0)
    DETERMINISTIC
BEGIN
    declare lv_lastn  decimal(30,0);
    declare lv_limit  decimal(30,0);
    declare lv_inc_by int(11);
    declare lv_cycle  varchar(1);
    declare lv_init   bigint(20);
    declare lv_nodes_num int(3) default @@SYNC_BINLOG+1;
    declare lv_node_id   int(3) default @@server_id;

    declare cu_lastn cursor for
      select MAX_NUMBER,increment_by,init_number,cycle_flag
        from adm_sequence
       where name = trim(upper(p_name));


    open cu_lastn;
    fetch cu_lastn
      into lv_limit,lv_inc_by,lv_init,lv_cycle;
    close cu_lastn;
/*
      update adm_sequence
        set last_number = last_insert_id(last_number + (increment_by))
      where name = trim(upper(p_name));
*/
      update adm_sequence t1 inner join adm_sequence_rep t2 on t1.name=t2.name
        set t1.last_number = last_insert_id(
        if(abs(t1.last_number-t2.last_number)>cast((t1.max_number/2) as UNSIGNED),least(t1.last_number,t2.last_number),greatest(t1.last_number,t2.last_number))
          + t1.increment_by),
            t2.last_number = t1.last_number
       where t1.name = trim(upper(p_name));

    set lv_lastn = last_insert_id();
/*
      update adm_sequence_rep set last_number=
        if(abs(lv_lastn-last_number)>cast((lv_limit/2) as UNSIGNED),least(lv_lastn,last_number),greatest(lv_lastn,last_number))
       where name = trim(upper(p_name));
*/
-- add by will 05Nov12 for HA failover
    set lv_lastn = (lv_lastn * lv_nodes_num) + lv_node_id;

    if (lv_inc_by > 0 and lv_lastn <= lv_limit) or
       (lv_inc_by < 0 and lv_lastn >= lv_limit) then

      return lv_lastn;
    elseif upper(lv_cycle)='Y' then
      update adm_sequence set last_number=lv_init where name = trim(upper(p_name));
      return lv_init;
    else
--      select 1 into @1 from Err_The_NextVal_Exceed_MaxValue;
		SIGNAL SQLSTATE '45101'
			SET MESSAGE_TEXT = 'Error: The nextvalue of sequence exceeded the maxvalue.';
    end if;

  end $$

DELIMITER ;