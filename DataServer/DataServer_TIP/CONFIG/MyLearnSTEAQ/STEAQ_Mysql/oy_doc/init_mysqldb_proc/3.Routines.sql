delimiter $$
drop procedure if exists prc_its_archive_cleanup$$
CREATE procedure prc_its_archive_cleanup(IN v_minutes int(11),
                    IN v_archive_date DATETIME)
begin

  #version of the Database.
  declare dbversion int(2); # 8 for Oracle8i, or 9 for Oracle9i.
  #delimeter.
  declare c_dlmtr VARCHAR(1) default ',';
  #Debug Mode.
  declare g_debug_mode VARCHAR(10) default 'DEBUG';

  declare  l_keep_time      int(11);
  declare  l_start_delete   DATETIME;
  declare  l_end_delete     DATETIME;
  declare  l_delete_command VARCHAR(1000) default NULL; # no-unicode
    #variables to substitute the bind#
  declare  v_start_date VARCHAR(20);
  declare  v_end_date   VARCHAR(20);

    #20110622 will refine
  # declare  lv_stat boolean;

  declare lv_errmsg varchar(300);
  declare lv_tab  varchar(30);
  declare lv_col varchar(30);

DECLARE no_more_rows BOOLEAN default false;

DECLARE c_get_archive_tables cursor for
      SELECT TABLE_NAME, QUERY_COL
        FROM AR_TABLES
       #where table_name <> 'EV_COMBINED'
       order by ARTABL_ID;

DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;

/*
    CURSOR c_get_storage_time IS
      SELECT ONLINE_PERIOD FROM AR_ONLINE WHERE ARONLI_ID = 1;
*/
    # 20110622 Will 1.delete orderly 2.eliminate EV_COMBINED(put it into another concurrent job)
    /*CURSOR c_get_archive_tables
    IS
    SELECT TABLE_NAME, QUERY_COL
    FROM AR_TABLES;*/



  # set default value
  if v_minutes is null or v_minutes = '' then
     set v_minutes = 5;
  end if;

  if v_archive_date is null or v_archive_date = '' then
     set v_archive_date = sysdate();
  end if;


