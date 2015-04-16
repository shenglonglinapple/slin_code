DELIMITER $$

DROP FUNCTION IF EXISTS `tra_occ`.`func_seq_get_curr_number`$$
CREATE DEFINER=`IT271350_5`@`%` FUNCTION  `tra_occ`.`func_seq_get_curr_number`(
p_name varchar(100)) RETURNS decimal(30,0)
    DETERMINISTIC
BEGIN
    declare lv_lastn  decimal(30,0);
    declare lv_nodes_num int(3) default @@SYNC_BINLOG+1;
    declare lv_node_id   int(3) default @@server_id;

    select if(abs(t1.last_number-t2.last_number)>cast((t1.max_number/2) as UNSIGNED),
        least(t1.last_number,t2.last_number),greatest(t1.last_number,t2.last_number))
      into lv_lastn from adm_sequence t1 inner join adm_sequence_rep t2 on t1.name=t2.name
    where t1.name = trim(upper(p_name));

    set lv_lastn = (lv_lastn * lv_nodes_num) + lv_node_id;
    return lv_lastn;

  end;

 $$

DELIMITER ;