-- table
DROP TABLE IF EXISTS `adm_sequence_rep`;
CREATE TABLE `adm_sequence_rep` (
  `PKEY` int(10) NOT NULL,
  `NAME` varchar(30) COLLATE utf8_bin NOT NULL,
  `INIT_NUMBER` bigint(20) NOT NULL,
  `LAST_NUMBER` decimal(30,0) NOT NULL,
  `MAX_NUMBER` decimal(30,0) NOT NULL,
  `INCREMENT_BY` int(11) NOT NULL,
  `CYCLE_FLAG` varchar(1) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`PKEY`),
  UNIQUE KEY `idx_adm_seq_rep_name` (`NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

insert into adm_sequence_rep (select * from adm_sequence);

-- triggers
delimiter $$
drop trigger if exists adm_seq_air_trg $$
CREATE TRIGGER adm_seq_air_trg after insert
    ON adm_sequence FOR EACH ROW
BEGIN

       insert into adm_sequence_rep values (new.pkey,new.name,new.init_number,new.last_number,
            new.max_number,new.increment_by,new.cycle_flag);

END$$
/*
drop trigger if exists adm_seq_aur_trg $$
CREATE TRIGGER adm_seq_aur_trg after update
    ON adm_sequence FOR EACH ROW
BEGIN
  if new.last_number = new.init_number then
       update adm_sequence_rep set  name=new.name, init_number=new.init_number,
             last_number=new.last_number, max_number=new.max_number,
             increment_by=new.increment_by, cycle_flag=new.cycle_flag
       where pkey=new.pkey;
  else
       update adm_sequence_rep set  name=new.name, init_number=new.init_number,
             last_number=greatest(new.last_number,last_number), max_number=new.max_number,
             increment_by=new.increment_by, cycle_flag=new.cycle_flag
       where pkey=new.pkey;
  end if;

END$$
*/
drop trigger if exists adm_seq_adr_trg $$
CREATE TRIGGER adm_seq_adr_trg after delete
    ON adm_sequence FOR EACH ROW
BEGIN

       delete from adm_sequence_rep where pkey=old.pkey;

END$$
delimiter ;

-- function

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
          + t1.increment_by)
       where t1.name = trim(upper(p_name));

    set lv_lastn = last_insert_id();

      update adm_sequence_rep set last_number=
        if(abs(lv_lastn-last_number)>cast((lv_limit/2) as UNSIGNED),least(lv_lastn,last_number),greatest(lv_lastn,last_number))
       where name = trim(upper(p_name));
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

DELIMITER $$

DROP FUNCTION IF EXISTS `func_seq_get_curr_number` $$
CREATE FUNCTION `func_seq_get_curr_number`(
p_name varchar(100)) RETURNS decimal(30,0)
    DETERMINISTIC
BEGIN
    declare lv_lastn  decimal(30,0);
    declare lv_nodes_num int(3) default @@SYNC_BINLOG+1;
    declare lv_node_id   int(3) default @@server_id;
--    select last_number into lv_lastn from adm_sequence where name = upper(p_name);
    select if(abs(t1.last_number-t2.last_number)>cast((t1.max_number/2) as UNSIGNED),
        least(t1.last_number,t2.last_number),greatest(t1.last_number,t2.last_number))
      into lv_lastn from adm_sequence t1 inner join adm_sequence_rep t2 on t1.name=t2.name
    where t1.name = trim(upper(p_name));

    set lv_lastn = (lv_lastn * lv_nodes_num) + lv_node_id;
    return lv_lastn;

  end $$

DELIMITER ;

insert into adm_sequence values ((select max(pkey)+1 from adm_sequence seq),'AQ_CEN_SID',1,0,999999999999999999999999999,1,'Y');