/*
    OPEN c_get_storage_time;
    FETCH c_get_storage_time
      INTO l_keep_time;
    CLOSE c_get_storage_time;
*/

    SELECT ONLINE_PERIOD INTO l_keep_time FROM AR_ONLINE WHERE ARONLI_ID = 1;

    # delete x minute period falling outside the keep time
    set l_start_delete = v_archive_date - interval l_keep_time day - interval v_minutes minute;

    set l_end_delete   = v_archive_date - interval l_keep_time day;

    open c_get_archive_tables;
    loop_tab_rec: loop
      begin
        fetch c_get_archive_tables into lv_tab,lv_col;
        if no_more_rows then
          close c_get_archive_tables;
          leave loop_tab_rec;
        end if;

        IF lv_tab IS NOT NULL THEN
          # get the restored field for this table
          # for each table do the delete 2000 rows at a time
          # delete on restored field

          #set v_start_date = date_format(l_start_delete, '%Y-%m-%d %H:%i:%s');
          #set v_end_date   = date_format(l_end_delete, '%Y-%m-%d %H:%i:%s');


          set @l_delete_command = concat('DELETE FROM ' , lv_tab ,
                              ' WHERE ' , lv_col ,
                              ' > str_to_date(''',l_start_delete,''',''%Y-%m-%d %H:%i:%s'')' ,
                              ' AND ' , lv_col ,
                              ' < str_to_date(''',l_end_delete,''',''%Y-%m-%d %H:%i:%s'')' ,
                              ' limit 5000');

#if lv_tab='ALARM' then
#select @l_delete_command;
#end if;

        # select @l_delete_command;
          /* Used to be this (without bind variables):
                    l_delete_command := 'DELETE FROM '||c_tab_rec.table_name
              ||' WHERE '||c_tab_rec.query_col||' > TO_DATE('''||TO_CHAR(l_start_delete,'DD-MON-YYYY hh24:mi:ss')
              ||''',''DD-MON-YYYY hh24:mi:ss'')'
              ||' AND '||c_tab_rec.query_col||' < TO_DATE('''||TO_CHAR(l_end_delete,'DD-MON-YYYY hh24:mi:ss')
              ||''',''DD-MON-YYYY hh24:mi:ss'')'
              ||' AND ROWNUM <= 2000';
          */
        prepare stmt from @l_delete_command;
         loop_delete: LOOP
              #        EXECUTE IMMEDIATE l_delete_command;
              EXECUTE stmt;

              if row_count()<=0   then
                leave loop_delete;
              end if;
         END LOOP;
        deallocate prepare stmt;
        set @l_delete_command = null;

      END IF;
        #20110622 will catch error for the continuity of process
    end;
   END LOOP; # Finished deleting from all tables for this date
    

    /*    #wf: 090922: added table truncation
    execute immediate ('TRUNCATE TABLE EVENT');
    execute immediate ('TRUNCATE TABLE LO_DATAPT_STATE_CHANGE');
    execute immediate ('TRUNCATE TABLE PRINTABLE_EVENT');*/

  END$$
delimiter ;

delimiter $$
drop procedure if exists prc_its_archive_trunc$$
CREATE procedure prc_its_archive_trunc()
begin

declare i int(3) default 1;

DECLARE no_more_rows BOOLEAN default false;


DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';

DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;


    #will 20110622 retry truncate table before delete
    trc_while_1: while i>0 and i<= 10 do
      begin
        set @1 = 'go';
        TRUNCATE TABLE EVENT;
        set i = i+1;
      end;
        if @1<>'err1' then leave trc_while_1;
        end if;
    end while;

    set i = 1;
    trc_while_2: while i>0 and i<= 10 do
      begin
        set @1='go';
        TRUNCATE TABLE LO_DATAPT_STATE_CHANGE;
        set i = i+1;
      end;
        if @1<>'err1' then leave trc_while_2;
        end if;
    end while;

    set i = 1;
    trc_while_3: while i>0 and i<= 10 do
      begin
        set @1='go';
        TRUNCATE TABLE PRINTABLE_EVENT;
        set i = i+1;
      end;
        if @1<>'err1' then leave trc_while_3;
        end if;
    end while;
    set @1=null;

  END$$
delimiter ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `enqueue_audit_data`$$
CREATE PROCEDURE  `enqueue_audit_data`(
	IN p_location              VARCHAR(1000),
	IN p_message_qualifier     VARCHAR(1000),
	IN p_audit_data_dml        VARCHAR(1000))
BEGIN
	declare lv_sql varchar(1000);
	set @lv_sql = p_audit_data_dml ;
	PREPARE stmt FROM @lv_sql;
	execute stmt;
	DEALLOCATE PREPARE stmt;
	commit;
END $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_desc_have_app_state`$$
CREATE FUNCTION  `func_desc_have_app_state`(node_id      INT(20),
                                                    app_state    VARCHAR(50)) RETURNS int(20)
    DETERMINISTIC
BEGIN

      DECLARE tmpvar            BIGINT(20) DEFAULT 0;
      DECLARE l_category_node   BIGINT(20);

      SELECT p_key
        INTO l_category_node
        FROM node_type
       WHERE type_value = 1;

      SELECT COUNT(approval_state.state_value)
        INTO tmpVar
        FROM approval_state, node_tree
       WHERE     node_tree.fk_approval_state = approval_state.p_key
             AND node_tree.parent_node = node_id
             AND approval_state.state_name = app_state;

      IF (tmpVar = 0)
      THEN
         SELECT COUNT(apps.state_value)
           INTO tmpVar
           FROM approval_state apps,
                   node_tree nt
                INNER JOIN
                   (SELECT p_key
                      FROM node_tree
                     WHERE parent_node = node_id
                           AND fk_node_type = l_category_node) et
                ON nt.parent_node = et.p_key
          WHERE nt.fk_approval_state = apps.p_key
                AND apps.state_name = app_state;
      END IF;

      IF (tmpVar > 0)
      THEN
         SET tmpVar = 1;
      ELSE
         SET tmpVar = 0;
      END IF;

      RETURN (tmpvar);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_get_demand`$$
CREATE FUNCTION  `func_dr_pwr_api_get_demand`(
   pi_entitykey    INT(11),
   pi_old_cons     decimal(38,30),
   pi_new_cons     decimal(38,30)) RETURNS decimal(38,30)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_new_cons   bigINT(20);
      DECLARE v_constant   bigINT(20);

      #DECLARE  v_szconstant VARCHAR(25);

      SELECT epv2.VALUE
        INTO v_constant
        FROM entityparameter ep1,
             entityparameter ep2,
             entityparametervalue epv1,
             entityparametervalue epv2
       WHERE     ep1.NAME = 'InputDependency'
             AND epv1.parameterkey = ep1.pkey
             AND epv1.VALUE = CONCAT('', CAST(pi_entitykey AS CHAR))
             AND ep2.NAME = 'RolloverConstant'
             AND epv2.entitykey = epv1.entitykey
             AND epv2.parameterkey = ep2.pkey;

      #SET v_constant = CAST(v_szconstant AS UNSIGNED);

      IF pi_new_cons < pi_old_cons AND pi_new_cons > v_constant - 1000
      THEN
         SET v_new_cons = pi_new_cons + (v_constant - pi_old_cons) + 1;
      ELSEIF pi_new_cons < pi_old_cons AND pi_new_cons <= v_constant - 1000
      THEN
         SET v_new_cons = 0;
      # will Aug 2011
      ELSEIF v_constant IS NULL or v_constant = ''
      THEN
         SET v_new_cons = NULL;
      ELSE
         SET v_new_cons = pi_new_cons - pi_old_cons;
      END IF;

      RETURN (v_new_cons * 2);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_get_interval`$$
CREATE FUNCTION  `func_dr_pwr_api_get_interval`(
   pi_sourcedate DATETIME) RETURNS int(5)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_min_char   VARCHAR(5) DEFAULT MINUTE(pi_sourcedate);
      DECLARE v_hrs_char   VARCHAR(5) DEFAULT HOUR(pi_sourcedate);
      DECLARE v_min        INT(2) DEFAULT 0;
      DECLARE v_hrs        INT(2) DEFAULT 0;
      DECLARE v_int        INT(5) DEFAULT 0;

      SET v_min = v_min_char;
      SET v_hrs = v_hrs_char;

      IF v_min < 30
      THEN
         IF v_hrs = 0
         THEN
            SET v_int = 1;
         ELSE
            SET v_int = (v_hrs * 2 + 1);
         END IF;
      ELSE
         IF v_hrs = 0
         THEN
            SET v_int = 2;
         ELSE
            SET v_int = (v_hrs * 2 + 2);
         END IF;
      END IF;

      RETURN (v_int);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_get_setpoint`$$
CREATE FUNCTION  `func_dr_pwr_api_get_setpoint`(
	pi_entitykey INT(11)
	) RETURNS bigint(20)
    DETERMINISTIC
BEGIN
# Will Aug 2011
#This logic is yet to be defined properly via Setpoint Data Points values
#Currently this procedure is set to return 200 for "On Peak" tariff and 100 for "Off Peak" tariff and fixed dummy names of the setpoints
    DECLARE  v_loc         VARCHAR(20);
    DECLARE  v_pkey        INT(11);
    DECLARE  v_entitykey   INT(11);
    DECLARE  v_value       VARCHAR(20);

    SELECT l.NAME INTO v_loc FROM location l, entity e
    WHERE e.pkey = pi_entitykey AND e.locationkey = l.pkey;

    SELECT pkey INTO v_entitykey FROM entity
    WHERE NAME = CONCAT(v_loc , '.SYS.PWR.DMDSP.miiSYS-PwrDmdSetPoint');

    SELECT VALUE INTO v_value  FROM dr_datapoint_state
    WHERE entitykey = v_entitykey;

    RETURN (CAST(v_value AS SIGNED));
END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_get_tariff`$$
CREATE FUNCTION  `func_dr_pwr_api_get_tariff`(p_pkey INT(11)) RETURNS tinyint(2)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_loc         VARCHAR(20);
      DECLARE v_pkey        INT(11);
      DECLARE v_entitykey   INT(11);
      DECLARE v_ret         tinyINT(2);
      DECLARE v_value       VARCHAR(20);
      DECLARE v_label       VARCHAR(20);

      SELECT l.NAME
        INTO v_loc
        FROM location l, entity e
       WHERE e.pkey = p_pkey AND e.locationkey = l.pkey;

      SELECT pkey
        INTO v_entitykey
        FROM entity
       WHERE NAME =
                CONCAT(v_loc, '.SYS.PWR.DMD.diiSYS-PwrDmdTariffOffOnPeak');

      SELECT epv.VALUE
        INTO v_label
        FROM entityparametervalue epv, entityparameter ep
       WHERE     ep.NAME = 'TrueLabel'
             AND ep.pkey = epv.parameterkey
             AND epv.entitykey = v_entitykey;

      SELECT VALUE
        INTO v_value
        FROM dr_datapoint_state
       WHERE entitykey = v_entitykey;

      IF v_value IS NULL or v_value = '' OR v_label IS NULL or v_label = ''
      THEN
         SET v_ret = NULL;
      ELSE
         IF (v_value = v_label)
         THEN
            SET v_ret = 1;
         ELSE
            SET v_ret = 0;
         END IF;
      END IF;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_is_30min_pwr_point_exist`$$
CREATE FUNCTION  `func_dr_pwr_api_is_30min_pwr_point_exist`(
   pi_entitykey     INT(11),
   pi_sourcedate    DATE,
   pi_int           DECIMAL(22, 0)) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_count        INT(11) DEFAULT 0;
      DECLARE v_ret          tinyint(1) DEFAULT FALSE;
      DECLARE v_entitykey    INT(11) DEFAULT pi_entitykey;
      DECLARE v_sourcedate   DATE DEFAULT CAST(pi_sourcedate AS DATE);
      DECLARE v_int          DECIMAL(22, 0) DEFAULT pi_int;
      DECLARE v_sql          VARCHAR(1000) DEFAULT NULL;

      SELECT count(*)
        INTO v_count
        FROM dr_pwrdmd_30min_table
       WHERE     entitykey = v_entitykey
             AND CAST(sourcedate AS DATE) = v_sourcedate
             AND `int` = v_int;

      IF v_count <> 0
      THEN
         SET v_ret = TRUE;
      ELSE
         SET v_ret = FALSE;
      END IF;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_is_pwr_point`$$
CREATE FUNCTION  `func_dr_pwr_api_is_pwr_point`(pi_entitykey INT(11)) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_ret          tinyint(1);
      DECLARE v_count        INT(11);
      DECLARE v_entityname   VARCHAR(2000);

      SELECT name
        INTO v_entityname
        FROM entity
       WHERE pkey = pi_entitykey;

      IF v_entityname LIKE '%.mii%'
      THEN
         SET v_ret = TRUE;
      ELSE
         SET v_ret = FALSE;
      END IF;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_is_pwr_point_exist`$$
CREATE FUNCTION  `func_dr_pwr_api_is_pwr_point_exist`(
   pi_entitykey INT(11)) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_ret     tinyint(1);
      DECLARE v_count   INT(11);

      SELECT COUNT(*)
        INTO v_count
        FROM dr_pwrdmd_data
       WHERE entitykey = pi_entitykey;

      IF v_count <> 0
      THEN
         SET v_ret = TRUE;
      ELSE
         SET v_ret = FALSE;
      END IF;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_dr_pwr_api_is_pwr_point_same`$$
CREATE FUNCTION  `func_dr_pwr_api_is_pwr_point_same`(
   pi_entitykey     INT(11),
   pi_sourcedate    DATETIME) RETURNS tinyint(1)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE v_ret     tinyint(1);
      DECLARE v_count   INT(11);

      SELECT COUNT(*)
        INTO v_count
        FROM dr_pwrdmd_data
       WHERE entitykey = pi_entitykey AND sourcedate = pi_sourcedate;

      IF v_count <> 0
      THEN
         SET v_ret = TRUE;
      ELSE
         SET v_ret = FALSE;
      END IF;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_ev_api_get_dpstatechange_range`$$
CREATE FUNCTION  `func_ev_api_get_dpstatechange_range`() RETURNS varchar(51) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE v_min         INT(11);
 DECLARE v_max         INT(11);
 DECLARE v_next_number INT(11);
 DECLARE v_maxdate     VARCHAR(15);
 DECLARE v_mindate     VARCHAR(15);
 DECLARE v_ret         VARCHAR(51);

 CALL prc_ev_api_get_dpstatechange_min_data(v_min,v_mindate);
 CALL prc_ev_api_get_dpstatechange_max_data(v_max,v_maxdate,v_next_number);

 IF v_maxdate <= v_mindate THEN 
#We apparently hit the boundaries of event_seq.
#Retrieve real min and max event datetime range, and pkey of the first record in that range.
#get real start

  SELECT ukey,DATE_FORMAT(logtime, '%Y%m%d%H%i%S')
  INTO v_min, v_mindate
  FROM  lo_datapt_state_change
  WHERE ukey = (SELECT MIN(ukey) FROM lo_datapt_state_change WHERE ukey > v_next_number-1);

  SELECT ukey,DATE_FORMAT(logtime, '%Y%m%d%H%i%S')
  INTO v_max, v_maxdate
  FROM lo_datapt_state_change
  WHERE ukey = (SELECT MAX(ukey) FROM lo_datapt_state_change WHERE ukey < v_next_number);

  IF v_min IS NULL or v_min = '' OR v_max IS NULL or v_max = '' THEN
      SET v_ret = '200001010000:0000000000:200001010000:0000000000';
  ELSE
      SET v_ret =  CONCAT(v_mindate, ':', LPAD(CAST(v_min AS CHAR),10,'0'), v_maxdate, ':', LPAD(CAST(v_max AS CHAR),10,'0'));
  END IF;

ELSE
  IF v_next_number = 1 THEN 
  #We have just rolled over the sequence, oops :-)
      SELECT func_seq_get_next_number('event_seq') INTO v_next_number;
  END IF;
  #Just return the range as it is.
  SET v_ret = CONCAT(v_mindate, ':', LPAD(CAST(v_min AS CHAR),10,'0'), ':',  v_maxdate, ':', LPAD(CAST(v_max AS CHAR),10,'0'));
END IF;

 RETURN v_ret;

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_ev_api_get_event_end_data`$$
CREATE FUNCTION  `func_ev_api_get_event_end_data`() RETURNS varchar(25) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE v_end         INT(11);
 DECLARE v_enddate     VARCHAR(15);
 DECLARE v_next_number INT(11);
 DECLARE v_ret         VARCHAR(25);

 SELECT DATE_FORMAT(logtime, '%Y%m%d%H%i%S'), MAX(pkey) INTO v_enddate,v_end
 FROM event WHERE logtime = (SELECT MAX(logtime) FROM event) GROUP BY logtime;
  IF v_end IS NULL or v_end = '' THEN
    SET v_ret = '200001010000:0000000000';
  ELSE
   SET v_ret = CONCAT(v_enddate, ':', LPAD(CAST(v_end AS CHAR),10,'0'));
  END IF;
 RETURN v_ret;

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_ev_api_get_event_range`$$
CREATE FUNCTION  `func_ev_api_get_event_range`() RETURNS varchar(51) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE v_min         INT(11);
 DECLARE v_mindate     VARCHAR(15);
 DECLARE v_max         INT(11);
 DECLARE v_maxdate     VARCHAR(15);
 DECLARE v_next_number INT(11);
  DECLARE v_ret         VARCHAR(51);
 #DECLARE v_ret         VARCHAR(51) DEFAULT '200001010000:0000000000:200001010000:0000000000';

 CALL prc_ev_api_get_event_min_data(v_min,v_mindate);
 CALL prc_ev_api_get_event_max_data(v_max,v_maxdate,v_next_number);
 IF v_maxdate <= v_mindate THEN
#We apparently hit the boundaries of event_seq.
#Retrieve real min and max event datetime range, and pkey of the first record in that range.
#get real start
  SELECT pkey, DATE_FORMAT(logtime, '%Y%m%d%H%i%S') INTO v_min, v_mindate
  FROM event
  WHERE pkey = (SELECT MIN(pkey) FROM event WHERE pkey > v_next_number-1);
#get real end
  SELECT pkey, DATE_FORMAT(logtime, '%Y%m%d%H%i%S') INTO v_max, v_maxdate
  FROM event
  WHERE pkey = (SELECT MAX(pkey) FROM event WHERE pkey < v_next_number);
   IF v_min IS NULL or v_min = '' OR v_max IS NULL or v_max = '' THEN
    SET v_ret = '200001010000:0000000000:200001010000:0000000000';
   ELSE
  SET v_ret = CONCAT(v_mindate, ':', LPAD(CAST(v_min AS CHAR),10,'0'), ':', v_maxdate, ':', LPAD(CAST(v_max AS CHAR),10,'0'));
   END IF;
 ELSE
  IF v_next_number = 1 THEN
   SELECT seq_nextval('event_seq') INTO v_next_number;
  END IF;
#Just return the range as it is.
  SET v_ret = CONCAT(v_mindate, ':', LPAD(CAST(v_min AS CHAR),10,'0'), ':', v_maxdate, ':', LPAD(CAST(v_max AS CHAR),10,'0'));
 END IF;
 RETURN v_ret;

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_ev_api_get_event_start_data`$$
CREATE FUNCTION  `func_ev_api_get_event_start_data`() RETURNS varchar(25) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE v_start        INT(11) DEFAULT 0;
 DECLARE v_startdate    VARCHAR(15) DEFAULT NULL;
 DECLARE v_ret          VARCHAR(25) DEFAULT NULL;
 #DECLARE v_min_logtime  DATETIME;

 #SELECT MIN(logtime) INTO v_min_logtime FROM event ;
 SELECT DATE_FORMAT(logtime, '%Y%m%d%H%i%S'), MIN(pkey)
 INTO v_startdate,v_start FROM event
 WHERE logtime = (SELECT MIN(logtime) FROM event)
  GROUP BY logtime;
  IF v_start <> '' THEN
   SET v_ret = CONCAT(v_startdate, ':', LPAD(CAST(v_start AS CHAR),10,'0'));
  ELSE
    SET v_ret = '200001010000:0000000000';
  END IF;
  RETURN v_ret;

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_get_entitykey`$$
CREATE FUNCTION  `func_get_entitykey`(p_name VARCHAR(50)) RETURNS int(11)
    DETERMINISTIC
BEGIN
      # Will Aug 2011
      DECLARE v_ret   INT(11) DEFAULT NULL;

      SELECT pkey
        INTO v_ret
        FROM entity
       WHERE name LIKE p_name;

      RETURN (v_ret);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_get_entityname`$$
CREATE FUNCTION  `func_get_entityname`(
 p_entitykey INT(11)
 ) RETURNS varchar(85) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE  v_ret VARCHAR(85) DEFAULT NULL;
 SELECT name INTO v_ret FROM entity WHERE pkey = p_entitykey;

 RETURN (v_ret);

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_get_entityparametervalue`$$
CREATE FUNCTION  `func_get_entityparametervalue`(
 p_entitykey     INT(9) ,
 p_typename      VARCHAR(85),
 p_parametername VARCHAR(85)
    ) RETURNS varchar(2000) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE  v_ret  VARCHAR(2000) DEFAULT NULL;

 SELECT value INTO v_ret FROM entityparametervalue
 WHERE entitykey = p_entitykey AND parameterkey =
 (SELECT pkey FROM entityparameter WHERE UPPER(name)= UPPER(p_parametername) AND typekey =
 (SELECT pkey FROM entitytype WHERE name = p_typename));

 RETURN (v_ret);

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_get_interval`$$
CREATE FUNCTION  `func_get_interval`(pi_sourcedate datetime) RETURNS int(11)
    DETERMINISTIC
BEGIN
# Will Aug 2011
       declare v_min_char   VARCHAR (5) DEFAULT Minute(pi_sourcedate);
       declare v_hrs_char   VARCHAR (5) DEFAULT Hour(pi_sourcedate);
       DECLARE v_min        INT(11);
       DECLARE v_hrs        INT(11);
       DECLARE v_int        INT(11);

      set v_min = v_min_char;
      set v_hrs = v_hrs_char;

      IF v_min < 30
      THEN
         IF v_hrs = 0
         THEN
            set v_int = 1;
         ELSE
            set v_int = (v_hrs * 2 + 1);
         END IF;
      ELSE
         IF v_hrs = 0
         THEN
            set v_int = 2;
         ELSE
            set v_int = (v_hrs * 2 + 2);
         END IF;
      END IF;

      RETURN (v_int);

END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_get_plan_path`$$
CREATE FUNCTION  `func_get_plan_path`(
 p_node_id   INT(9)
 ) RETURNS varchar(600) CHARSET utf8
    DETERMINISTIC
BEGIN
# Will Aug 2011
 DECLARE v_parent_node_id INT(9);
 DECLARE v_node_name      VARCHAR(150);
 DECLARE v_path           VARCHAR(600) default '';

 DECLARE PATH_SEPARATOR   VARCHAR(1)   DEFAULT '/';

# Get the parent of the specified node.
   SELECT parent_node INTO v_parent_node_id
   FROM node_tree
   WHERE p_key = p_node_id;

# If the node has no parent, it must be the root of the plan tree.
# The root is denoted with a single '/'.
    IF v_parent_node_id IS NULL or v_parent_node_id = '' THEN
        RETURN (PATH_SEPARATOR);
    END IF;
    
    WHILE v_parent_node_id <> '' DO
# Get the node's name.
        SELECT name INTO v_node_name
        FROM node_tree
        WHERE p_key = p_node_id;

# Append the node's name to the path of its parent node.
# Separate the two with a single '/'.

       SET v_path = concat(PATH_SEPARATOR , v_node_name, TRIM(TRAILING PATH_SEPARATOR FROM v_path));
       SET p_node_id = v_parent_node_id;
       
       SELECT parent_node INTO v_parent_node_id
        FROM node_tree
        WHERE p_key = p_node_id;
        
    END WHILE;
    
       RETURN (v_path);
  
END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_has_children`$$
CREATE FUNCTION  `func_has_children`(node_id INT(9)) RETURNS int(9)
    DETERMINISTIC
BEGIN
      # Will Aug 2011
      DECLARE tmpvar   INT(9) DEFAULT 0;

      SELECT count(node_tree.P_KEY)
        INTO tmpVar
        FROM node_tree
       WHERE node_tree.parent_node = node_id;

      IF (tmpVar > 0)
      THEN
         SET tmpVar = 1;
      ELSE
         SET tmpVar = 0;
      END IF;

      RETURN (tmpvar);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_is_plan_edit_locked`$$
CREATE FUNCTION  `func_is_plan_edit_locked`(v_node_id     INT(9),
                                                    v_time_out    INT(11)) RETURNS int(2)
    DETERMINISTIC
BEGIN
# Will Aug 2011
      DECLARE l_return       INT(2) DEFAULT 1;
      DECLARE l_time_stamp   DATETIME;

      SELECT node_tree.edit_time_stamp
        INTO l_time_stamp
        FROM node_tree
       WHERE p_key = v_node_id;

      IF (l_time_stamp IS NULL or l_time_stamp = '')
      THEN
         SET l_return = 0;
      ELSE
         SELECT node_tree.edit_time_stamp
           INTO l_time_stamp
           FROM node_tree
          WHERE p_key = v_node_id;

         IF (SYSDATE() > (l_time_stamp + v_time_out))
         THEN
            SET l_return = 0;
         END IF;
      END IF;

      RETURN (l_return);
   END;

 $$

DELIMITER ;

DELIMITER $$

DROP FUNCTION IF EXISTS `func_ltrim`$$
CREATE FUNCTION  `func_ltrim`(
  p_char varchar(2000),
  p_set  varchar(2000)
 ) RETURNS varchar(2000) CHARSET utf8
    DETERMINISTIC
begin

  declare lv_str varchar(2000) default p_char;
  declare n bigint(20) default 1;

 if p_char is null or p_char = '' or p_set is null or p_set = ''
    or char_length(p_char) = 0 or char_length(p_set) = 0 then
      return null;
 end if;


while n>0 and n<=char_length(p_char) do
   if  instr(binary p_set,substr(p_char,n,1))>0 then
       set lv_str = substr(p_char,n+1,char_length(p_char));
       set n = n+1;
   else
       set n = char_length(p_char)+1000;
   end if;

end while;

return lv_str;

end;

 $$

DELIMITER ;

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

DELIMITER $$

DROP FUNCTION IF EXISTS `func_strcmpincase`$$
CREATE FUNCTION  `func_strcmpincase`(
	p_str1        VARCHAR(2000),
	p_str2        VARCHAR(2000)
) RETURNS int(1)
    DETERMINISTIC
BEGIN
	DECLARE  v_ret_value    INT(1) DEFAULT 0;
	DECLARE  v_fetch_num    INT(1) DEFAULT 1;
	DECLARE  v_str1_size    INT(9) DEFAULT 0;
	DECLARE  v_str2_size    INT(9) DEFAULT 0;
	DECLARE  v_scanstr_pos  INT(9) DEFAULT 1;
	DECLARE  v_substr1      VARCHAR(1) DEFAULT NULL;
	DECLARE  v_substr2      VARCHAR(1) DEFAULT NULL;
	
	IF (p_str1 IS NULL or p_str1 = '') AND (p_str2 IS NULL or p_str2 = '') THEN
		RETURN (v_ret_value);
	END IF;
	
	SET v_str1_size = CHAR_LENGTH(p_str1);
	SET v_str2_size = CHAR_LENGTH(p_str2);
	
	IF v_str1_size <> v_str2_size THEN
		SET v_ret_value = 1;
		RETURN (v_ret_value);
	END IF;
	
	the_compare_loop: LOOP
		IF (v_scanstr_pos = v_str1_size) AND (v_scanstr_pos = v_str2_size) THEN
			SET v_substr1 = SUBSTR(p_str1, v_scanstr_pos, v_fetch_num);
			SET v_substr2 = SUBSTR(p_str2, v_scanstr_pos, v_fetch_num);
			IF (HEX(v_substr1) <> HEX(v_substr2)) THEN
				SET v_ret_value = 1;
			ELSE
				SET v_ret_value = 0;
			END IF;
			LEAVE the_compare_loop;
		END IF;
		
		SET v_substr1 = SUBSTR(p_str1, v_scanstr_pos, v_fetch_num);
		SET v_substr2 = SUBSTR(p_str2, v_scanstr_pos, v_fetch_num);
		IF (HEX(v_substr1) <> HEX(v_substr2)) THEN
			SET v_ret_value = 1;
			LEAVE the_compare_loop;
		END IF;
		
		SET v_scanstr_pos = v_scanstr_pos + 1;
	END LOOP the_compare_loop;

	RETURN (v_ret_value);
	
END;

 $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_agent_config_change_child_agent`$$
CREATE PROCEDURE  `prc_agent_config_change_child_agent`(
      IN v_entitykey   int(9),
      IN v_entityarr   varchar(4000),
      IN v_agentkey    int(9)
   )
Begin

-- Note: The form of v_entiyarr: '1;2;' or null.

      -- output array
      declare l_outarr  varchar(4000) default '';
      -- input array
      declare l_inparr  varchar(4000) default '';
      declare l_entitykey   int(9);
      declare l_count       int(11)  default 0;

      declare c_entitykey   int(9);
      declare l_inparr_cnt     int(11);
      declare l_outarr_cnt    int(11);
      declare i int(11) default 1;
      declare lv_entitykey  int(9);
	    DECLARE  no_more_rows  BOOLEAN DEFAULT FALSE;

      declare c_get_children cursor for
         SELECT pkey
           FROM entity
          WHERE parentkey = c_entitykey AND pkey <> c_entitykey;

	    DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;
      DECLARE EXIT HANDLER FOR SQLEXCEPTION ROLLBACK;
      # DECLARE EXIT HANDLER FOR SQLWARNING ROLLBACK;


      START TRANSACTION;

      IF v_entityarr IS NULL or v_entityarr = ''
      THEN
	     -- This is the original entity whose agentkey was changed
         set l_inparr = concat(v_entitykey,';');
      ELSE
	     -- this is tha array of parent entities from the previous invocation
         set l_inparr = v_entityarr;
      END IF;

      select char_length(l_inparr)-char_length(replace(l_inparr,';','')) into l_inparr_cnt;

      While i>0 and i<=l_inparr_cnt do
	  -- Cycle through all parents
      set c_entitykey = substring_index(l_inparr,';',1);
      set l_inparr = substr(l_inparr,instr(l_inparr,';')+1);

      open c_get_children;

      the_loop_1: LOOP

         -- Get all children for each of the parents
        fetch c_get_children into lv_entitykey;

		IF no_more_rows THEN
			CLOSE c_get_children;
			LEAVE the_loop_1;

		END IF;

            IF lv_entitykey <> ''
            THEN
               set l_count = l_count + 1;
			   -- Assign the child to the new array
               set l_outarr = concat(l_outarr,';',lv_entitykey);
               set l_outarr = trim(leading ';' from l_outarr);
			   -- Change agentkey for the child record
               UPDATE entity
                  SET agentkey = v_agentkey
                WHERE pkey = lv_entitykey;
            END IF;


      END LOOP the_loop_1;

      set i = i+1;
         COMMIT; -- after each parent cycle
      END while;

      select char_length(l_outarr)-char_length(replace(l_outarr,';','')) into l_outarr_cnt;

      IF l_outarr_cnt > 0
      THEN
         call prc_agent_config_change_child_agent (NULL, l_outarr, v_agentkey);
	  -- else we're finished
      END IF;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_check_record`$$
CREATE PROCEDURE  `prc_check_record`(
   IN p_table       VARCHAR(50),
   IN p_colval      VARCHAR(100),
   IN p_colkey      VARCHAR(50),
	 IN p_value       VARCHAR(50),
   OUT p_key        INT(20)
   )
BEGIN
	DECLARE  v_select   VARCHAR(1000);

  # set default value
  if p_colval is null or p_colval = '' then
    set p_colval = 'NAME';
  end if;
  if p_colkey is null or p_colkey = '' then
    set p_colkey = 'PKEY';
  end if;

  set v_select = CONCAT('SELECT ', p_colkey,' INTO @g_tmp_key FROM ', p_table, ' WHERE ', p_colval, ' IN (''', p_value, ''')') ;
	#DECLARE  cu_key     
	set @g_tmp_key = null;
  set @gv_str = v_select;	
  prepare stmt from @gv_str;
  execute stmt;
  deallocate prepare stmt;
  set @gv_str='';
  
      set p_key = @g_tmp_key;
      set @g_tmp_key='';
      IF p_key IS NULL or p_key = '' THEN
	  	  set p_key = -1;     
	    END IF;
      
  select p_key;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_copy_equip_report_data`$$
CREATE PROCEDURE  `prc_copy_equip_report_data`(
 IN v_SourceReportKey  VARCHAR(40),
 IN v_NewReportKey     VARCHAR(40)
 )
BEGIN
# Modified Sept 2011
 DECLARE  lv_datanode_id   INT(9);
 DECLARE  lv_datapoint_id  INT(9);
 DECLARE  lv_scerep_id     VARCHAR(40) DEFAULT NULL;
 DECLARE  no_more_rows    BOOLEAN DEFAULT FALSE;


 DECLARE  c_get_report CURSOR FOR
 SELECT SCEREP_ID, DATANODE_ID, DATAPOINT_ID FROM sc_equip_report_entities
 WHERE SCEREP_ID = v_SourceReportKey;

 DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;

 OPEN c_get_report;
 the_report_loop: LOOP
  FETCH c_get_report INTO lv_scerep_id, lv_datanode_id, lv_datapoint_id;
  IF no_more_rows THEN
   LEAVE the_report_loop;
  END IF;
  BEGIN
   INSERT INTO sc_equip_report_entities(SCEREN_ID, SCEREP_ID, DATANODE_ID, DATAPOINT_ID)
   VALUES(get_uuid, v_NewReportKey, v_datanode_id, v_datapoint_id);
  END;

 END LOOP the_report_loop;
  CLOSE c_get_report;

 COMMIT;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_copy_plan`$$
CREATE PROCEDURE  `prc_copy_plan`(
	IN v_source_plan_pkey      INT(11),
	IN v_target_category_pkey  INT(11),
        IN v_plan_name             VARCHAR(150),
	IN v_operator_name         VARCHAR(85) 
	)
BEGIN	
	DECLARE JUMP_STEP                INT(11);
	DECLARE DECISION_STEP            INT(11);
	DECLARE ACTIVE_PLAN_CHECK_STEP   INT(11);
	DECLARE DATA_POINT_CHECK_STEP    INT(11);
	DECLARE EVALUATE_EXPRESSION_STEP INT(11);
	DECLARE RUN_PLAN_STEP            INT(11);
	DECLARE TERMINATE_PLAN_STEP      INT(11);	
	DECLARE l_plan_pkey 			 INT(11);
	DECLARE l_step_pkey              INT(11);
	DECLARE l_step_parameter_pkey    INT(11);
	DECLARE l_node_type 			 INT(11);	
	DECLARE l_step_number 			 INT(11);
	DECLARE l_is_step_number         INT(11);
	DECLARE l_is_plan_path           INT(11);  
	DECLARE v_step_number_len        INT(11);
	DECLARE no_more_rows             BOOLEAN;
	DECLARE l_plan_path              VARCHAR(600);
	DECLARE l_plan_description       VARCHAR(4000);
	DECLARE STEP_NUMBER_PREFIX       VARCHAR(1)   DEFAULT  '#';
	DECLARE l_source_plan_path       VARCHAR(600) DEFAULT  NULL ; 
	
	
	DECLARE v_details_p_key          INT(9);
	DECLARE v_details_fk_step_type   INT(9);
    DECLARE v_details_position       INT(9);
    DECLARE v_details_name           VARCHAR(150);
    DECLARE v_details_description    VARCHAR(500);
    DECLARE v_details_skippable      INT(2);
    DECLARE v_details_skip           INT(2);
    DECLARE v_details_ignore_failure INT(2);
    DECLARE v_details_delay          INT(9);
    DECLARE v_details_no_wait        INT(2);
	
	
	DECLARE v_parameters_p_key       INT(9);
	DECLARE v_parameters_position    INT(9);
	DECLARE v_parameters_value       VARCHAR(1000);	

	DECLARE  c_plan_steps_source CURSOR FOR
	SELECT p_key, fk_step_type, position, name, description, skippable, skip, ignore_failure, delay, no_wait
	FROM step_details WHERE  fk_node_tree = v_source_plan_pkey;

	DECLARE  c_plan_steps_pkey  CURSOR FOR
	SELECT p_key, fk_step_type, position, name, description, skippable, skip, ignore_failure, delay, no_wait
	FROM step_details WHERE  fk_node_tree = l_plan_pkey;

	DECLARE  c_plan_step_parameters CURSOR FOR
	SELECT p_key, position, value  
	FROM step_parameters WHERE  fk_step_details = v_details_p_key;
	
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;

	SET l_source_plan_path = func_get_plan_path(v_source_plan_pkey);

    
    SELECT fk_node_type, description
    INTO   l_node_type,  l_plan_description
    FROM   node_tree
    WHERE  p_key = v_source_plan_pkey;

    
	SELECT func_seq_get_next_number('plans_seq') INTO l_plan_pkey ;

    
    INSERT INTO node_tree (p_key, parent_node, fk_node_type, name, description, node_created_by, node_modified_by, approval_modified_by,
        fk_approval_state, date_modified, approval_date_modified)
    VALUES(l_plan_pkey, v_target_category_pkey, l_node_type, v_plan_name, l_plan_description, v_operator_name, v_operator_name,v_operator_name,
        (SELECT p_key FROM approval_state WHERE state_name = 'Unapproved'), SYSDATE(), SYSDATE() );

    
	SET l_plan_path = func_get_plan_path(l_plan_pkey);

    
	OPEN c_plan_steps_source ;
	the_step_source_loop: LOOP
		SET no_more_rows = FALSE;
		FETCH c_plan_steps_source 
		INTO v_details_p_key, v_details_fk_step_type, v_details_position, v_details_name, v_details_description, v_details_skippable, 
			 v_details_skip, v_details_ignore_failure, v_details_delay, v_details_no_wait ;
		
		
		
		IF no_more_rows THEN
			CLOSE c_plan_steps_source;
			LEAVE the_step_source_loop;
		END IF;
		SELECT func_seq_get_next_number('plans_seq') INTO l_step_pkey ;
		INSERT INTO step_details (p_key,fk_node_tree,fk_step_type,position,name, description,skippable,skip,ignore_failure,delay,no_wait)
        VALUES(l_step_pkey,l_plan_pkey, v_details_fk_step_type, v_details_position, v_details_name,v_details_description, v_details_skippable,
            v_details_skip, v_details_ignore_failure, v_details_delay, v_details_no_wait);
		
		
		SET no_more_rows = FALSE;
		OPEN c_plan_step_parameters ;
		the_step_parameters_loop: LOOP
			FETCH c_plan_step_parameters INTO v_parameters_p_key, v_parameters_position, v_parameters_value ;
			
			
			
			IF no_more_rows THEN
				CLOSE c_plan_step_parameters ;
				LEAVE the_step_parameters_loop ;
			END IF;
			SELECT func_seq_get_next_number('plans_seq') INTO l_step_parameter_pkey ;
			INSERT INTO step_parameters (p_key, fk_step_details, position, value)
            VALUES(l_step_parameter_pkey,l_step_pkey, v_parameters_position, v_parameters_value);
		
		END LOOP the_step_parameters_loop;		
		
	END LOOP the_step_source_loop ;    

    
    
    
    
    SELECT p_key INTO JUMP_STEP                FROM step_type WHERE type_name = 'Jump';
    SELECT p_key INTO DECISION_STEP            FROM step_type WHERE type_name = 'Decision';
    SELECT p_key INTO ACTIVE_PLAN_CHECK_STEP   FROM step_type WHERE type_name = 'Active Plan Check';
    SELECT p_key INTO DATA_POINT_CHECK_STEP    FROM step_type WHERE type_name = 'Data Point Check';
    SELECT p_key INTO EVALUATE_EXPRESSION_STEP FROM step_type WHERE type_name = 'Evaluate Expression';
    SELECT p_key INTO RUN_PLAN_STEP            FROM step_type WHERE type_name = 'Run Plan';
    SELECT p_key INTO TERMINATE_PLAN_STEP      FROM step_type WHERE type_name = 'Terminate Plan';

	OPEN c_plan_steps_pkey ;
	the_step_pkey_loop: LOOP
		SET no_more_rows = FALSE;
		FETCH c_plan_steps_pkey
		INTO v_details_p_key, v_details_fk_step_type, v_details_position, v_details_name, v_details_description, v_details_skippable,
			 v_details_skip, v_details_ignore_failure, v_details_delay, v_details_no_wait ;
		
		
		
		IF no_more_rows THEN
			CLOSE c_plan_steps_pkey;
			LEAVE the_step_pkey_loop;
		END IF;
		
		SET no_more_rows = FALSE;
		OPEN c_plan_step_parameters ;
		the_step_parameters_loop2: LOOP
			FETCH c_plan_step_parameters INTO v_parameters_p_key, v_parameters_position, v_parameters_value ;
			
			
			
			IF no_more_rows THEN
				CLOSE c_plan_step_parameters ;
				LEAVE the_step_parameters_loop2 ;
			END IF;
			
            IF ((v_details_fk_step_type = JUMP_STEP                AND v_parameters_position = 1)       OR
                (v_details_fk_step_type = DECISION_STEP            AND v_parameters_position IN (3, 4)) OR
                (v_details_fk_step_type = ACTIVE_PLAN_CHECK_STEP   AND v_parameters_position IN (2, 3)) OR
                (v_details_fk_step_type = DATA_POINT_CHECK_STEP    AND v_parameters_position IN (4, 5)) OR
                (v_details_fk_step_type = EVALUATE_EXPRESSION_STEP AND v_parameters_position IN (2, 3)))
            THEN
				
                
                
                
				
				SET v_step_number_len = ifnull(CHAR_LENGTH(func_ltrim(TRIM(v_parameters_value),'0123456789')),0) ;
                SET l_is_step_number  = IF( v_step_number_len = 0, 0, v_step_number_len ) ; 
				
                IF (l_is_step_number = 0) THEN
                    
                    SELECT position INTO  l_step_number FROM  step_details
                    WHERE  fk_node_tree = v_source_plan_pkey AND p_key = CAST(v_parameters_value AS UNSIGNED) ;					

                    
                    UPDATE step_parameters
                    SET    value = CONCAT(STEP_NUMBER_PREFIX , CAST(l_step_number AS CHAR))
                    WHERE  p_key = plan_step_parameter.p_key;
                END IF;
			END IF;
			
			
            IF ((v_details_fk_step_type = ACTIVE_PLAN_CHECK_STEP AND v_parameters_position = 1) OR
                (v_details_fk_step_type = RUN_PLAN_STEP          AND v_parameters_position = 1) OR
                (v_details_fk_step_type = TERMINATE_PLAN_STEP    AND v_parameters_position = 1))
            THEN
                
                
                


				SET v_step_number_len = ifnull(CHAR_LENGTH(func_ltrim(TRIM(v_parameters_value),'0123456789')),0) ;
                SET l_is_step_number  = IF( v_step_number_len = 0, 0, v_step_number_len ) ;

                
                
                IF ((l_is_plan_path = 0 AND v_source_plan_pkey = CAST(v_parameters_value AS UNSIGNED)) OR
                    (l_is_plan_path <> 0 AND l_source_plan_path = v_parameters_value)) THEN
                    
                    UPDATE step_parameters SET value = l_plan_path
                    WHERE  p_key = v_parameters_p_key;
                END IF;
            END IF;
			
		END LOOP the_step_parameters_loop2 ;
	
	END LOOP the_step_pkey_loop;    

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_create_operator`$$
CREATE PROCEDURE  `prc_create_operator`(
	IN m_name         VARCHAR(50),
	IN m_description  VARCHAR(500),
	IN m_passwd       VARCHAR(50),
	IN m_accesslevel  INT(9) ,
	IN m_issystem     INT(9)
)
BEGIN	
	DECLARE  v_accesslevel  INT(9) DEFAULT 0;
	DECLARE  v_issystem     INT(9) DEFAULT 0;
	DECLARE  v_sql          VARCHAR(2048);
	DECLARE  v_pwd          VARCHAR(50) DEFAULT 'transactive';

  # set default value.
  if m_passwd is null or m_passwd = '' then
    set m_passwd = 'transactive';
  end if;
  if m_accesslevel is null or m_accesslevel = '' then
    set m_accesslevel = 0;
  end if;
  if m_issystem  is null or m_issystem = '' then
    set m_issystem = 0;
  end if;

	
	IF m_passwd <> '' OR CHAR_LENGTH(m_passwd) > 0 THEN
		SET v_pwd = m_passwd;
	END IF;
	IF m_accesslevel <> '' THEN
		SET v_accesslevel = m_accesslevel;
	END IF;
	IF m_issystem <> '' THEN
		SET v_issystem = m_issystem;
	END IF;
	
	SET @v_sql = CONCAT('INSERT INTO OPERATOR (PKEY, NAME, PASSWD, ACCESSLEVEL, DESCRIPTION, 
						IS_SYSTEM) values (operator_seq.nextval, ''' , m_name , ''', ''' , v_pwd , ''', 
						' , v_accesslevel , ', ''' , m_description , ''', ' , v_issystem , ')');

	PREPARE stmt FROM @v_sql;
	execute stmt;
	DEALLOCATE PREPARE stmt;
  set @v_sql='';
	commit;
 
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_create_operator_profile_map`$$
CREATE PROCEDURE  `prc_create_operator_profile_map`(
	IN  p_operator VARCHAR(50),
	IN  p_profile VARCHAR(200)
)
BEGIN
	DECLARE v_operator_key  INT(9);
	DECLARE v_profile_key   INT(9);
	
	DECLARE  c_operator CURSOR FOR
	SELECT pkey FROM operator WHERE name = p_operator AND deleted = 0;

	DECLARE  c_profile CURSOR FOR
	SELECT seprof_id from se_profile where name = p_profile;
	
	OPEN c_operator;
	FETCH c_operator INTO v_operator_key;
	CLOSE c_operator;
	
	OPEN c_profile;
	FETCH c_profile INTO v_profile_key;
	CLOSE c_profile;

	INSERT INTO se_operator_profile( seopro_id, operatorkey, seprof_id ) VALUES ( func_seq_get_next_number('SECURITY_SEQ'), v_operator_key, v_profile_key );
	COMMIT;
  
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_createidx`$$
CREATE PROCEDURE  `prc_createidx`()
begin


DECLARE CONTINUE HANDLER FOR SQLSTATE '42000' SET @x2 = 1;
DECLARE CONTINUE HANDLER FOR SQLSTATE '42S02' SET @x3 = 1;
DECLARE CONTINUE HANDLER FOR SQLSTATE '23000' SET @x4 = 1;



 create index atmssz_msszone_idx on at_msszone (mss_zone);
create index atmssz_stnid_idx on at_msszone (station_id);
create index atpema_dpnametype_idx on at_psd_entity_map (data_point_nameof_type);
 create index atpema_dptype_idx on at_psd_entity_map (data_point_type);
create index atplam_platid_idx on at_platform (platform_id);
 create index atplam_platname_idx on at_platform (platform_name);
create index atplam_stnid_idx on at_platform (station_id);
create index atpoem_dpentitykey_idx on at_power_entity_map (data_point_entity_key);
create index atpoem_location_idx on at_power_entity_map (location_key);
create index attema_dpentitytype_idx on at_twp_entity_map (data_point_entity_type);
create index cocomp_category_idx on co_component (category);
create index cocomp_component_idx on co_component (component);
 create index cocomp_entitytype_idx on co_component (entitytypekey);
 create index config_vars_ndx on config_vars (var_name, var_table, var_column, var_value);
create unique index drdns_01_uk on dr_datanode_state (entitykey);
create index drlp_status_idx on dr_live_property (drlp_status);
create unique index drlp_uk on dr_live_property (drlp_identifier);
create unique index drps_01_uk on dr_datapoint_state (entitykey);
 create index drtc_propertyid_idx on dr_trend_config (property_identifier);
create index dr_trend_int10min_nu on dr_trend_interval (int10min);
create index dr_trend_int1min_nu on dr_trend_interval (int1min);
create index dr_trend_int15min_nu on dr_trend_interval (int15min);
create index dr_trend_int1hr_nu on dr_trend_interval (int1hrs);
create unique index dr_trend_int1min_un on dr_trend_interval (int1min);
create index dr_trend_int0min_nu on dr_trend_interval (int0min);
create index dr_trend_intmin_nu on dr_trend_interval (intmin);
 create index dr_trend_int30min_nu on dr_trend_interval (int30min);
create index dr_trend_int3min_nu on dr_trend_interval (int3min);
create index dr_trend_int40min_nu on dr_trend_interval (int40min);
create index dr_trend_int45min_nu on dr_trend_interval (int45min);
create index dr_trend_int4min_nu on dr_trend_interval (int4min);
 create index dr_trend_int5min_nu on dr_trend_interval (int5min);
create index dr_trend_int6min_nu on dr_trend_interval (int6min);
create index ecmmhe_ecmmod_idx on ec_master_mode_helper (ecmmod_id);
 create index ecmmhe_ecsmod_idx on ec_master_mode_helper (ecsmod_id);
 create index ecmmode_afdirect_idx on ec_master_mode (airflow_direction);
create index ecmmode_condition_idx on ec_master_mode (`condition`);
create index ecmmode_dispdirect_idx on ec_master_mode (display_direction);
create index ecmmode_eczoneid_idx on ec_master_mode (eczone_id);
 create index ecmmode_evdirect_idx on ec_master_mode (evacuation_direction);
create unique index ecmmod_uk on ec_master_mode (master_mode);
 create index ecsmode_condition_idx on ec_station_mode (`condition`);
create index ecsmode_congestlog_idx on ec_station_mode (congestion_logic);
create index ecsmode_locationkey_idx on ec_station_mode (locationkey);
create index ecsmode_operation_idx on ec_station_mode (operation);
 create index ecsmode_stnmode_idx on ec_station_mode (station_mode);
create index ecsmode_track_idx on ec_station_mode (track);
create unique index ecstationcolour_name_idx on ec_station_colour (`name`);
create unique index eczone_01_uk on ec_zone (occ_equipment_entitykey);
 create unique index eczone_0_uk on ec_zone (stn_equipment_entitykey);
create unique index entitytypeparent_keys_uk on entitytypeparent (et_key, et_parentkey);
 create index entity_agentkey_idx on entity (agentkey);
create index entity_deleted_idx on entity (deleted);
 create index entity_locationkey_idx on entity (locationkey);
create unique index entity_name_uk on entity (`name`);
create index entity_parentkey_idx on entity (parentkey);
create index entity_physical_idx on entity (physical_subsystem_key);
 create index entity_region_idx on entity (seregi_id);
 create index entity_subsystemkey_idx on entity (subsystemkey);
 create index entity_typekey_idx on entity (typekey);
 create index epv_entityparameter_idx on entityparametervalue (parameterkey);
 create index epv_value_idx on entityparametervalue (value);
create index epv_entityparameter_idx on entityparametervalue_org_merge (parameterkey);
 create index epv_value_idx on entityparametervalue_org_merge (value);
create index ep_defdatatype_idx on entityparameter (ep_default_datatype);
create index ep_typekey_idx on entityparameter (typekey);
 create index errorlog_timestamp_idx on error_log (timestamp desc);
create unique index etype_01_uk on entitytype (`name`);
 create index etype_tasubsys_idx on entitytype (ta_subsystemkey);
create unique index evcom_pkey_indx on ev_combined (pkey desc);
create index evcom_sub_time_indx on ev_combined (createtime desc, subsystem_key, physical_subsystem_key, action_id);
create unique index eventcolour_name_idx on eventcolour (`name`);
 create index eventplanmaps_01_idx on eventplanmaps (entitytypekey, entitykey, eventtypekey);
create index eventplanmaps_enabled_idx on eventplanmaps (enabled);
 create index event_alarm_idx on event (alarm_id);
create index event_createtime_idx on event (createtime desc);
 create index event_incident_idx on event (incident_id);
create unique index event_message_idx on event (message_id);
create index globalapp_fullname_idx on guiapplication (fullname);
create unique index globalapp_name_idx on guiapplication (`name`);
 create unique index gparam_01_uk on global_parameter (subsystemkey, name);
create index gparam_name_idx on global_parameter (`name`);
create index idx_alarm_acknowledged on alarm (acknowledged_by);
 create index idx_alarm_entity on alarm (entitykey);
create index idx_alarm_expired on alarm (expired);
 create index idx_alarm_state on alarm (state);
 create index idx_step_details_ntree on step_details (fk_node_tree);
create index idx_step_pars_sdetails on step_parameters (fk_step_details);
create index idx_sttype_subsystemkey on st_type (subsystemkey);
create index idx_stvalu_entitykey on st_values (entitykey);
create index ind_ev_combined_time on ev_combined (createdatetime);
create index ininci_crtoprid_idx on in_incident_report (create_operat_id);
create index ininci_crtseprofid_idx on in_incident_report (create_seprof_id);
create index ininci_entityid_idx on in_incident_report (entity_id);
create index ininci_locatiid_idx on in_incident_report (locati_id_1, locati_id_);
create index inplan_incident_idx on in_plan (ininci_id);
create index inrepo_accsepgro_idx on in_report_access (access_sepgro_id);
 create index inrepo_crtsepgro_idx on in_report_access (create_sepgro_id);
create index inrepo_isincident_idx on in_report_access (is_incident);
 create unique index lkenty_uc_enty on lk_entity_types (entity_type);
 create unique index lkinal_01_uk on lk_alias (lkirul_id, variable_name);
create index lkintlockrules_entitykey_idx on lk_interlocking_rules (entity_key);
create unique index lkvrty_uc_enty on lk_variable_types (entity_type);
create unique index loc_desc_unique on location (description);
 create unique index loc_name_uk on ti_pid_groups (location_key, name);
create unique index loc_name_unique on location (`name`);
create unique index loc_order_unique on location (order_id);
create unique index lodsch_01_uk on lo_datapt_state_change (ukey);
create index lodsch_timestamp_idx on lo_datapt_state_change (timestamp desc);
create index meatyp_memconid_idx on me_alarm_type (memcon_id);
 create unique index meatyp_uk on me_alarm_type (type_name);
 create index memcon_meecha_id_idx on me_message_context (meecha_id);
 create index memtyp_isvisible_idx on me_message_type (isvisible);
 create index memtyp_memcon_id_idx on me_message_type (memcon_id);
 create unique index memtyp_uk on me_message_type (type_name);
create unique index mmsche_uk on mm_scheduling (physicalkey);
create index namefilter_applicationkey_idx on named_filter (applicationkey);
create index namefilter_filtername_idx on named_filter (filter_name);
 create index nf_op_app_idx on named_filter (operatorkey, applicationkey);
create index nodetree_fknodetype_idx on node_tree (fk_node_type);
create index nodetree_parentnode_idx on node_tree (parent_node);
 create index onlineprint_isalarm_idx on online_printer (is_alarm);
 create index onlineprint_subsyskey_idx on online_printer (subsystemkey);
create unique index opc_dt_pt_u01 on opc_dt_pt (data_pt_name);
create index operator_deleted_idx on operator (deleted);
create index operator_issys_idx on operator (is_system);
create unique index opl_subsys_unique on online_printer (locationkey, subsystemkey, is_alarm);
create unique index padmprve_01_uk on pa_dva_message_private_version (locationkey);
create unique index padmpuve_01_uk on pa_dva_message_public_version (locationkey);
create unique index padmve_01_uk on pa_dva_message_version (locationkey);
 create unique index pastat_01_uk on pa_station (locationkey);
create unique index patmmap_01_uk on pa_tis_message_map (locationkey, id);
create unique index pazghe_01_uk on pa_zone_group_helper (pazone_id, pazgro_id);
create index pazghe_pazgroid_idx on pa_zone_group_helper (pazgro_id);
 create unique index pazgro_01_uk on pa_zone_group (locationkey, label);
 create unique index pazhel_01_uk on pa_zone_helper (pazone_id, pid_zone_equipment);
 create index pazhel_pidzoneeqp_idx on pa_zone_helper (pid_zone_equipment);
create unique index pazone_01_uk on pa_zone (stn_equipment);
create unique index pazone_0_uk on pa_zone (occ_equipment);
create unique index pazone_03_uk on pa_zone (locationkey, id);
create unique index pk_epv on entityparametervalue (pkey);
create unique index pk_alarm on alarm (alarm_id);
 create unique index pk_alarmrule on alarmrule (pkey);
 create unique index pk_alarmseverity on alarmseverity (pkey);
 create unique index pk_entityparameter on entityparameter (pkey);
 create unique index pk_entityparameterdatatype on entityparameterdatatype (pkey);
create unique index pk_entitytypepar on entitytypeparent (pkey);
create unique index pk_epv on entityparametervalue_org_merge (pkey);
create unique index pk_eventcolour on eventcolour (pkey);
create unique index pk_guiapplication on guiapplication (pkey);
 create unique index pk_location on location (pkey);
create unique index pk_online_printcfg on online_printcfg (locationkey);
create unique index pk_online_printer on online_printer (pkey);
 create unique index pk_operator on operator (pkey);
create unique index pk_subsystem on subsystem (pkey);
create unique index pk_ta_session on ta_session (pkey);
create unique index pk_user_settings on user_settings (op_key, ap_type_key, setting_name);
create unique index pk_zonetype on zonetype (pkey);
create unique index plasta_01_uk on approval_state (state_value);
create unique index plasta_0_uk on approval_state (state_name);
 create unique index plntre_child_name_uk on node_tree (name, parent_node);
create unique index plntyp_01_uk on node_type (type_value);
 create unique index plntyp_0_uk on node_type (type_name);
create index plstpt_fkparamtype_idx on step_type_parameter_types (fk_parameter_type);
 create index plstpt_fksteptype_idx on step_type_parameter_types (fk_step_type);
 create index plstpt_position_idx on step_type_parameter_types (position);
create unique index plstyp_01_uk on step_type (type_value);
 create unique index plstyp_0_uk on step_type (type_name);
create unique index prtev_01_idx on printable_event (pkey);
create index prtev_0_idx on printable_event (location_key);
create index prtev_03_idx on printable_event (alarm_id);
create index prtev_04_idx on printable_event (event_id);
create index racshi_ie on ra_call_stack_history (profile_name, location_key);
create unique index ragmem_uk on ra_group_members (group_rasubs_id, member_rasubs_id);
create unique index raigro_uk on ra_itsi_group (`name`);
 create unique index rapmem_uk on ra_patch_members (patch_rasubs_id, group_rasubs_id);
 create unique index rasdbu_01_idx on ra_speed_dial_button (rasdse_id, button_position);
create unique index rasdse_idx on ra_speed_dial_set (set_name);
create index raspeeddialset_seprofid_idx on ra_speed_dial_set (seprof_id);
create index rasubs_ie on ra_subscribers (subscriber_name);
create index rasubs_subtype_idx on ra_subscribers (subscriber_type);
create unique index recipient_unique on recipient_all (name, member);
create unique index recip_01_uk on recipient (`name`, `address`);
create unique index scciru_0_uk on sc_calculated_input_rule (rule);
create unique index scciru_03_uk on sc_calculated_input_rule (label);
 create unique index scdoas_01_uk on sc_derived_output_association (scdsta_id, output_dp_pkey);
 create index sceqrepenti_datanodeid_idx on sc_equip_report_entities (datanode_id);
 create index sceqrepenti_datapointid_idx on sc_equip_report_entities (datapoint_id);
 create index sceqrepenti_scerepid_idx on sc_equip_report_entities (scerep_id);
 create index scequipreport_location_idx on sc_equip_report (location_id);
create unique index scequipreport_repname_idx on sc_equip_report (report_name, location_id);
create unique index sciass_01_uk on sc_input_association (main_entity_pkey, input_entity_pkey, input_calc_order);
 create unique index scotal_0_uk on sc_opc_tag_alias (alias);
 create index scotal_entityid_idx on sc_opc_tag_alias (entity_id_dp);
 create index scscadasche_colocaid_idx on sc_scada_schematic (coloca_id);
create unique index scsdat_01_uk on sc_scada_datatypes (`name`);
create unique index scssch_01_uk on sc_scada_schematic (`name`);
 create unique index scssch_0_uk on sc_scada_schematic (path);
 create unique index seacti_uk on se_action (`name`);
 create index seopro_idx on se_operator_profile (operatorkey);
 create index seopro_seprof_idx on se_operator_profile (seprof_id);
create index seoreg_idx on se_operator_regions (operatorkey);
 create index seoreg_seregi_idx on se_operator_regions (seregi_id);
create index sepacc_seagro_id_indx on se_profile_access (seagro_id);
 create index sepacc_sesstaid_idx on se_profile_access (sessta_id);
create index sepacc_subsys_key_indx on se_profile_access (subsystemkey);
create unique index sepgro_uk on se_profile_group (`name`);
create index seploc_idx on se_profile_location (locationkey);
create index sepp_disp1_idx on se_profile_parameters (display_1);
 create index sepp_disp_idx on se_profile_parameters (display_);
 create index sepp_disp3_idx on se_profile_parameters (display_3);
 create index seprofile_deleted_idx on se_profile (deleted);
 create index seprofile_issys_idx on se_profile (is_system);
 create index seprofile_raigroid_idx on se_profile (raigro_id);
create unique index seprof_uk on se_profile (`name`);
create unique index septyp_uk on se_profile_type (`name`);
create unique index seregi_01_uk on se_region (`name`);
create unique index seregi_0_uk on se_region (description);
create unique index sessta_01_uk on se_subsystem_state (`name`);
 create unique index sessta_0_uk on se_subsystem_state (description);
 create index se_actgroup_map_seacti_id_indx on se_action_group_map (seacti_id);
 create index se_actgroup_map_seagro_id_indx on se_action_group_map (seagro_id);
 create index se_action_memtyp_id_indx on se_action (memtyp_id);
create index sngroupmonitor_snscgrid_idx on sn_group_monitor (snscgr_id);
create unique index snscgr_01_uk on sn_system_controller_group (`name`);
 create unique index snscon_01_uk on sn_system_controller (`name`);
 create index snsysctrl_snscgrid_idx on sn_system_controller (snscgr_id);
create unique index soscat_01_uk on so_sound_category (`name`);
create index sosoundfile_soscatid_idx on so_sound_file (soscat_id);
create index statusdata_entitykey_indx on entitystatusdata (entitykey);
create index statusdata_statustype_indx on entitystatusdata (entitystatustype);
 create index stdetail_position_idx on step_details (position);
 create index stdetail_steptype_idx on step_details (fk_step_type);
 create index stparam_position_idx on step_parameters (position);
create index subsystem_isphysical_idx on subsystem (is_physical);
 create unique index subsystem_name_uk on subsystem (`name`);
create unique index sys_c008344 on aq_timeout (pkey);
 create unique index sys_c008458 on dr_pwrdmd_config (locationkey);
create unique index sys_c008766 on naming_ports (entity_key);
create unique index sys_c009365 on vi_video_output_group (coenti_id_01, position);
 create unique index sys_c003304 on audit_data_queue_t (msgid);
 create unique index sys_c003307 on aq$_audit_data_queue_t_s (subscriber_id);
create unique index sys_c003317 on tmp_revert_tables (table_name);
create index t5_indx on t5 (seprof_id, subsystemkey, physical_subsystem_key, seacti_id, sessta_id);
 create index t6_indx on t6 (seprof_id, subsystemkey, physical_subsystem_key, seacti_id, sessta_id);
 create index t8_indx on t8 (seprof_id, subsystemkey, physical_subsystem_key, seacti_id, sessta_id);
 create index tasession_oprkey_idx on ta_session (operatorkey);
create index ta_session_locati_id_indx on ta_session (locati_id);
create index ta_session_seprof_id_indx on ta_session (seprof_id);
create index tedent_status_idx on te_directory_entry (status);
 create index tedent_tesubdid_idx on te_directory_entry (tesubd_id);
create index tesdbu_btnpos_idx on te_speed_dial_button (button_position);
create index tesdbu_tesdseid_idx on te_speed_dial_button (tesdse_id);
 create unique index tesubd_name_idx on te_subdirectory (`name`);
 create index tesubd_status_idx on te_subdirectory (status);
 create index tiadat_tipmliid_idx on ti_adhoc_default_attributes (tipmli_id);
create index tidreq_timestamp_idx on ti_display_request (timestamp);
 create index tipgro_name_idx on ti_pid_groups (`name`);
create index tipmes_mestag_idx on ti_predefined_message (message_tag);
 create index tipmes_tipmliid_idx on ti_predefined_message (tipmli_id);
 create unique index tipmli_01_uk on ti_predefined_message_library (version, library_type);
create index tipmli_libtype_idx on ti_predefined_message_library (library_type);
 create index tipmli_ver_idx on ti_predefined_message_library (version);
create index tirmes_crtdate_idx on ti_ratis_message (creation_date);
 create index tirmes_rqevett_idx on ti_ratis_message (requires_vetting);
create index tirmes_tag_idx on ti_ratis_message (tag);
 create unique index tittsc_01_uk on ti_train_time_schedule (`name`);
 create index tittse_tittscid_idx on ti_train_time_schedule_entry (tittsc_id);
create index tra_system_stats on tra_system_stats (statid, type, c5, c1, c, c3, c4, version);
create unique index trendtemplate_name_idx on trend_template (`name`);
 create index trendviewer_config_ndx on trendviewer_config (config_name, data_pt_name, data_pt_type, data_pt_color, data_pt_server, data_pt_enabled, data_pt_lbl_enabled, data_pt_lbl_name);
 create index trendviewer_formula_config_ndx on trendviewer_formula_config (config_name, data_pt_equation, data_pt_type, data_pt_color, data_pt_enabled, data_pt_lbl_enabled, data_pt_lbl_name);
 create index trendviewer_hist_config_ndx on trendviewer_hist_config (config_name, data_pt_name, data_pt_type, data_pt_color, data_pt_server, data_pt_enabled, data_pt_lbl_enabled, data_pt_lbl_name, data_pt_dt);
create index trendviewer_log_ndx on trendviewer_log (data_pt_name, data_pt_server, data_pt_value, data_pt_date);
create index trendviewer_marker_ndx on trendviewer_marker (config_name, marker_name, marker_width, marker_value, marker_enabled, marker_bcolor, marker_fcolor);
create unique index trradg_01_uk on tr_radio_group (group_tsi);
 create unique index uc_me_event_channel on me_event_channel (channel_name);
create unique index uc_me_message_context on me_message_context (context_name);
create unique index uk_entityparameter on entityparameter (name, typekey);
create unique index unique_operator_desc on operator (description);
create unique index unique_operator_name on operator (`name`);
create unique index unique_te_dir_entry_tel_number on te_directory_entry (tel_number, status);
 create unique index unique_ti_ratis_dest_dest on ti_ratis_dest (destination);
create unique index unique_ti_ratis_tag_gd on ti_ratis_tag (tag_group, detail);
create unique index u_tsds_ok_si_sn on te_speed_dial_set (operator_key, seprof_id, set_name);
create unique index vistid_loc_uk on vi_station_id (ta_location);
create unique index vistid_sid_uk on vi_station_id (station_id);

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_delete_derived_state`$$
CREATE PROCEDURE  `prc_delete_derived_state`(
    IN   p_entityname           VARCHAR(85),   
    IN   p_state_value          INT(6),
    IN   p_state_description    VARCHAR(1000), 
    IN   p_alarm_enabled        INT(3),
    IN   p_alarm_delay          INT(6),
    IN   p_alarm_message        VARCHAR(1000),
    IN   p_alarm_severity       VARCHAR(50),
    IN   p_alarm_mms            VARCHAR(50),
    IN   p_return_condition     VARCHAR(100),
    IN   p_filename             VARCHAR(256)  
)
BEGIN
    DECLARE  v_epkey  INT(11);    

    # default value
    if p_return_condition is null or p_return_condition = '' then
      set p_return_condition = ' ';
    end if;

    select pkey into v_epkey from entity where name = p_entityname;
    delete from  sc_derived_state  where derived_dp_pkey = v_epkey;
	COMMIT;
	
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_delete_plan`$$
CREATE PROCEDURE  `prc_delete_plan`( IN v_node_id  INT(11) )
BEGIN

declare lv_step_key int(11);
DECLARE no_more_rows BOOLEAN default false;
declare cu_step_det cursor for
 select p_key FROM step_details
  WHERE fk_node_tree = v_node_id;


DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;

open cu_step_det;
 the_loop_1: loop
    fetch cu_step_det into lv_step_key;
    if no_more_rows then
      close cu_step_det;
      leave the_loop_1;
    end if;

    delete from step_parameters where fk_step_details=lv_step_key;
 end loop the_loop_1;


    DELETE FROM step_details
    WHERE fk_node_tree = v_node_id;

    DELETE FROM node_tree
    WHERE p_key = v_node_id;

    COMMIT;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dp_param_list`$$
CREATE PROCEDURE  `prc_dp_param_list`(
	IN  param_list	 VARCHAR(200),
	OUT p_return	 VARCHAR(200)
	)
BEGIN
	DECLARE v_key		INT(11)  DEFAULT 0;
	DECLARE v_start		INT(11)  DEFAULT 0;
	DECLARE v_end		INT(11)  DEFAULT 0;
	DECLARE v_subStr	VARCHAR(2000) DEFAULT NULL;

	IF(param_list <> '') THEN
		SET v_key = instr(binary param_list, 'ClosedValue:');
		if (v_key = 0) then
			SET v_key = instr(binary param_list, 'DataPointValue:');
			if (v_key = 0) then
				SET v_key = instr(binary param_list, ':');
			end if;
		end if;

		
		if (v_key > 0) then
			SET v_subStr = SUBSTR(param_list, v_key);
			SET v_start  = instr(binary v_subStr, ':');
			SET v_end    = instr(binary v_subStr, ',');

			
			IF v_end < v_start THEN
			    SET p_return = SUBSTR(v_subStr, v_start+1);
			ELSE
			    SET p_return = SUBSTR(v_subStr, v_start+1, (v_end-1)-v_start);
			END IF;
		else
			SET p_return = '';
		end if;
	END IF;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dp_value_from_param_list`$$
CREATE PROCEDURE  `prc_dp_value_from_param_list`(
  IN  param_list   VARCHAR(200),
  OUT p_return     VARCHAR(200)
  )
BEGIN
	DECLARE  v_key      INT(11)  DEFAULT 0;
	DECLARE  v_start    INT(11)  DEFAULT 0;
	DECLARE  v_end      INT(11)  DEFAULT 0;
	DECLARE  v_subStr   VARCHAR(2000) DEFAULT NULL;

	IF(param_list <> '') THEN
		SET v_key = instr(binary param_list, 'ClosedValue:');
    if (v_key = 0) then
		SET v_key = instr(binary param_list, 'DataPointValue:');
      if (v_key = 0) then
        SET v_key = instr(binary param_list, ':');
      end if;
    end if;
    if (v_key > 0) then
		SET v_subStr = SUBSTR(param_list, v_key);
    SET v_start  = length(v_subStr)-length(substring_index(v_subStr,':',-1));
    SET v_end  = length(v_subStr)-length(substring_index(v_subStr,',',-1));
		IF v_end < v_start THEN
			SET p_return = SUBSTR(v_subStr, v_start+1);
		ELSE
			SET p_return = SUBSTR(v_subStr, v_start+1, (v_end-1)-v_start);
		END IF;
    else
		SET p_return = '';
    end if;
  END IF;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_create_base_table`$$
CREATE PROCEDURE  `prc_dr_api_create_base_table`(
	IN pi_table  VARCHAR(50)   
	)
BEGIN
	DECLARE v_columns       VARCHAR(2000) DEFAULT 'sourcedate DATE,timeofday NUMBER,entitykey NUMBER(9),sourcetime DATE,logtime DATE';
	DECLARE v_colname       VARCHAR(100)  DEFAULT NULL;
	DECLARE v_coltype       VARCHAR(50)   DEFAULT NULL;
	DECLARE v_createtable   VARCHAR(2000) DEFAULT NULL;
	DECLARE v_createindex1  VARCHAR(2000) DEFAULT NULL;
	DECLARE v_createindex2  VARCHAR(2000) DEFAULT NULL;
	DECLARE v_createindex3  VARCHAR(2000) DEFAULT NULL;
	DECLARE v_createtrigger VARCHAR(4000) DEFAULT NULL;
	DECLARE no_more_rows    BOOLEAN DEFAULT FALSE;
	
	DECLARE  cu_columns CURSOR FOR
	SELECT DISTINCT drlp_column,drlp_column_type FROM dr_live_property
	WHERE drlp_table = pi_table AND drlp_column <> '';
	
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;

	CALL prc_drop_object ('TABLE',UPPER(pi_table));
	OPEN cu_columns;
	the_loop: LOOP
		FETCH cu_columns INTO v_colname, v_coltype;
		IF no_more_rows THEN
			CLOSE cu_columns;
			LEAVE the_loop;
		END IF;
		IF (v_colname <> '') AND (v_coltype <> '') THEN
			SET v_columns = CONCAT(v_columns, ',',  v_colname, ' ', v_coltype);
		END IF;
	END LOOP the_loop;	
  
	SET @v_createtable = CONCAT('CREATE TABLE ' , pi_table , '(' , v_columns , ',
                     CONSTRAINT ' , SUBSTR(pi_table,1,27) , '_pk PRIMARY KEY (sourcedate,timeofday,entitykey) USING INDEX TABLESPACE hist_indx)
                     TABLESPACE hist_base');

	SET @v_createindex1 = CONCAT('CREATE INDEX ' , SUBSTR(pi_table,1,24) , '_1_idx ON ' , pi_table , '(sourcetime) TABLESPACE hist_indx');

	SET @v_createindex2 = CONCAT('CREATE INDEX ' , SUBSTR(pi_table,1,24) , '_2_idx ON ' , pi_table , '(timeofday) TABLESPACE hist_indx');

	SET @v_createindex3 = CONCAT('CREATE INDEX ' , SUBSTR(pi_table,1,24) , '_3_idx ON ' , pi_table , '(entitykey) TABLESPACE hist_indx');

	SET @v_createtrigger = CONCAT('CREATE TRIGGER ' , SUBSTR(pi_table,1,26) , '_TRG BEFORE INSERT ON ' , pi_table , ' FOR EACH ROW
	BEGIN
		DECLARE v_sourcedate DATE  DEFAULT NULL;
		SET NEW.logtime = SYSDATE();
		SET NEW.timeofday = IF(NEW.timeofday IS NULL or NEW.timeofday = '',0, NEW.timeofday);
		IF NEW.sourcedate IS NULL or NEW.sourcedate = '' OR NEW.sourcedate = STR_TO_DATE(''01/01/1970'',''%d/%m/%Y'') THEN
			SET NEW.sourcedate = CAST(NEW.sourcetime AS DATE);
			SET NEW.timeofday  = (NEW.sourcetime - NEW.sourcedate) * 86400;
		ELSE
			SET NEW.sourcedate = CAST(NEW.sourcedate AS DATE);
		END IF;

		BEGIN
			select sourcedate into v_sourcedate from dr_datapoint_date where sourcedate = NEW.sourcedate;
		END;

		if (v_sourcedate is NULL or v_sourcedate = '') then
			insert into dr_datapoint_date(sourcedate) values(NEW.sourcedate);
		end if;
	END;');
	
	PREPARE stmt FROM @v_createtable;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
  set @v_createtable='';

	PREPARE stmt FROM @v_createindex1;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
  set @v_createindex1='';

	PREPARE stmt FROM @v_createindex2;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
  set @v_createindex2='';

	PREPARE stmt FROM @v_createindex3;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
  set @v_createindex3='';
	
	PREPARE stmt FROM @v_createtrigger;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
  set @v_createtrigger='';

	UPDATE dr_live_property SET drlp_status = 'AVAILABLE' WHERE drlp_table = pi_table AND drlp_column <> '';
	COMMIT;
  
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_create_base_tables`$$
CREATE PROCEDURE  `prc_dr_api_create_base_tables`()
BEGIN
	DECLARE  no_more_rows  BOOLEAN DEFAULT FALSE;
	DECLARE  v_tablename  VARCHAR(50) DEFAULT NULL;
	DECLARE  cu_tables CURSOR FOR
	SELECT DISTINCT drlp_table FROM dr_live_property
	WHERE drlp_status = 'PENDING' AND drlp_table <> '';
	DECLARE CONTINUE HANDLER FOR NOT FOUND 
		SET no_more_rows = TRUE;

	OPEN cu_tables;
	the_loop: LOOP
		FETCH cu_tables INTO v_tablename;
		IF no_more_rows THEN
			CLOSE cu_tables;
			LEAVE the_loop;
		END IF;
		CALL prc_dr_api_create_base_table(v_tablename);
	END LOOP the_loop;
	
	COMMIT;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_create_summary_object`$$
CREATE PROCEDURE  `prc_dr_api_create_summary_object`(
	IN pi_name     VARCHAR(30),
	IN pi_select1  VARCHAR(2000),
	IN pi_select2  VARCHAR(2000)
)
BEGIN
	DECLARE v_stmnt1 VARCHAR(2000) DEFAULT NULL;
	DECLARE v_stmnt2 VARCHAR(2000) DEFAULT NULL;

	SET @v_stmnt1 = pi_select1;
	SET @v_stmnt2 = pi_select2;

	PREPARE stmt FROM @v_stmnt1;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;
	
	PREPARE stmt FROM @v_stmnt2;
	EXECUTE stmt ;
	DEALLOCATE PREPARE stmt;	

	UPDATE dr_trend_config SET DR_STATUS = 'AVAILABLE' WHERE object_name = pi_name;

	COMMIT;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_create_summary_objects`$$
CREATE PROCEDURE  `prc_dr_api_create_summary_objects`()
BEGIN
	DECLARE  v_objname     VARCHAR(30) DEFAULT NULL;
	DECLARE  v_select1     VARCHAR(2000) DEFAULT NULL;
	DECLARE  v_select2     VARCHAR(2000) DEFAULT NULL;
	DECLARE  no_more_rows  BOOLEAN DEFAULT FALSE;

	DECLARE  cu_objects CURSOR FOR
	SELECT object_name,object_select1,object_select2
	FROM dr_trend_config WHERE DR_STATUS = 'PENDING' ORDER BY dr_id;
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;

	OPEN cu_objects;
	the_loop: LOOP
		FETCH cu_objects INTO v_objname, v_select1, v_select2;
		IF no_more_rows THEN
			CLOSE cu_objects;
			LEAVE the_loop;
		END IF;
		CALL prc_dr_api_create_summary_object (v_objname,v_select1,v_select2);
	END LOOP the_loop;
  
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_drop_summary_object`$$
CREATE PROCEDURE  `prc_dr_api_drop_summary_object`(
	IN pi_type  VARCHAR(50),
	IN pi_name  VARCHAR(50)
)
BEGIN
	CALL prc_drop_object(pi_type, pi_name);
	UPDATE dr_trend_config SET DR_STATUS = 'DELETED' WHERE object_name = pi_name;

	COMMIT;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_drop_summary_objects`$$
CREATE PROCEDURE  `prc_dr_api_drop_summary_objects`()
BEGIN
	DECLARE no_more_rows  BOOLEAN DEFAULT FALSE;
	DECLARE v_type     VARCHAR(50) DEFAULT NULL;
	DECLARE v_objname  VARCHAR(50) DEFAULT NULL;
	DECLARE  cu_objects CURSOR FOR
	SELECT dr_type2,object_name FROM dr_trend_config;
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;

	OPEN cu_objects;
	the_loop: LOOP
		FETCH cu_objects INTO v_type, v_objname;
		IF no_more_rows THEN
			CLOSE cu_objects;
			LEAVE the_loop;
		END IF;
		CALL prc_dr_api_drop_summary_object(v_type, v_objname);
	END LOOP the_loop;
	
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_get_last_lp_value`$$
CREATE PROCEDURE  `prc_dr_api_get_last_lp_value`(
	IN  pi_table       VARCHAR(50),
	IN  pi_sourcedate  DATE,
	IN  pi_timeofday   INT(6),
	IN  pi_entitykey   INT(11),
	OUT po_bret        BOOLEAN
	)
BEGIN	
	DECLARE v_select VARCHAR(2000) DEFAULT NULL ;
	DECLARE v_count  INT(9) DEFAULT 0;
	DECLARE v_sourcedate  DATE;
	DECLARE v_timeofday   INT(6);
	DECLARE v_entitykey   INT(11);
	
	SET @v_sourcedate = pi_sourcedate;
	SET @v_timeofday  = pi_timeofday ;
	SET @v_entitykey  = pi_entitykey ;
	SET @v_select = CONCAT('SELECT COUNT(*) INTO @v_count FROM ', pi_table, ' WHERE sourcedate = ? AND timeofday = ? AND entitykey = ? ' );
	
	PREPARE stmt FROM @v_select;
	EXECUTE stmt USING @v_sourcedate, @v_timeofday, @v_entitykey;
	DEALLOCATE PREPARE stmt;
  set @v_select='';
  set @v_sourcedate='';
  set @v_timeofday='';
  set @v_entitykey='';
	COMMIT; 
	
	IF v_count = 0 THEN
		SET po_bret = FALSE;
	ELSE
		SET po_bret = TRUE;
	END IF;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_get_last_recorded_values`$$
CREATE PROCEDURE  `prc_dr_api_get_last_recorded_values`(
	IN  pi_property_identifier  VARCHAR(10),
	IN  pi_entitykey            INT(11),
	OUT po_sourcetime           DATE,
	OUT po_value                INT(11)
	)
BEGIN
	DECLARE v_table   VARCHAR(50) DEFAULT NULL;
	DECLARE v_column  VARCHAR(50) DEFAULT NULL; 
	DECLARE v_cursor  VARCHAR(2000) DEFAULT NULL;
	DECLARE v_maxdate DATE;
	DECLARE v_maxtimeofday INT(6)  DEFAULT 0;
	DECLARE v_entitykey    INT(11) DEFAULT pi_entitykey;
	DECLARE v_sourcetime   DATE;
	DECLARE v_value        INT(11) DEFAULT 0;
	DECLARE no_more_rows  BOOLEAN  DEFAULT FALSE;
	DECLARE  cu_table CURSOR FOR
	SELECT drlp_table,drlp_column FROM dr_live_property WHERE drlp_identifier = pi_property_identifier;	
	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;

	OPEN cu_table;
	FETCH cu_table INTO v_table,v_column;
	CLOSE cu_table;
	IF v_table <> '' AND v_column <> '' THEN
    set @v_entitykey=v_entitykey;
		SET @v_cursor = CONCAT('SELECT IF(MAX(sourcedate) IS NULL or MAX(sourcedate) = '',STR_TO_DATE(''01/01/1970 080000'',''%d/%m/%Y %H%i%S''), MAX(sourcedate)) INTO @v_maxdate FROM ',
								v_table, ' WHERE entitykey = ?');
		PREPARE stmt FROM @v_cursor;
		EXECUTE stmt USING @v_entitykey;
		DEALLOCATE PREPARE stmt;

		SET @v_cursor = CONCAT('SELECT IF(MAX(timeofday) IS NULL or MAX(timeofday) = '',0, MAX(timeofday)) INTO @v_maxtimeofday FROM ',
								v_table, ' WHERE entitykey = ? AND sourcedate = ?');
		PREPARE stmt FROM @v_cursor;
		EXECUTE stmt USING @v_entitykey, @v_maxdate;
		DEALLOCATE PREPARE stmt;
    set @v_cursor='';
    set @v_entitykey='';
    set @v_maxdate='';
		
		SET @v_cursor =  CONCAT('SELECT sourcetime,', v_column, ' INTO @v_sourcetime, @v_value FROM ', v_table,
								' WHERE entitykey = ? AND sourcedate = ? AND timeofday = ? AND ROWNUM = 1 ');
		
		PREPARE stmt FROM @v_cursor;
		EXECUTE stmt USING @v_entitykey, @v_maxdate, @v_maxtimeofday;
		DEALLOCATE PREPARE stmt;

    set @v_cursor='';
    set @v_entitykey='';
    set @v_maxdate='';
    set @v_maxtimeofday='';
		COMMIT;
		
		SET po_sourcetime = v_sourcetime;
		SET po_value = v_value;		
	END IF;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_populate_base_with_snapshot`$$
CREATE PROCEDURE  `prc_dr_api_populate_base_with_snapshot`(
 IN pi_realtime_view  VARCHAR(50)
)
BEGIN
# Modified by Will Sept 2011
 DECLARE v_sourcetable  VARCHAR(30); #Base table for the pi_property Live Property
 DECLARE v_sourceview   VARCHAR(30); #RealTime View for the pi_property Live Property
 DECLARE v_sourcecolumn VARCHAR(30); #Column in the Base table for the pi_property Live Property
 DECLARE v_property_category   VARCHAR(30); #entity type name for the Live Property
 DECLARE v_property_identifier VARCHAR(30); #Identifier of the Live Property
 DECLARE v_sourcedate DATE DEFAULT curdate(); #date of snapshot
 DECLARE v_sourcedate_char VARCHAR(20) DEFAULT date_format(curdate(),'%d-%b-%Y'); #same as above, converted to varchar2;
 DECLARE v_timeofday INT(15) DEFAULT (SUBSTR(CAST(SYSDATE() AS UNSIGNED),9) * 86400); #time (in seconds) of the snapshot
 DECLARE v_entitykey INT(9); #entitykey of the snapshot
 DECLARE v_sourcetime DATETIME; #sourcetime of the last recorded value
 DECLARE v_value INT(11); #last recorded value

 DECLARE v_dateinsource DATETIME;

 DECLARE no_more_rows  BOOLEAN DEFAULT FALSE;

#variables to hold SQL statements to be executed:
 DECLARE v_select VARCHAR(2000) DEFAULT NULL;
 DECLARE v_insert VARCHAR(2000) DEFAULT NULL;
 DECLARE v_lock VARCHAR(2000) DEFAULT NULL;

 DECLARE cu_select CURSOR FOR
 SELECT entitykey FROM entityparametervalue_v
 WHERE UPPER(parametername) = 'ENABLETRENDING'
 AND UPPER(typename) = UPPER(v_property_category) AND value = 1;
 DECLARE CONTINUE HANDLER FOR NOT FOUND
  SET no_more_rows = TRUE;

#get the name of the Base table of the Live Property for the designated table, and property category (entitytype name) of the Live property:
 SELECT source_name,source_column,property_category,property_identifier
    INTO v_sourcetable,v_sourcecolumn,v_property_category,v_property_identifier
  FROM DR_TREND_CONFIG
  WHERE UPPER(object_name) = UPPER(pi_realtime_view);
BEGIN
 err_tran:
BEGIN
 #get max populated date from the source table of the source view of the designated table:
  SET v_select = concat('SELECT MAX(sourcedate) into @v_dateinsource FROM ',v_sourcetable);
  SET @gv_select = v_select;
    PREPARE stmt FROM @gv_select;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
  SET @gv_select = NULL;
  SET v_dateinsource = @v_dateinsource;
    IF v_dateinsource IS NULL or v_dateinsource = '' THEN
    # 'Source empty. Exiting... ' exit if the source is empty
     LEAVE err_tran;
    # ELSE 'Source IS NOT empty: MAX DATE IN Source: '||TO_CHAR(v_dateinsource));
    END IF;

    SET v_sourcedate_char = date_format(v_sourcedate,'%d-%b-%Y');

  #Populate Designated Table:
   OPEN cu_select;
   #--fetch first--
  FETCH cu_select INTO v_entitykey;
  the_loop: LOOP
   #--loop through all entitykeys until finished--
   IF no_more_rows THEN
    LEAVE the_loop;
   END IF;
   CALL prc_dr_api_get_last_recorded_values(v_property_identifier,v_entitykey,v_sourcetime,v_value);
   SET v_insert = CONCAT('INSERT INTO ', pi_realtime_view, '(sourcedate,startsecond,entitykey,startdatetime,icount)
						 VALUES (?,?,?,?,?)');
      SET @gv_insert = v_insert;
   #Only process insert if values found in the base table for this entity:
   IF v_sourcetime <> '' THEN
    PREPARE stmt FROM @v_insert;
    EXECUTE stmt USING @v_sourcedate,@v_timeofday,@v_entitykey,@v_sourcetime,@v_value;
    DEALLOCATE PREPARE stmt;
   END IF;
      SET @gv_insert = NULL;
   #--fetch next--
      FETCH cu_select INTO v_entitykey;
  END LOOP the_loop;
    CLOSE cu_select;
    COMMIT;
 END;
END;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_api_populate_summary_table`$$
CREATE PROCEDURE  `prc_dr_api_populate_summary_table`(
	IN  pi_table  VARCHAR(50)
	)
BEGIN
	DECLARE v_jobseq       INT(11) DEFAULT 0;       
	DECLARE v_jobstart     DATE DEFAULT SYSDATE();  
	DECLARE v_jobtimeofday INT(15) DEFAULT CAST(SUBSTR(CAST(CAST(SYSDATE() AS UNSIGNED) AS CHAR), 9) AS UNSIGNED) * 86400;	
	DECLARE v_sourceview VARCHAR(30);    
	DECLARE v_intervalseconds INT(11);   
	DECLARE v_sourcetable VARCHAR(30);   
	DECLARE v_sourcedate DATE DEFAULT NULL; 
	DECLARE v_timeofday  INT(16);
	DECLARE v_datetime   DATE;           
	DECLARE v_dateinsource DATE;         
	DECLARE v_timeinsource INT(11);
	DECLARE v_sourcedatetime DATE;       


	#DECLARE v_select VARCHAR(2000)  DEFAULT '';
	DECLARE v_insert VARCHAR(2000)  DEFAULT '';
	DECLARE v_where  VARCHAR(2000)  DEFAULT '';
	#DECLARE v_lock   VARCHAR(2000)  DEFAULT '';
	
	DECLARE v_diff INT(9);          
	DECLARE v_rows INT(9) DEFAULT 0;
	
	do_the_work:
	BEGIN
		
		SELECT func_seq_get_next_number('DR_JOB_SEQ') INTO v_jobseq ;

		
		SELECT source_name,interval_seconds INTO v_sourceview,v_intervalseconds FROM dr_trend_config WHERE object_name = pi_table;
		SET v_insert = CONCAT('INSERT INTO ' , pi_table , ' SELECT sourcedate,startsecond,entitykey,icount,iavg,imin,imax,isum FROM ' ,v_sourceview);


		SELECT source_name INTO v_sourcetable FROM dr_trend_config WHERE UPPER(object_name) = UPPER(v_sourceview);

		
		SET @v_select = CONCAT('SELECT MAX(sourcedate) INTO ',v_sourcedate,' FROM ' , pi_table);
		PREPARE stmt FROM @v_select;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
    set @v_select='';
		COMMIT;    
		IF v_sourcedate IS NULL or v_sourcedate = '' THEN   
			SET @v_select = CONCAT('SELECT MIN(sourcedate) INTO ',v_sourcedate,' FROM ' , v_sourcetable);
			PREPARE stmt FROM @v_select;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @v_select = '';
			COMMIT;				
		END IF;


		SET @v_select = CONCAT('SELECT MAX(timeofday) +  ',v_intervalseconds,' INTO ',v_timeofday,' FROM ', pi_table, ' WHERE sourcedate = ',v_sourcedate);
		PREPARE stmt FROM @v_select;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
    set @v_select = '';
		COMMIT;	
		IF v_timeofday IS NULL or v_timeofday = '' THEN
			SET v_timeofday = v_intervalseconds;
		END IF;

		
		IF v_timeofday >= 86400 THEN
			SET v_sourcedate = v_sourcedate + 1;
			SET v_timeofday  = 0;
		END IF;

		
		SET v_datetime = v_sourcedate + (v_timeofday / 86400);

		
		SET @v_select = CONCAT('SELECT MAX(sourcedate) INTO ',v_dateinsource,' FROM ', v_sourcetable);
		PREPARE stmt FROM @v_select;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
    set @v_select = '';
		COMMIT;	
		IF v_dateinsource IS NULL or v_dateinsource = '' THEN
			LEAVE do_the_work; 
		END IF;

		
		SET @v_select = CONCAT('SELECT MAX(timeofday) INTO ',v_timeinsource,' FROM ', v_sourcetable, ' WHERE sourcedate = ',v_dateinsource);
		PREPARE stmt FROM @v_select;
		EXECUTE stmt;
		DEALLOCATE PREPARE stmt;
    set @v_select = '';
		COMMIT;
		
		IF v_timeinsource IS NULL or v_timeinsource = '' THEN 
			SET v_timeinsource = v_jobtimeofday;
		END IF;

		
		SET v_sourcedatetime = v_dateinsource + (v_timeinsource/86400);

		
		SET v_diff = FLOOR((v_sourcedatetime - v_datetime) * 86400 / v_intervalseconds);  
		IF v_diff > 0  THEN
			WHILE v_diff > 0 DO


 #cancel the row share lock strategy of Oracle
                 SET v_where = concat(' WHERE sourcedate = ',v_sourcedate,' AND startsecond = ',v_timeofday);
                 SET @v_inswhere = CONCAT(v_insert,v_where);
                 PREPARE stmt from @v_inswhere;
                 execute stmt;
                 deallocate prepare stmt;
                 set @v_inswhere='';
                 COMMIT;

			   SET v_diff = v_diff - 1;

		
			   SET v_timeofday = v_timeofday + v_intervalseconds;

		
				IF v_timeofday >= 86400 THEN
					SET v_sourcedate = v_sourcedate + 1;
					SET v_timeofday  = 0;
				END IF;
			END WHILE;
		ELSE
	  
	
	
			COMMIT;
		END IF;
	END;
  
	COMMIT;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_pwr_api_get_interval_diff`$$
CREATE PROCEDURE  `prc_dr_pwr_api_get_interval_diff`(
    IN  pi_sourcedate1          DATETIME,
    IN  pi_sourcedate2          DATETIME,
    OUT  v_old                  INT(11),
    OUT  v_new                  INT(11),
    OUT  v_counter              INT(11)
   )
BEGIN
# Will Aug 2011
		SET v_new = func_dr_pwr_api_get_interval (pi_sourcedate2);
		SET v_old = func_dr_pwr_api_get_interval (pi_sourcedate1);
		SET v_counter = v_new + 48 * (DATEDIFF(pi_sourcedate2, pi_sourcedate1)) - v_old;
		#SET v_counter = FLOOR(v_counter);
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_pwr_api_get_tariff_setpoint`$$
CREATE PROCEDURE  `prc_dr_pwr_api_get_tariff_setpoint`(
   IN  pi_entitykey   INT(11),
   OUT v_tariff       INT(2),
   OUT v_setpoint     DECIMAL(22, 0))
BEGIN
# Will Aug 2011
      DECLARE v_pkey        INT(11);
      DECLARE v_entitykey   INT(11);
      DECLARE v_loc         VARCHAR(20);
      DECLARE v_value       VARCHAR(20);
      DECLARE v_label       VARCHAR(20);

      DECLARE done int default 0;
      DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

      SELECT locationname
        INTO v_loc
        FROM entity_v
       WHERE pkey = pi_entitykey;

      SELECT tariff
        INTO v_value
        FROM dr_pwrdmd_config
       WHERE LOCATION = v_loc;

      SELECT setpoint
        INTO v_setpoint
        FROM dr_pwrdmd_config
       WHERE LOCATION = v_loc;

      SELECT pkey
        INTO v_entitykey
        FROM entity
       WHERE NAME =
                CONCAT(v_loc, '.SYS.PWR.DMD.diiSYS-PwrDmdTariffOffOnPeak');

      SELECT epv.VALUE
        INTO v_label
        FROM entityparametervalue epv, entityparameter ep
       WHERE     ep.NAME = 'TrueLabel'
             AND ep.pkey = epv.parameterkey
             AND epv.entitykey = v_entitykey;

      IF done = 0 then
         IF (v_value = v_label)
         THEN
            SET v_tariff = 1;
            #Tariff: ON Peak.
         ELSE
            SET v_tariff = 0;
            #Tariff: OFF Peak.
         END IF;
      #else 'no setpoint/tariff found in the db.'
      END IF;
      
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_pwr_api_ins_new_30min_rec`$$
CREATE PROCEDURE  `prc_dr_pwr_api_ins_new_30min_rec`(
    IN  pi_entitykey         INT(11),
    IN  pi_sourcedate        DATETIME,
        pi_int               INT(11),
        pi_tariff            INT(11),
        pi_setpoint          INT(11),
        pi_setpointname      VARCHAR(85),
    IN  pi_demand            decimal(38,30)
   )
BEGIN
# Will Sept 2011
    DECLARE  v_entityname   VARCHAR(90);
    DECLARE  v_week         DATE;
    DECLARE  v_weeknum      INT(11);

    # add default value.
    if pi_demand is null or pi_demand = '' then
      set pi_demand = 0;
    end if;

    #begin ins_new_30min_rec
    SELECT NAME INTO v_entityname FROM entity WHERE pkey = pi_entitykey;

    SET v_week = DATE(pi_sourcedate);
    SET v_weeknum = FLOOR(TIMESTAMPDIFF(DAY, STR_TO_DATE('02/01/2000 00:00:00', '%d/%m/%Y %H:%i:%S' ), pi_sourcedate) / 7 );

 INSERT INTO dr_pwrdmd_30min_table(ENTITYKEY,entityname,SOURCEDATE,`INT`,TARIFF,DEMAND,SETPOINT,SETPOINT_NAME,EDITED_DEMAND,week,
    weeknum,MODIFIED_BY,DATE_MODIFIED)
 VALUES(pi_entitykey,v_entityname,pi_sourcedate,pi_int,pi_tariff,pi_demand,pi_setpoint,pi_setpointname,0,v_week,v_weeknum,
     substring_index(current_user,'@',1),SYSDATE() );
    #End ins_new_30min_rec
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_pwr_api_upd_30min_pwr_point`$$
CREATE PROCEDURE  `prc_dr_pwr_api_upd_30min_pwr_point`(
    IN  pi_entitykey         INT(11),
      pi_sourcedate        DATETIME,
      pi_int               INT(11),
      pi_demand            decimal(38,30)
   )
BEGIN
# Will Aug 2011
    DECLARE  v_cons               INT(11);
    DECLARE  v_new_cons           INT(11);
    DECLARE  v_count              INT(11);
#dr_pwrdmd_30min_table declarations	
    DECLARE  v_demand_30min       decimal(38,30);
    DECLARE  v_upd_demand_30min   decimal(38,30)      DEFAULT 0;
    DECLARE  v_int                INT(11)      DEFAULT 0;
    DECLARE  v_tariff             VARCHAR (20);
    DECLARE  v_setpoint           INT(11);
    DECLARE  v_setpointname       VARCHAR(20);
    DECLARE  v_raise_alarm        VARCHAR(2000);
    DECLARE  v_demand             decimal(38,30);
    DECLARE  v_entityname         VARCHAR(90);

	SELECT demand INTO v_demand_30min FROM dr_pwrdmd_30min_table WHERE entitykey = pi_entitykey and
		DATE(sourcedate) = DATE(pi_sourcedate) and `int` = pi_int ;
    SELECT setpoint INTO v_setpoint FROM dr_pwrdmd_30min_table WHERE entitykey = pi_entitykey and 
		DATE(sourcedate) = DATE(pi_sourcedate) and `int` = pi_int ; 

    SET  v_upd_demand_30min = v_demand_30min + pi_demand;
#        IF((v_setpoint < v_upd_demand_30min) and (v_setpoint <> 0)) THEN
#       dbms_output.put_line('30min demand > setpoint, now raising alarm');
#       execute immediate 'select name from entity where pkey = :b1 ' into v_entityname using pi_entitykey;
#       v_raise_alarm := raise_alarm(v_entityname,NULL,NULL,NULL,'30 minutes accumulated power demand more than setpoint');
#        END IF;
	UPDATE dr_pwrdmd_30min_table SET demand = v_upd_demand_30min WHERE entitykey = pi_entitykey and
		DATE(sourcedate) = DATE (pi_sourcedate) and `int` = pi_int ;
#Updating of dr_pwrdmd_30min_table is complete;
#End of procedure upd_pwr_point;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_dr_pwr_api_upd_pwr_point`$$
CREATE PROCEDURE  `prc_dr_pwr_api_upd_pwr_point`(
    IN   pi_entitykey           INT(11),
    IN   pi_sourcedate          DATETIME,
    IN   pi_cons                decimal(38,30),
    OUT  po_demand              decimal(38,30)
   )
BEGIN
# Will Sept 2011
/*
Procedure upd_pwr_point updates the dr_pwrdmd_data and dr_pwrdmd_30min_table
This procedure finds what is the existing demand for specific power point(entity) in the table dr_pwrdmd_data, there is no need to insert a record
as record gets populated in dr_pwrdmd_data when ever a new entity gets added of power point type.

Once existing demand is acquired then computes the running total of the demand, then updates thes dr_pwrdmd_data table with new demand. Once this process is done
procedure proceeds to updating of dr_pwrdmd_30min_table which contains total consumption for given period of time(30)mins.

Classification of entries has been made accofding to the below scenario.

identifies which half an hour of the day this record belongs to, Unique identifier for the day is TRUNC(SYSDATE) and each day had 48 sub divisions, it may be better to take sysdate into considaration as it resides inside the
table and not requires to read any other table.

Time received by this procedure contains Hours consider hours and mins then calculate it accordingly
How (If thats's 2hrs and it is after that 30min interval') then (2*2) else (2*2-1)
How (If thats's 4hrs and it is before 30min interval') then (4*2) else (4*2-1)

v_hrs  :=  TO_CHAR(:NEW.sourcetime,'HH24') ; --To find out 24hrs time
v_date := select TRUNC(SYSDATE) from dual; -- To identify the sysdate
v_mins := TO_CHAR(:NEW.sourcetime,'MI') ; --To identify the Minute it happend

Insert into dr_pwrdmd_30min_table(SYSDATE,ID(1-48),.....fields);
When you call UPDATE, use update where id=.... and date=sysdate.

*/
#dr_pwrdmd_data
    DECLARE  v_cons   decimal(38,30);
	
	SELECT consumption INTO v_cons FROM dr_pwrdmd_data WHERE entitykey = pi_entitykey ;    

      #pi_value => New consumption value and v_demand is the Existing consumption value in the table dr_pwrdmd_data
      #If new consumption value < the consumption value dr_pwrdmd_data then
      #New consumption value = New consumption value (DR_DATAPOINT_STATE)+ (Rollover constant - Existing Consumption Value(dr_pwrdmd_data)) +1              
    SET  po_demand = func_dr_pwr_api_get_demand (pi_entitykey, v_cons, pi_cons);
     #Update dr_pwrdmd_data table with the new New consumption value, it is required to update dr_pwrdmd_data table with the original value
     #as the demand(dr_pwrdmd_30min_table) is the only parameter which should get reflect the roll over value.
     #The demand will only gets added to the table dr_pwrdmd_30min_table.           
	UPDATE dr_pwrdmd_data SET sourcedate = pi_sourcedate, consumption = pi_cons WHERE entitykey = pi_entitykey ;    
     #Update of dr_pwrdmd_data is complete
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_drop_object`$$
CREATE PROCEDURE  `prc_drop_object`(
   IN p_object_type   VARCHAR(50),
   IN p_object_name   VARCHAR(256)
)
BEGIN
   DECLARE l_command   VARCHAR (1000) DEFAULT NULL;

	IF UPPER (p_object_type) = 'TABLE'     THEN
		SET @l_command = CONCAT('DROP TABLE ' , p_object_name , ' cascade constraints');
	ELSEIF UPPER (p_object_type) = 'VIEW'  THEN
		SET @l_command = CONCAT('DROP VIEW ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'TRIGGER'  THEN
		SET @l_command = CONCAT('DROP TRIGGER ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'SEQUENCE'   THEN
		SET @l_command = CONCAT('DROP SEQUENCE ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'MV'  THEN
		SET @l_command = CONCAT('DROP MATERIALIZED VIEW ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'MVL'  THEN
		SET @l_command = CONCAT('DROP MATERIALIZED VIEW LOG ON ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'LINK'  THEN
		SET @l_command = CONCAT('DROP DATABASE LINK ' , p_object_name);
	ELSEIF UPPER (p_object_type) = 'TYPE' THEN
		SET @l_command = CONCAT('DROP TYPE ' , p_object_name);
	ELSE
		SET @l_command = NULL;
	END IF;
	
	PREPARE stmt FROM @l_command;
	execute stmt;
	DEALLOCATE PREPARE stmt;
  set @l_command='';
	commit;
   
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_ev_api_get_dpstatechange_max_data`$$
CREATE PROCEDURE  `prc_ev_api_get_dpstatechange_max_data`(
	OUT p_pkey         INT(11),
	OUT p_date         VARCHAR(15),   
	OUT p_next_number  INT(11)
)
BEGIN
# Will Aug 2011
	DECLARE v_max         INT(11);
	DECLARE v_next_number INT(11);
	DECLARE v_maxdate     VARCHAR(15);
  #DECLARE v_max_ukey    INT(11) DEFAULT 0;
  DECLARE done int default 0;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

	#SELECT MAX(ukey) INTO v_max_ukey FROM lo_datapt_state_change;
	SELECT ukey,DATE_FORMAT(logtime, '%Y%m%d%H%i%S'),func_seq_get_next_number('LODSCH_SEQ')
	INTO v_max, v_maxdate, v_next_number
	FROM lo_datapt_state_change WHERE ukey =
  (SELECT MAX(ukey) FROM lo_datapt_state_change);

  if done = 0 then
  	SET p_pkey = v_max;
  	SET p_date = v_maxdate;
  	SET p_next_number = v_next_number;
  else 
    set p_pkey = 0;
    set p_date = '20000101';
    #select 'no_data_found';
  End if;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_ev_api_get_dpstatechange_min_data`$$
CREATE PROCEDURE  `prc_ev_api_get_dpstatechange_min_data`(
	OUT p_pkey  INT(11),
	OUT p_date  VARCHAR(15)  
)
BEGIN
# Will Aug 2011
	DECLARE v_min       INT(11) DEFAULT 0;
	DECLARE v_mindate   VARCHAR(15) DEFAULT NULL;
	#DECLARE v_min_pkey  INT(11) DEFAULT 0;
  DECLARE done int default 0;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
  
	#SELECT MIN(ukey) INTO v_min_pkey FROM lo_datapt_state_change;
	SELECT ukey, DATE_FORMAT(logtime, '%Y%m%d%H%i%S')
	INTO v_min, v_mindate
	FROM lo_datapt_state_change WHERE ukey =
  (SELECT MIN(ukey) FROM lo_datapt_state_change);

  if done = 0 then
  	SET p_pkey = v_min;
	  SET p_date = v_mindate;
  else
    SET p_pkey = 0;
    SET p_date = '20000101';
  end if;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_ev_api_get_event_max_data`$$
CREATE PROCEDURE  `prc_ev_api_get_event_max_data`(OUT p_pkey INT(11),OUT p_date varchar(15),OUT p_next_number int(11))
BEGIN
# Will Aug 2011
  declare v_max int(11);
  declare v_maxdate varchar(15);
  declare v_next_number int(11);

 SELECT pkey,date_format(logtime,'%Y%m%d%H%i%S'),func_seq_get_next_number('event_seq')
 INTO v_max, v_maxdate, v_next_number
 FROM event WHERE pkey =
 (SELECT MAX(pkey) FROM event);

  if v_max <> '' then
   set p_pkey = v_max;
   set p_date = v_maxdate;
   set p_next_number = v_next_number;
  else
   set p_pkey = 0;
   set p_date = '20000101';
   #select 'no_data_found';
  end if;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_ev_api_get_event_min_data`$$
CREATE PROCEDURE  `prc_ev_api_get_event_min_data`(OUT p_pkey INT(11),OUT p_date VARCHAR(15))
BEGIN
# Will Aug 2011
declare v_min int(11);
declare v_mindate varchar(15);

 SELECT pkey,date_format(logtime,'%Y%m%d%H%i%S')
 INTO v_min, v_mindate
 FROM event WHERE pkey =
 (SELECT MIN(pkey) FROM event);

 if v_min <> '' then
    set p_pkey = v_min;
    set p_date = v_mindate;
 else
    set p_pkey = 0;
    set p_date = '20000101';
    #select 'no_data_found';
 end if;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_ev_api_populate_ev_combined`$$
CREATE PROCEDURE  `prc_ev_api_populate_ev_combined`(
   IN p_source_table             VARCHAR(50),
   IN p_pkey                     INT(11),
   IN p_createdatetime           DATETIME,
   #IN     p_createtime              TIMESTAMP,
   IN p_createtime               VARCHAR(23),
   IN p_subsystem_key            INT(11),
   IN p_physical_subsystem_key   INT(11),
   IN p_location_key             INT(11),
   IN p_severity_key             INT(11),
   IN p_severity_name            VARCHAR(50),
   IN p_asset_name               VARCHAR(256),
   IN p_description              VARCHAR(1024),
   IN p_event_type_key           INT(9),
   IN p_event_type_name          VARCHAR(256),
   IN p_alarm_id                 VARCHAR(40),
   IN p_alarm_type_key           INT(9),
   IN p_value                    VARCHAR(2000),
   IN p_mms_state                VARCHAR(100),
   IN p_dss_state                VARCHAR(30),
   IN p_avl_state                VARCHAR(100),
   IN p_operator_key             INT(9),
   IN p_operator_name            VARCHAR(85),
   IN p_alarm_comment            VARCHAR(1024),
   IN p_event_level              INT(1),
   IN p_alarm_ack                VARCHAR(38),
   IN p_alarm_status             VARCHAR(2),
   IN p_session_key              VARCHAR(38),
   IN p_session_location         INT(9),
   IN p_profile_id               INT(9),
   IN p_action_id                INT(9),
   IN p_operation_mode           VARCHAR(2))
BEGIN
# Modified by Will Sept 2011
      INSERT INTO ev_combined(SOURCE_TABLE,
                              PKEY,
                              CREATEDATETIME,
                              CREATETIME,
                              SUBSYSTEM_KEY,
                              PHYSICAL_SUBSYSTEM_KEY,
                              LOCATION_KEY,
                              SEVERITY_KEY,
                              SEVERITY_NAME,
                              ASSET_NAME,
                              DESCRIPTION,
                              EVENT_TYPE_KEY,
                              EVENT_TYPE_NAME,
                              ALARM_ID,
                              ALARM_TYPE_KEY,
                              VALUE,
                              MMS_STATE,
                              DSS_STATE,
                              AVL_STATE,
                              OPERATOR_KEY,
                              OPERATOR_NAME,
                              ALARM_COMMENT,
                              EVENT_LEVEL,
                              ALARM_ACK,
                              ALARM_STATUS,
                              SESSION_KEY,
                              session_LOCATION,
                              profile_id,
                              action_id,
                              operation_mode)
      VALUES (p_source_table,
              p_pkey,
              p_createdatetime,
              p_createtime,
              p_subsystem_key,
              p_physical_subsystem_key,
              p_location_key,
              p_severity_key,
              p_severity_name,
              p_asset_name,
              p_description,
              p_event_type_key,
              p_event_type_name,
              p_alarm_id,
              p_alarm_type_key,
              p_value,
              p_mms_state,
              p_dss_state,
              p_avl_state,
              p_operator_key,
              p_operator_name,
              p_alarm_comment,
              p_event_level,
              p_alarm_ack,
              p_alarm_status,
              p_session_key,
              p_session_location,
              p_profile_id,
              p_action_id,
              p_operation_mode);

     -- COMMIT;
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_insert_global_parameter`$$
CREATE PROCEDURE  `prc_insert_global_parameter`(
   IN v_subsystem_name   VARCHAR(85),
   IN v_name             VARCHAR(85),
   IN v_value            VARCHAR(512))
BEGIN
      # Modified by Will Sept 2011
      DECLARE l_id              INT(9) DEFAULT 0;
      DECLARE l_subsystem_key   INT(9) DEFAULT 0;

      SELECT func_seq_get_next_number('gparam_seq')
        INTO l_id;

      SELECT pkey
        INTO l_subsystem_key
        FROM subsystem
       WHERE NAME = v_subsystem_name;


      INSERT INTO global_parameter(gparam_id,
                                   subsystemkey,
                                   name,
                                   value)
      VALUES (l_id,
              l_subsystem_key,
              v_name,
              v_value);

      COMMIT;
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_insert_plan`$$
CREATE PROCEDURE  `prc_insert_plan`(
   IN v_node_type        INT(6),
   IN v_parent_node      INT(6),
   IN v_name             VARCHAR(150),
   IN v_description      VARCHAR(2000),
   IN v_approval_state   INT(6),
   IN v_operatorName     VARCHAR(256),
   IN v_end_step         INT(6))
BEGIN
      # Modified by Will Sept 2011
      DECLARE l_node_id          INT(11) DEFAULT 0;
      DECLARE l_node_type        INT(9) DEFAULT 0;
      DECLARE l_approval_state   INT(6) DEFAULT 0;

      # add default value
      if v_end_step is null or v_end_step = '' then
        set v_end_step = 1;
      end if;

      SELECT func_seq_get_next_number('plans_seq')
        INTO l_node_id;

      SELECT p_key
        INTO l_node_type
        FROM node_type
       WHERE type_value = v_node_type;

      SELECT p_key
        INTO l_approval_state
        FROM approval_state
       WHERE state_value = v_approval_state;

      #insert Plan into node_tree table
      INSERT INTO node_tree(p_key,
                            fk_node_type,
                            parent_node,
                            name,
                            description,
                            fk_approval_state,
                            node_created_by,
                            node_modified_by,
                            modified_by,
                            date_modified,
                            approval_modified_by,
                            approval_date_modified)
      VALUES (l_node_id,
              l_node_type,
              v_parent_node,
              v_name,
              v_description,
              l_approval_state,
              v_operatorName,
              v_operatorName,
              substring_index(current_user, '@', 1),
              SYSDATE(),
              v_operatorName,
              SYSDATE());


      IF v_end_step = 1
      THEN
         INSERT INTO step_details(p_key,
                                  fk_step_type,
                                  fk_node_tree,
                                  position,
                                  description,
                                  skip,
                                  skippable,
                                  DELAY,
                                  name)
         VALUES (func_seq_get_next_number('plans_seq'),
                 1,
                 l_node_id,
                 1,
                 'End Step',
                 0,
                 0,
                 0,
                 'End');
      END IF;

      COMMIT;
   #Values deleted.....exiting return 1
   #exception.....exiting return -1
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_new_action_group`$$
CREATE PROCEDURE  `prc_new_action_group`(
	IN p_actionname       VARCHAR(80),
	IN p_actiongroupname  VARCHAR(256)
)
BEGIN
# Reviewed
	DECLARE v_actionkey      INT(9);
	DECLARE v_actiongroupkey INT(9);

	SELECT a.seacti_id,dt.seagro_id INTO v_actionkey,v_actiongroupkey
	FROM se_action a, se_action_group dt
	WHERE a.name = p_actionname AND dt.name = p_actiongroupname;
	INSERT INTO se_action_group_map (seacti_id,seagro_id) VALUES (v_actionkey,v_actiongroupkey);	


END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_new_operator_profile`$$
CREATE PROCEDURE  `prc_new_operator_profile`(
   IN p_operatorname   VARCHAR(85),
   IN p_profilename    VARCHAR(85))
BEGIN
# Modified Setp 2011
      DECLARE v_operatorkey   INT(9);
      DECLARE v_profilekey    INT(9);

      SELECT o.pkey, p.seprof_id
        INTO v_operatorkey, v_profilekey
        FROM OPERATOR o, se_profile p
       WHERE o.name = p_operatorname AND p.name = p_profilename;

      INSERT INTO SE_OPERATOR_PROFILE(seopro_id, operatorkey, seprof_id)
      VALUES (func_seq_get_next_number('SECURITY_SEQ'), v_operatorkey, v_profilekey);

      COMMIT;
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_new_profile_access`$$
CREATE PROCEDURE  `prc_new_profile_access`(
   IN p_profilename       VARCHAR(85),
   IN p_subsystemname     VARCHAR(80),
   IN p_subsystemstate    VARCHAR(80),
   IN p_actiongroupname   VARCHAR(256))
BEGIN
# Modified Setp 2011
      DECLARE v_profilekey          INT(9);
      DECLARE v_subsystemkey        INT(9);
      DECLARE v_subsystemstatekey   INT(9);
      DECLARE v_actiongroupkey      INT(9);

      SELECT p.seprof_id,
             s.pkey,
             ss.sessta_id,
             dt.seagro_id
        INTO v_profilekey,
             v_subsystemkey,
             v_subsystemstatekey,
             v_actiongroupkey
        FROM se_profile p,
             subsystem s,
             se_subsystem_state ss,
             se_action_group dt
       WHERE     p.name = p_profilename
             AND s.name = p_subsystemname
             AND ss.name = p_subsystemstate
             AND dt.name = p_actiongroupname;

      INSERT INTO se_profile_access(seprof_id,
                                    subsystemkey,
                                    sessta_id,
                                    seagro_id)
      VALUES (v_profilekey,
              v_subsystemkey,
              v_subsystemstatekey,
              v_actiongroupkey);
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_omflag_param_list`$$
CREATE PROCEDURE  `prc_omflag_param_list`(
	IN  param_list   VARCHAR(2000),
  OUT p_return     VARCHAR(2000)
	)
BEGIN
# Modified by Will Sept 2011
    DECLARE v_key        INT(9) DEFAULT 0;
    DECLARE v_start      INT(9) DEFAULT 0;
    DECLARE v_end        INT(9) DEFAULT 0;
    DECLARE v_subStr     VARCHAR(2000) DEFAULT NULL;

    IF(param_list <> '') THEN
        SET v_key = instr(binary param_list, 'OMFlag:');

# get needed substring        
        if (v_key > 0) then
            SET v_subStr = SUBSTR(param_list, v_key);
            SET v_start  = instr(binary v_subStr,':');
            SET v_end    = instr(binary v_subStr,',');

#if end comma is not found then fetch all the remaining text as value            
            IF v_end < v_start THEN
                SET p_return = SUBSTR(v_subStr, v_start+1);
            ELSE
                SET p_return = SUBSTR(v_subStr, v_start+1, (v_end-1)-v_start);
            END IF;
            IF length(p_return)>1 then
                SET p_return := SUBSTR(p_return,0,1);
            END IF;
        else
            SET p_return = '';
        end if;
    END IF;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_populate_managed_procs`$$
CREATE PROCEDURE  `prc_populate_managed_procs`()
BEGIN
# Modified by Will Sept 2011
# TO-DO: This procedure need to update the l_count(previous<=32 stations) for C955
  DECLARE l_typekey                INT(9);
	DECLARE l_max_order              INT(9);
	DECLARE l_min_order              INT(9);
	DECLARE l_next_order             INT(9); 
	DECLARE l_count                  INT(9);
	DECLARE l_system_controller_id   INT(9);
	DECLARE l_location_id            INT(9);
  
  Declare l_entity_pkey            INT(9);
  
	DECLARE no_more_rows             BOOLEAN default false;
  
	DECLARE  c_get_managed_process CURSOR FOR  
    SELECT pkey FROM entity
    WHERE typekey = l_typekey AND locationkey = l_location_id;
   # WHERE typekey = c_typekey AND locationkey = c_location_id
   #  AND name NOT LIKE '%AtsMonitoredProcess';

	DECLARE  c_get_system_controller_id CURSOR FOR 
    SELECT ssc.snscon_id FROM sn_system_controller ssc, entity en
    WHERE en.locationkey = l_location_id AND ssc.SERVER_ENTITY_PKEY = en.pkey;
	
	DECLARE c_get_location_id_count CURSOR FOR
	SELECT pkey FROM location WHERE order_id = l_count;
	
	DECLARE  c_get_location_id_order CURSOR FOR
    SELECT pkey FROM location WHERE order_id = l_next_order;  
    
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;

	SELECT pkey INTO l_typekey FROM entitytype WHERE NAME = 'MonitoredProcess';
	SELECT pkey INTO l_location_id FROM location WHERE NAME = 'OCC';	
	# Process OCC location first
  
	OPEN c_get_managed_process;
  
	the_managed_process_loop1: LOOP  
		FETCH c_get_managed_process INTO l_entity_pkey;
		IF no_more_rows THEN
			LEAVE the_managed_process_loop1;
		END IF;
    
		BEGIN
			INSERT INTO sn_managed_process (snscon_id, managed_process_pkey, default_operating_mode)
            VALUES (0, l_entity_pkey, 0);
			INSERT INTO sn_managed_process (snscon_id, managed_process_pkey, default_operating_mode)
            VALUES (1, l_entity_pkey, 1);
			COMMIT;     
    END;
		
	END LOOP the_managed_process_loop1;
  CLOSE c_get_managed_process;
	
	SELECT pkey INTO l_typekey FROM entitytype WHERE NAME = 'MonitoredProcess';
	SELECT pkey INTO l_location_id FROM location WHERE NAME = 'KCD';
	#Now Process KCD
	SET no_more_rows = FALSE;
	OPEN c_get_managed_process;
	the_managed_process_loop2: LOOP
		FETCH c_get_managed_process INTO l_entity_pkey;
		IF no_more_rows THEN
			LEAVE the_managed_process_loop2;
		END IF;
		BEGIN
			INSERT INTO sn_managed_process (snscon_id, managed_process_pkey, default_operating_mode)
			VALUES (2, l_entity_pkey, 0 );
			INSERT INTO sn_managed_process (snscon_id, managed_process_pkey, default_operating_mode)
			VALUES (3, l_entity_pkey, 1 );
			COMMIT;      
		END;		
	
	END LOOP the_managed_process_loop2;  
	CLOSE c_get_managed_process;
   # Can't use order_id anymore as values are now present for all
   # locations.

   # Get min order ID for location (DBG)
   # SELECT MIN (order_id)
   # INTO l_min_order
   # FROM LOCATION;		
	SET l_min_order = 3;
   # Get max order ID for location (HBF)
   # SELECT MAX (order_id)
   #  INTO l_max_order
   #  FROM LOCATION;	
	SET l_max_order = 32;
   # Process all locations with an order_id column value
	
	SET l_count = l_max_order;
	#WHILE v_counter >= l_min_order DO
	proc_all_loc_loop : loop	
    # Skip the WCT station and KCD.
    # wangfei: dont skip WCT!
    # IF (l_count != 28) AND (l_count != 14)		
		IF (l_count <> 14) THEN
			# Get location for this order_ID
			OPEN c_get_location_id_count;
			FETCH c_get_location_id_count INTO l_location_id;
			CLOSE c_get_location_id_count;
			# Get system controller id for this location
			OPEN c_get_system_controller_id ;
			FETCH c_get_system_controller_id INTO l_system_controller_id;
			CLOSE c_get_system_controller_id;
			
      # Get all managed processes for this location
      # Insert those processes in CONTROL mode.			
			SET no_more_rows = FALSE;
			OPEN c_get_managed_process;
			the_managed_process_loop3: LOOP
				FETCH c_get_managed_process INTO l_entity_pkey;						
				IF no_more_rows THEN
					LEAVE the_managed_process_loop3;
				END IF;				
				BEGIN
					INSERT INTO sn_managed_process (snscon_id, managed_process_pkey,default_operating_mode)
					VALUES (l_system_controller_id, l_entity_pkey,0);
					COMMIT;        
				END;
				
			END LOOP the_managed_process_loop3;		
      CLOSE c_get_managed_process;
			
      # Get the next location id in the loop (previous location in the line)
      # If the current location is the beginning of the line, then the next location is
      # the LAST location of the line.
      # In the particular case of PPJ station (29), skip the previous WCT station and set the
      # previous station as being KRG (27).
      # In the particular case of BLY station (15), skip the previous KCD location and set the
      # previous station as being TSG (13).				
			IF l_count <= l_min_order THEN
				SET l_next_order = l_max_order;
      # wangfei: treate WCT as a normal station.
      # ELSIF (l_count = 29) OR (l_count = 15)								
			ELSEIF  (l_count = 15)  THEN
				SET l_next_order = l_count - 2;
			ELSE
				SET l_next_order = l_count - 1;
			END IF;

      # Get location for this order_ID			
			OPEN c_get_location_id_order ;
			FETCH c_get_location_id_order INTO l_location_id;
			CLOSE c_get_location_id_order;
			
      # Get all managed processes for this location
      # Insert those processes in MONITOR mode.			
			SET no_more_rows = FALSE;
			OPEN c_get_managed_process;
			the_managed_process_loop4: LOOP
				FETCH c_get_managed_process INTO l_entity_pkey;
				IF no_more_rows THEN
					LEAVE the_managed_process_loop4;
				END IF;
				BEGIN
					INSERT INTO  sn_managed_process (snscon_id, managed_process_pkey,default_operating_mode)
					VALUES (l_system_controller_id, l_entity_pkey,1 );
					COMMIT;         
				END;				
			END LOOP the_managed_process_loop4;		
      CLOSE c_get_managed_process;
		END IF;
    
		SET l_count = l_count - 1;
    IF l_count >= l_min_order THEN ITERATE proc_all_loc_loop; END IF;
    LEAVE proc_all_loc_loop;
    
	END loop;		

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_replace_plan`$$
CREATE PROCEDURE  `prc_replace_plan`(
	IN v_existing_plan_pkey     INT(6), 
	IN v_overwriting_plan_pkey  INT(6),
	IN v_operator_name          VARCHAR(85), 
	IN v_copy_overwriting_plan  INT(6)
)
BEGIN
# Modified Sept 2011
	DECLARE l_target_category_pkey  INT(6);
	DECLARE l_plan_name             VARCHAR(200);
  
  # Determine where the plan being replaced lives.    
    SELECT name,        parent_node
    INTO   l_plan_name, l_target_category_pkey
    FROM   node_tree
    WHERE  p_key = v_existing_plan_pkey;

  # Remove the existing plan.    
    DELETE FROM step_parameters
    WHERE  fk_step_details IN (SELECT p_key
                               FROM   step_details
                               WHERE  fk_node_tree = v_existing_plan_pkey);

    DELETE FROM step_details WHERE  fk_node_tree = v_existing_plan_pkey;

    DELETE FROM node_tree WHERE  p_key = v_existing_plan_pkey;

  # Copy or move the overwriting plan as required.    
    IF (v_copy_overwriting_plan = 0) THEN
  # When moving the plan only the parent node is updated, the rest of the plan data remains intact.      
        UPDATE node_tree
        SET    parent_node = l_target_category_pkey
        WHERE  p_key = v_overwriting_plan_pkey;
    ELSE
        CALL prc_copy_plan(v_overwriting_plan_pkey, l_target_category_pkey, l_plan_name, v_operator_name);
    END IF;

    COMMIT;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_sent_map_param`$$
CREATE PROCEDURE  `prc_sent_map_param`(
	IN p_etype  VARCHAR(80)
)
BEGIN
/*   SENT_MAP_PARAM procedure dynamically assigns custom field names to entity parameters
* (to be used for site entities in de-normalised structure, i.e. SI_ENTITY table)
*  Intended usage:
*  execute sent_map_param('DataPoint');
*/
	
	DECLARE  v_name         VARCHAR(80);
  
  DECLARE  v_row_num      INT(9) default 1;
  DECLARE  no_more_rows   BOOLEAN DEFAULT FALSE;
	
	DECLARE  cu_temp CURSOR FOR 
	select name from entityparameter where typekey in
	(select pkey from entitytype where name = p_etype);

	DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;
	
	OPEN cu_temp;
	the_loop: LOOP
		FETCH cu_temp INTO v_name;
		IF no_more_rows THEN
			LEAVE the_loop;
		END IF;
		UPDATE entityparameter SET ec_field = CONCAT('ec_short', v_row_num) WHERE name = v_name and typekey in
            (SELECT pkey FROM entitytype WHERE name = p_etype);
		SET v_row_num = v_row_num + 1;
	END LOOP the_loop;	
  CLOSE cu_temp;

END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_set_plan_edit_lock`$$
CREATE PROCEDURE  `prc_set_plan_edit_lock`(
	v_node_id   INT(6), 
	v_owner     VARCHAR(85), 
	v_time_out  bigint(20)
)
BEGIN
# Modified Sept 2011
	DECLARE l_return     INT(2);
	DECLARE l_time_stamp DATETIME;
	DECLARE l_owner      VARCHAR(100);

  SET l_return = 0;
  
	SELECT node_tree.edit_lock_owner, node_tree.EDIT_TIME_STAMP
   		INTO l_owner, l_time_stamp
   	FROM node_tree WHERE p_key = v_node_id;

	IF ( (l_owner IS NULL or l_owner = '') OR (l_time_stamp IS NULL or l_time_stamp = '') OR ( l_owner = v_owner ) ) THEN
       SET l_return = 1;
	ELSE
		SELECT node_tree.edit_time_stamp INTO l_time_stamp
   		FROM node_tree 
    WHERE p_key = v_node_id;

   		IF ( SYSDATE > (l_time_stamp + v_time_out) ) THEN
   	  	  	SET l_return = 1;
		END IF;
	END IF;

	IF ( l_return = 1 ) THEN
		UPDATE node_tree SET edit_lock_owner = v_owner, edit_time_stamp = SYSDATE()
		WHERE p_key = v_node_id;
	END IF;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_test`$$
CREATE PROCEDURE  `prc_test`(v_sourcetable varchar(30))
begin
/*
DECLARE no_more_rows             BOOLEAN default false;
declare v_select  varchar(2000);
 
 declare v_demandpersecond   decimal(38,30);
 declare lv_name varchar(30) default '30023';
 */
 	declare lv_timest varchar(30);
  declare lv_cur cursor for select timestamp from test02 where name='bghjbj';

  #update test02 set timestamp = now();  
 #set lv_name = 'f';
 begin
 
	 DECLARE continue HANDLER FOR not found begin end;	

 open lv_cur;
 fetch lv_cur into lv_timest;
 close lv_cur;
 end;
   #select timestamp into lv_timest from test02 where name='bghjbj';
 #set @lv_name='f';
 #set v_select = concat('SELECT name into @lv_timest FROM ',v_sourcetable,' limit 1');
 /*set @v_select = concat('SELECT name into @lv_timest FROM test02 where name=?');
 	PREPARE stmt FROM @v_select;
		EXECUTE stmt using @lv_name;
		DEALLOCATE PREPARE stmt;*/
     /* select (
            CASE lv_name
            WHEN 30022 THEN  'ALM'
            WHEN 30023 THEN  'SUP'
            WHEN 30013 THEN  'ACK'
            WHEN 30016 THEN  'CLS'
            ELSE  ' '
            END)
         into lv_timest; */
 #open lv_cur;
 #fetch lv_cur into lv_timest;
 #close lv_cur;
 #select timestamp into lv_timesta from test02 where name='fhbb';
 #select lv_timest;
 /*select FOUND_ROWS();
 update test02 set name = 'c' limit 1;
select ROW_COUNT();*/
if 'avcb' like '%cb' then
set @gv_test = 'OK_LIKE';
#insert into test02(number) values (0.284410612244898284410612244898284410612244898284410612);
end if;
select lv_timest;
end $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_train_tr_train_update`$$
CREATE PROCEDURE  `prc_train_tr_train_update`(
   IN TrainId               INT(2),             #The Train ID
   IN PrimaryTsi            VARCHAR(32),        #The TSI of the primary TIMS. And it's obsoleted when update since 28/12/2011
   IN SecondaryTsi          VARCHAR(32),        #The TSI of the secondary TIMS. And it's obsoleted when update since 28/12/2011
   IN PaLibraryVersion      INT(5),             #The PA Library Version on the train
   IN TtisLibraryVersion    INT(5),             #The TTIS Library Version on the train
   IN TtisScheduleVersion   INT(5),             #The TTIS Time Schedule Version on the train
   IN UpdateTime            BIGINT(20)          #The time the update came from the train
                                      )
BEGIN
      # Modified by Will Sept 2011
      DECLARE v_rowExists    INT(11) DEFAULT 0;
      DECLARE v_updateDate   DATETIME;

      BEGIN
         SELECT COUNT(TRAIN_ID)
           INTO v_rowExists
           FROM tr_train
          WHERE TRAIN_ID = TrainId;

         SET v_updateDate =
                DATE_SUB(
                   DATE_ADD(STR_TO_DATE('01011970', '%d%m%Y'),
                            INTERVAL UpdateTime SECOND),
                   INTERVAL 4 HOUR);

         #GST -> EDT

         IF v_rowExists > 0
         THEN
         /*
            UPDATE tr_train
               SET PRIMARY_TSI = PrimaryTsi,
                   SECONDARY_TSI = SecondaryTsi,
                   PA_LIBRARY_VERSION = PaLibraryVersion,
                   TTIS_LIBRARY_VERSION = TtisLibraryVersion,
                   TTIS_SCHEDULE_VERSION = TtisScheduleVersion,
                   TIMESTAMP = v_updateDate
             WHERE TRAIN_ID = TrainId AND v_updateDate > TIMESTAMP;
         */
            UPDATE tr_train
               SET PA_LIBRARY_VERSION = PaLibraryVersion,
                   TTIS_LIBRARY_VERSION = TtisLibraryVersion,
                   TTIS_SCHEDULE_VERSION = TtisScheduleVersion,
                   TIMESTAMP = v_updateDate
             WHERE TRAIN_ID = TrainId AND v_updateDate > TIMESTAMP;
         ELSE
            INSERT INTO tr_train(TRAIN_ID,
                                 PRIMARY_TSI,
                                 SECONDARY_TSI,
                                 PA_LIBRARY_VERSION,
                                 TTIS_LIBRARY_VERSION,
                                 TTIS_SCHEDULE_VERSION,
                                 TIMESTAMP)
            VALUES (TrainId,
                    PrimaryTsi,
                    SecondaryTsi,
                    PaLibraryVersion,
                    TtisLibraryVersion,
                    TtisScheduleVersion,
                    v_updateDate);
         END IF;

         COMMIT;
      END;
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_update_derived_state`$$
CREATE PROCEDURE  `prc_update_derived_state`(
   IN p_entityname          VARCHAR(85),                       #Name of entity
   IN p_state_value         INT(8),                               #State Value
   IN p_state_description   VARCHAR(250),                   #State description
   IN p_alarm_enabled       INT(1),
   IN p_alarm_delay         INT(8),
   IN p_alarm_message       VARCHAR(250),
   IN p_alarm_severity      VARCHAR(9),
   IN p_alarm_mms           VARCHAR(250),
   IN p_return_condition    VARCHAR(250),
   IN p_filename            VARCHAR(500))
BEGIN
      #Modified by Will Sept 2011
      DECLARE v_epkey              INT(9);
      DECLARE l_return_condition   VARCHAR(200);

      #Add default value.
      if p_return_condition is null or p_return_condition = '' then
      SET p_return_condition = ' ';
      end if;

      set l_return_condition = p_return_condition;

      /* IF l_return_condition IS NULL or l_return_condition = ''
      THEN
         SET l_return_condition = ' ';
      END IF;
      */

      SELECT pkey
        INTO v_epkey
        FROM entity
       WHERE name = p_entityname;

      UPDATE sc_derived_state
         SET state_value = p_state_value,
             state_description = p_state_description,
             alarm_enabled = p_alarm_enabled,
             alarm_delay = p_alarm_delay,
             alarm_message = p_alarm_message,
             alarm_severity = p_alarm_severity,
             alarm_mms = p_alarm_mms,
             state_return_condition = l_return_condition
       WHERE derived_dp_pkey = v_epkey;
   END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_update_plans_seq`$$
CREATE PROCEDURE  `prc_update_plans_seq`(IN v_seq_name varchar(30))
BEGIN
      # Modified Sept 2011
      DECLARE x                            INT(11);
      DECLARE l_step_details_pkey_max      INT(6);
      DECLARE l_node_tree_pkey_max         INT(6);
      DECLARE l_step_parameters_pkey_max   INT(6);
      DECLARE l_plans_seq_value            BIGINT(20);
      DECLARE l_upper_limit                INT(11);
      DECLARE l_lower_limit                INT(11);

      SELECT max(p_key) INTO l_step_details_pkey_max FROM step_details;

      SELECT max(p_key) INTO l_node_tree_pkey_max FROM node_tree;

      SELECT max(p_key) INTO l_step_parameters_pkey_max FROM step_parameters;

      SELECT func_seq_get_next_number('plans_seq')
        INTO l_plans_seq_value;

      SET l_lower_limit = l_plans_seq_value + 1;

      IF (l_step_details_pkey_max > l_node_tree_pkey_max)
      THEN
         SET l_upper_limit = l_step_details_pkey_max;
      ELSE
         SET l_upper_limit = l_node_tree_pkey_max;
      END IF;

      IF (l_step_parameters_pkey_max > l_upper_limit)
      THEN
         SET l_upper_limit = l_step_parameters_pkey_max;
      END IF;

      IF (l_plans_seq_value < l_upper_limit)
      THEN
         WHILE l_lower_limit <= l_upper_limit
         DO
            SELECT func_seq_get_next_number('plans_seq')
              INTO x;

            SET l_lower_limit = l_lower_limit + 1;
         END WHILE;
      END IF;
   END $$

DELIMITER ;