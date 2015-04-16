DELIMITER $$

DROP FUNCTION IF EXISTS `func_locate_isnotnum`$$
CREATE FUNCTION  `func_locate_isnotnum`(
p_str varchar(8080)) RETURNS int(11)
    Reads SQL Data
BEGIN
  declare i int default 1;
  declare lv_loc_notnumber int default 0;

    set p_str = substr(p_str,1,10);

     loop1: while i>=1 and i<=10 DO
        if substr(p_str,i,1) not REGEXP '[0-9]' then
          set lv_loc_notnumber = i;
          leave loop1;
        end if;
        set i = i+1;
     end while;


    return lv_loc_notnumber;

  end;

 $$

DELIMITER ;