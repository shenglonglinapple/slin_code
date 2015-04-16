-- Triggers

DELIMITER ;;

drop trigger if exists `alarm_printevent_trg` ;;
drop trigger if exists `alarm_bf_row_audit` ;;
drop trigger if exists `alarmplanmap_bif_row_audit` ;;
drop trigger if exists `alarmplanmap_buf_row_audit` ;;
drop trigger if exists `ar_bfi_row_audit` ;;
drop trigger if exists `ar_bfu_row_audit` ;;
drop trigger if exists `alarmseverity_bif_row_audit` ;;
drop trigger if exists `alarmseverity_buf_row_audit` ;;
drop trigger if exists `approval_state_bif_row_audit` ;;
drop trigger if exists `approval_state_buf_row_audit` ;;
drop trigger if exists `arinve_bif_row_audit` ;;
drop trigger if exists `arinve_buf_row_audit` ;;
drop trigger if exists `artabl_bif_row_audit` ;;
drop trigger if exists `artabl_buf_row_audit` ;;
drop trigger if exists `atfblo_bif_trg` ;;
drop trigger if exists `atmssz_bir_trg` ;;
drop trigger if exists `atmssz_bur_trg` ;;
drop trigger if exists `atplat_bir_trg` ;;
drop trigger if exists `atplat_bur_trg` ;;
drop trigger if exists `atpoem_bif_trg` ;;
drop trigger if exists `atpoem_buf_trg` ;;
drop trigger if exists `atpema_bif_trg` ;;
drop trigger if exists `atpema_buf_trg` ;;
drop trigger if exists `attema_bif_trg` ;;
drop trigger if exists `attema_biuf_trg_u` ;;
drop trigger if exists `cocomp_audit_bir_trg` ;;
drop trigger if exists `cocomp_audit_bur_trg` ;;
drop trigger if exists `cocounter_audit_bir_trg` ;;
drop trigger if exists `cocounter_audit_bur_trg` ;;
drop trigger if exists `co_line_bfi_row_audit` ;;
drop trigger if exists `co_line_bfu_row_audit` ;;
drop trigger if exists `drdns_bir_trg` ;;
drop trigger if exists `drdns_bur_trg` ;;
drop trigger if exists `dr_datapoint_data_trg` ;;
drop trigger if exists `drps_bir_trg` ;;
drop trigger if exists `ddrdps_air_general_power_hdl_setp_trg` ;;
drop trigger if exists `drps_bur_trg` ;;
drop trigger if exists `drdps_aur_general_power_hdl_setp_trg` ;;
drop trigger if exists `drdps_adr_general_power_trg` ;;
drop trigger if exists `drlp_bir_trg` ;;
drop trigger if exists `drlp_air_trg` ;;
drop trigger if exists `drtc_bir_trg` ;;
drop trigger if exists `ecmmod_bir_trg` ;;
drop trigger if exists `ecmmod_bur_trg` ;;
drop trigger if exists `ecmmhe_bif_trg` ;;
drop trigger if exists `ecmmhe_buf_trg` ;;
drop trigger if exists `ecscol_bir_trg` ;;
drop trigger if exists `ecscol_bur_trg` ;;
drop trigger if exists `ecsmod_bif_trg` ;;
drop trigger if exists `ecsmod_buf_trg` ;;
drop trigger if exists `eczone_bif_trg` ;;
drop trigger if exists `eczone_buf_trg` ;;
drop trigger if exists `entity_bif_row_audit` ;;
drop trigger if exists `entity_buf_row_audit` ;;
drop trigger if exists `cascade_del_entity` ;;
drop trigger if exists `enparam_bif_row_audit` ;;
drop trigger if exists `enparam_buf_row_audit` ;;
drop trigger if exists `cascade_del_entparam` ;;
drop trigger if exists `epv_bif_row_audit` ;;
drop trigger if exists `epv_buf_row_audit` ;;
drop trigger if exists `entitystatusdata_bif_row_audit` ;;
drop trigger if exists `entitystatusdata_buf_row_audit` ;;
drop trigger if exists `etype_bir_audit_trg` ;;
drop trigger if exists `etype_bur_audit_trg` ;;
drop trigger if exists `cascade_del_enttype` ;;
drop trigger if exists `entypepar_bif_row_audit` ;;
drop trigger if exists `entypepar_buf_row_audit` ;;
drop trigger if exists `evcom_event_trg` ;;
drop trigger if exists `evcom_printevent_trg` ;;
drop trigger if exists `event_bir_trg` ;;
drop trigger if exists `event_evcom_air_trg` ;;
drop trigger if exists `event_evcom_aur_trg` ;;
drop trigger if exists `event_evcom_adr_trg` ;;
drop trigger if exists `eventcolour_bfi_row_audit` ;;
drop trigger if exists `eventcolour_bfu_row_audit` ;;
drop trigger if exists `eventplanmap_bfi_row_audit` ;;
drop trigger if exists `eventplanmap_bfu_row_audit` ;;
drop trigger if exists `gparam_bfi_trg` ;;
drop trigger if exists `gparam_bfu_trg` ;;
drop trigger if exists `guiapp_bfi_row_audit` ;;
drop trigger if exists `guiapp_bfu_row_audit` ;;
drop trigger if exists `ininci_bif_trg` ;;
drop trigger if exists `ininci_buf_trg` ;;
drop trigger if exists `inplan_bif_trg` ;;
drop trigger if exists `inplan_buf_trg` ;;
drop trigger if exists `inrepo_bif_trg` ;;
drop trigger if exists `inrepo_buf_trg` ;;
drop trigger if exists `instat_bif_trg` ;;
drop trigger if exists `instat_buf_trg` ;;
drop trigger if exists `lodsch_bir_trg` ;;
drop trigger if exists `lodsch_evcom_air_trg` ;;
drop trigger if exists `lodsch_evcom_aur_trg` ;;
drop trigger if exists `lodsch_evcom_adr_trg` ;;
drop trigger if exists `loc_bif_row_audit` ;;
drop trigger if exists `loc_aifr_row` ;;
drop trigger if exists `loc_buf_row_audit` ;;
drop trigger if exists `loc_auf_row` ;;
drop trigger if exists `alarm_type_bif_row_audit` ;;
drop trigger if exists `alarm_type_buf_row_audit` ;;
drop trigger if exists `msg_type_bif_row_audit` ;;
drop trigger if exists `msg_type_buf_row_audit` ;;
drop trigger if exists `node_tree_bif_row_audit` ;;
drop trigger if exists `node_tree_buf_row_audit` ;;
drop trigger if exists `node_type_bif_row_audit` ;;
drop trigger if exists `node_type_buf_row_audit` ;;
drop trigger if exists `opc_bif_row_audit` ;;
drop trigger if exists `opc_buf_row_audit` ;;
drop trigger if exists `opl_bif_row_audit` ;;
drop trigger if exists `opl_buf_row_audit` ;;
drop trigger if exists `opc_dt_interval_trigger` ;;
drop trigger if exists `sample_grp_iflag_trigger` ;;
drop trigger if exists `sample_grp_uflag_trigger` ;;
drop trigger if exists `sample_grp_dflag_trigger` ;;
drop trigger if exists `operator_bif_row_audit` ;;
drop trigger if exists `operator_air_trg` ;;
drop trigger if exists `operator_buf_row_audit` ;;
drop trigger if exists `operator_aur_trg` ;;
drop trigger if exists `operator_bdr_trg` ;;
drop trigger if exists `paatbr_bif_trg` ;;
drop trigger if exists `paatbr_buf_trg` ;;
drop trigger if exists `padmes_bif_trg` ;;
drop trigger if exists `padmes_buf_trg` ;;
drop trigger if exists `padmprve_bif_trg` ;;
drop trigger if exists `padmprve_buf_trg` ;;
drop trigger if exists `padmpuve_bif_trg` ;;
drop trigger if exists `padmpuve_buf_trg` ;;
drop trigger if exists `padmve_bif_trg` ;;
drop trigger if exists `padmve_buf_trg` ;;
drop trigger if exists `pastat_bif_trg` ;;
drop trigger if exists `pastat_buf_trg` ;;
drop trigger if exists `patmmap_bif_trg` ;;
drop trigger if exists `patmmap_buf_trg` ;;
drop trigger if exists `patdme_tif_trg` ;;
drop trigger if exists `patdme_tuf_trg` ;;
drop trigger if exists `pazone_bif_trg` ;;
drop trigger if exists `pazone_buf_trg` ;;
drop trigger if exists `pazgro_bif_trg` ;;
drop trigger if exists `pazgro_buf_trg` ;;
drop trigger if exists `pazghe_bif_trg` ;;
drop trigger if exists `pazghe_buf_trg` ;;
drop trigger if exists `pazhel_bif_trg` ;;
drop trigger if exists `pazhel_buf_trg` ;;
drop trigger if exists `param_type_bif_row_audit` ;;
drop trigger if exists `param_type_buf_row_audit` ;;
drop trigger if exists `ra_btncfg_bif_row_audit` ;;
drop trigger if exists `ra_btncfg_buf_row_audit` ;;
drop trigger if exists `racshi_bir_trg` ;;
drop trigger if exists `radent_bif_row_audit` ;;
drop trigger if exists `radent_buf_row_audit` ;;
drop trigger if exists `radmem_bif_row_audit` ;;
drop trigger if exists `radmem_buf_row_audit` ;;
drop trigger if exists `ragmem_bir_trg` ;;
drop trigger if exists `raigro_audit_bir_trg` ;;
drop trigger if exists `raigro_audit_bur_trg` ;;
drop trigger if exists `rapmem_bir_trg` ;;
drop trigger if exists `raptex_bif_row_audit` ;;
drop trigger if exists `raptex_buf_row_audit` ;;
drop trigger if exists `rasc_bir_trg` ;;
drop trigger if exists `ra_subscriber_bif_row_audit` ;;
drop trigger if exists `ra_subscriber_buf_row_audit` ;;
drop trigger if exists `ratinb_bif_row_audit` ;;
drop trigger if exists `ratinb_buf_row_audit` ;;
drop trigger if exists `razone_bif_trg` ;;
drop trigger if exists `razone_buf_trg` ;;
drop trigger if exists `scerep_bir_trg` ;;
drop trigger if exists `scerep_bur_trg` ;;
drop trigger if exists `sceren_bir_trg` ;;
drop trigger if exists `sceren_bur_trg` ;;
drop trigger if exists `scotal_audit_bir_trg` ;;
drop trigger if exists `scotal_audit_bur_trg` ;;
drop trigger if exists `scssch_audit_bir_trg` ;;
drop trigger if exists `scssch_audit_bur_trg` ;;
drop trigger if exists `seacti_audit_bir_trg` ;;
drop trigger if exists `seacti_audit_bur_trg` ;;
drop trigger if exists `actgro_audit_bir_trg` ;;
drop trigger if exists `actgro_audit_bur_trg` ;;
drop trigger if exists `seagmap_audit_bir_trg` ;;
drop trigger if exists `update_on_update_se_xxx_i_trg` ;;
drop trigger if exists `seagmap_audit_bur_trg` ;;
drop trigger if exists `update_on_update_se_xxx_u_trg` ;;
drop trigger if exists `update_on_update_se_xxx_d_trg` ;;
drop trigger if exists `seopro_audit_bir_trg` ;;
drop trigger if exists `seopro_audit_bur_trg` ;;
drop trigger if exists `seorge_bir_trg` ;;
drop trigger if exists `seorge_bur_trg` ;;
drop trigger if exists `seprof_audit_bir_trg` ;;
drop trigger if exists `seprof_audit_bur_trg` ;;
drop trigger if exists `sepacc_audit_bir_trg` ;;
drop trigger if exists `sepacc_audit_bur_trg` ;;
drop trigger if exists `sepgro_audit_bir_trg` ;;
drop trigger if exists `sepgro_audit_bur_trg` ;;
drop trigger if exists `sepp_audit_bir_trg` ;;
drop trigger if exists `sepp_audit_bur_trg` ;;
drop trigger if exists `septyp_audit_bir_trg` ;;
drop trigger if exists `septyp_audit_bur_trg` ;;
drop trigger if exists `seregi_bir_trg` ;;
drop trigger if exists `seregi_bur_trg` ;;
drop trigger if exists `sessta_bir_trg` ;;
drop trigger if exists `sessta_bur_trg` ;;
drop trigger if exists `sngmon_audit_bir_trg` ;;
drop trigger if exists `sngmon_audit_bur_trg` ;;
drop trigger if exists `snmpro_audit_bir_trg` ;;
drop trigger if exists `snmpro_audit_bur_trg` ;;
drop trigger if exists `snscon_audit_bir_trg` ;;
drop trigger if exists `snscon_audit_bur_trg` ;;
drop trigger if exists `snscgr_audit_bir_trg` ;;
drop trigger if exists `snscgr_audit_bur_trg` ;;
drop trigger if exists `sosfil_bif_row_audit` ;;
drop trigger if exists `sosfil_buf_row_audit` ;;
drop trigger if exists `step_details_bif_row_audit` ;;
drop trigger if exists `step_details_buf_row_audit` ;;
drop trigger if exists `step_params_bif_row_audit` ;;
drop trigger if exists `step_params_buf_row_audit` ;;
drop trigger if exists `step_type_bif_row_audit` ;;
drop trigger if exists `step_type_buf_row_audit` ;;
drop trigger if exists `st_partype_bif_audit` ;;
drop trigger if exists `st_partype_buf_audit` ;;
drop trigger if exists `subsystem_bif_row_audit` ;;
drop trigger if exists `subsystem_aif_trg` ;;
drop trigger if exists `subsystem_buf_row_audit` ;;
drop trigger if exists `ta_sess_bif_row_audit` ;;
drop trigger if exists `ta_sess_buf_row_audit` ;;
drop trigger if exists `tri_bandelsupsess` ;;
drop trigger if exists `tedent_bif_trg` ;;
drop trigger if exists `tedent_buf_trg` ;;
drop trigger if exists `tesdbu_bif_trg` ;;
drop trigger if exists `tesdbu_buf_trg` ;;
drop trigger if exists `tesdse_bif_trg` ;;
drop trigger if exists `tesdse_buf_trg` ;;
drop trigger if exists `tesubd_bif_trg` ;;
drop trigger if exists `tesubd_buf_trg` ;;
drop trigger if exists `test_insert_date` ;;
drop trigger if exists `trg_test02_name` ;;
drop trigger if exists `tidreq_bif_row_audit` ;;
drop trigger if exists `tidreq_buf_row_audit` ;;
drop trigger if exists `tirdes_bif_trg` ;;
drop trigger if exists `tirdes_buf_trg` ;;
drop trigger if exists `tirtag_bif_trg` ;;
drop trigger if exists `tirtag_buf_trg` ;;
drop trigger if exists `trtem_bif_row_audit` ;;
drop trigger if exists `trtem_buf_row_audit` ;;
drop trigger if exists `version_bif_row_audit` ;;
drop trigger if exists `version_buf_row_audit` ;;
drop trigger if exists `vistationid_bif_trg` ;;
drop trigger if exists `vistationid_buf_trg` ;;
drop trigger if exists `vitrev_bif_trg` ;;
drop trigger if exists `vitrev_buf_trg` ;;

DELIMITER ;

/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER alarm_printevent_trg
AFTER INSERT ON alarm FOR EACH ROW
BEGIN
# Modified by Will Sept 2011
   declare v_pkey            int(11);
   DECLARE v_printalarm    INT(9) DEFAULT 0;
   DECLARE occ_locationkey INT(9);
   DECLARE v_locationkey   INT(9);
   DECLARE v_physical_subsystem_key INT(9);
   DECLARE v_subsystem_key INT(9);
   DECLARE v_printer       VARCHAR(50) DEFAULT NULL;
   DECLARE v_occ_printer   VARCHAR(50) DEFAULT NULL;
   DECLARE v_alarmtype     VARCHAR(30);
   DECLARE v_planstate     VARCHAR(30);
   DECLARE v_mmsstate      VARCHAR(30);
   DECLARE v_avlstate      VARCHAR(30);
   DECLARE v_severityname  VARCHAR(20);
   DECLARE v_operatorname  VARCHAR(85);

   DECLARE no_more_rows    BOOLEAN DEFAULT FALSE;

   DECLARE p_entitykey INT(9);
   DECLARE cu_entity CURSOR FOR
        SELECT
            subsystemkey AS SUBSYSTEM_KEY,
            physical_subsystem_key AS PHYSICAL_SUBSYSTEM_KEY,
            locationkey AS LOCATION_KEY
        FROM entity
        WHERE pkey = p_entitykey;
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;

/*    CURSOR cu_entity(p_entitykey NUMBER) IS
        SELECT
            subsystemkey AS SUBSYSTEM_KEY,
            physical_subsystem_key AS PHYSICAL_SUBSYSTEM_KEY,
            locationkey AS LOCATION_KEY
        FROM entity
        WHERE pkey = p_entitykey;
    */

# optimize the trigger performance
BEGIN
        select print_alarm into v_printalarm from me_alarm_type where meatyp_id = NEW.type;
      IF no_more_rows THEN
        SET v_printalarm = 0;
      END IF;
    END;



    IF (v_printalarm = 1) THEN
        # get subsystem_key, physical_subsystem_key, location_key
        SET p_entitykey = NEW.entitykey;
        OPEN cu_entity;
            FETCH cu_entity INTO v_subsystem_key,v_physical_subsystem_key,v_locationkey;
        CLOSE cu_entity;

# get printer name
# ++ AZ : TD14242
SET no_more_rows = FALSE;
BEGIN
            IF (v_physical_subsystem_key <> '') THEN
                SELECT printer into v_printer from online_printer
                WHERE LOCATIONKEY = v_locationkey AND IS_ALARM = 1 AND SUBSYSTEMKEY = v_physical_subsystem_key;
            END IF;

            IF ((v_printer IS NULL or v_printer = '') AND v_subsystem_key <> '') THEN
                SELECT printer INTO v_printer FROM online_printer
                WHERE LOCATIONKEY = v_locationkey AND IS_ALARM = 1 AND SUBSYSTEMKEY = v_subsystem_key;
            END IF;

            IF (v_printer IS NULL or v_printer = '') THEN
                SELECT def_printer INTO v_printer FROM online_printcfg
                WHERE LOCATIONKEY = v_locationkey;
            END IF;

          IF no_more_rows THEN
            SELECT def_printer INTO v_printer FROM online_printcfg
            WHERE LOCATIONKEY = v_locationkey;
          END IF;
        END;
# AZ ++ : TD14242

# get alarm type
#select nvl2(:NEW.ACKNOWLEDGED_BY, 'ACK', 'ALM')

SELECT 'ALM' INTO v_alarmtype FROM dual;

# get plan state

SELECT (CASE
           WHEN NEW.PLANSTATUS = 'NoAssociatedPlan' THEN ' '
           WHEN NEW.PLANSTATUS = 'AutoPlansNotRun' THEN 'A'
           WHEN NEW.PLANSTATUS = 'SemiAutoPlansNotRun' THEN 'S'
           WHEN NEW.PLANSTATUS = 'PlansRun' THEN 'R'
           WHEN NEW.PLANSTATUS = 'PlanPostponed' THEN 'X'
           ELSE ' '
        END)
  INTO v_planstate;


/*select decode(NEW.PLANSTATUS,
                'NoAssociatedPlan',' ',
                'AutoPlansNotRun','A',
                'SemiAutoPlansNotRun','S',
                'PlansRun','R',
                'PlanPostponed','X',
                ' ')
        into v_planstate
        from dual;
        */

# ++ CF : TD14536
# get MMS state

SELECT (CASE
           WHEN NEW.MMS_STATE_TYPE = 0 THEN ' '
           WHEN NEW.MMS_STATE_TYPE = 1 THEN 'S'
           WHEN NEW.MMS_STATE_TYPE = 2 THEN 'A'
           WHEN NEW.MMS_STATE_TYPE = 3 THEN 'R'
           WHEN NEW.MMS_STATE_TYPE = 4 THEN ' '
           WHEN NEW.MMS_STATE_TYPE = 5 THEN 'I'
           WHEN NEW.MMS_STATE_TYPE = 6 THEN 'D'
           ELSE ' '
        END)
  INTO v_mmsstate;


/*select decode(:NEW.MMS_STATE_TYPE,
                0,' ',
                1,'S',
                2,'A',
                3,'R',
                4,' ',
                5,'I',
                6,'D',
                ' ')
        into v_mmsstate
        from dual;
        */

# get AVL state

SELECT (CASE
           WHEN NEW.AVL_STATUS = 0 THEN ' '
           WHEN NEW.AVL_STATUS = 1 THEN 'H'
           WHEN NEW.AVL_STATUS = 2 THEN 'F'
           ELSE ' '
        END)
  INTO v_avlstate;


/*select decode(:NEW.AVL_STATUS,
                0,' ',
                1,'H',
                2,'F',
                ' ')
        into v_avlstate
        from dual;
        */
# CF ++ : TD14536

# all nonOCC event or alarm must send to OCC

SELECT pkey
  INTO occ_locationkey
  FROM location
 WHERE name = 'OCC';

# get severity name

SELECT name
  INTO v_severityname
  FROM alarmseverity
 WHERE pkey = NEW.SEVERITY;

# get operator name
SET no_more_rows = FALSE;
BEGIN
            IF ( NEW.ACKNOWLEDGED_BY <> '') THEN
                select name into v_operatorname from operator
                where pkey=(select operatorkey from ta_session where pkey=NEW.ACKNOWLEDGED_BY);
            END IF;
          IF no_more_rows THEN
            SET v_operatorname = NULL;
          END IF;
        END;

        IF (v_locationkey <> occ_locationkey) THEN
# ++ AZ : TD14242
            SET no_more_rows = FALSE;
BEGIN
                IF (v_physical_subsystem_key <> '') THEN
                    SELECT printer into v_occ_printer from online_printer
                    WHERE LOCATIONKEY = occ_locationkey AND IS_ALARM = 1 AND SUBSYSTEMKEY = v_physical_subsystem_key;
                END IF;

                IF ((v_occ_printer IS NULL or v_occ_printer = '') AND v_subsystem_key <> '') THEN
                    SELECT printer INTO v_occ_printer FROM online_printer
                    WHERE LOCATIONKEY = occ_locationkey AND IS_ALARM = 1 AND SUBSYSTEMKEY = v_subsystem_key;
                END IF;

                IF (v_occ_printer IS NULL or v_occ_printer = '') THEN
                    SELECT def_printer INTO v_occ_printer FROM online_printcfg
                    WHERE LOCATIONKEY = occ_locationkey;
                END IF;

                IF no_more_rows THEN
                  SELECT def_printer INTO v_occ_printer FROM online_printcfg
                  WHERE LOCATIONKEY = occ_locationkey;
                END IF;
            END;
# AZ ++ : TD14242

SELECT func_seq_get_next_number('PRINTABLE_EVENT_SEQ') INTO v_pkey FROM DUAL;

INSERT INTO printable_event(pkey,
                            alarm_id,
                            event_id,
                            printer,
                            alarmflag,
                            createtime,
                            severity,
                            asset,
                            description,
                            value,
                            mms,
                            dss,
                            avalanche,
                            operatorname,
                            alarm_comment,
                            alm,
                            location_key)
   SELECT v_pkey,
          NEW.ALARM_ID,
          NULL,
          v_occ_printer,
          'ALARM',
          date_format(new.sourcetime, '%d-%m-%y %H:%m:%s'),
          #to_char(:NEW.SOURCETIME, 'DD-MM-YY HH24:MI:SS'),
          v_severityname,
          NEW.ASSET_NAME,
          NEW.DESCRIPTION,
          NEW.CONTEXT,
          v_mmsstate,
          v_planstate,
          v_avlstate,
          NULL,
          ifnull(NEW.COMMENTS, 'C'),
          v_alarmtype,
          occ_locationkey
     FROM DUAL;

        END IF;

# all event/alarm should send to their owner

SELECT func_seq_get_next_number('PRINTABLE_EVENT_SEQ') INTO v_pkey FROM DUAL;

INSERT INTO printable_event(pkey,
                            alarm_id,
                            event_id,
                            printer,
                            alarmflag,
                            createtime,
                            severity,
                            asset,
                            description,
                            value,
                            mms,
                            dss,
                            avalanche,
                            operatorname,
                            alarm_comment,
                            alm,
                            location_key)
   SELECT v_pkey,
          NEW.ALARM_ID,
          NULL,
          v_printer,
          'ALARM',
          date_format(new.sourcetime, '%d-%m-%y %H:%m:%s'),
          #to_char(:NEW.SOURCETIME, 'DD-MM-YY HH24:MI:SS'),
          v_severityname,
          NEW.ASSET_NAME,
          NEW.DESCRIPTION,
          NEW.CONTEXT,
          v_mmsstate,
          v_planstate,
          v_avlstate,
          NULL,
          ifnull(NEW.COMMENTS, 'C'),
          v_alarmtype,
          v_locationkey
     FROM DUAL;

    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarm_bf_row_audit` BEFORE UPDATE
    ON alarm FOR EACH ROW
BEGIN
    IF old.state = 1 and new.state = 0 then
	    IF new.acknowledged_by <> '' then
	     SET new.expired = sysdate();
      END IF;
    ELSEIF (old.acknowledged_by is null or old.acknowledged_by = '') and new.acknowledged_by <> '' then
      IF new.state = 0 then
         SET new.expired = sysdate();
      END IF;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `alarm_inhibition_view`
--


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarmplanmap_bif_row_audit` BEFORE INSERT
    ON alarmplanmaps FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarmplanmap_buf_row_audit` BEFORE UPDATE
    ON alarmplanmaps FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ar_bfi_row_audit` BEFORE INSERT
    ON alarmrule FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ar_bfu_row_audit` BEFORE UPDATE
    ON alarmrule FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarmseverity_bif_row_audit` BEFORE INSERT
    ON alarmseverity FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarmseverity_buf_row_audit` BEFORE UPDATE
    ON alarmseverity FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `approval_state_bif_row_audit` BEFORE INSERT
    ON approval_state FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `approval_state_buf_row_audit` BEFORE UPDATE
    ON approval_state FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `arinve_bif_row_audit` BEFORE INSERT
    ON ar_inventory FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `arinve_buf_row_audit` BEFORE UPDATE
    ON ar_inventory FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `artabl_bif_row_audit` BEFORE INSERT
    ON ar_tables FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `artabl_buf_row_audit` BEFORE UPDATE
    ON ar_tables FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atfblo_bif_trg` BEFORE INSERT
    ON at_fixed_block_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `at_fixed_block_map_v`
--


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atmssz_bir_trg` BEFORE INSERT
    ON at_msszone FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atmssz_bur_trg` BEFORE UPDATE ON at_msszone FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atplat_bir_trg` BEFORE INSERT
    ON at_platform FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atplat_bur_trg` BEFORE UPDATE
    ON at_platform FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atpoem_bif_trg` BEFORE INSERT
    ON at_power_entity_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atpoem_buf_trg` BEFORE UPDATE
    ON at_power_entity_map FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `at_power_entity_map_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atpema_bif_trg` BEFORE INSERT
    ON at_psd_entity_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `atpema_buf_trg` BEFORE UPDATE
    ON at_psd_entity_map FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `at_psd_entity_map_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `attema_bif_trg` BEFORE INSERT
    ON at_twp_entity_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER attema_biuf_trg_u
 BEFORE UPDATE ON at_twp_entity_map FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;



--
-- Temporary table structure for view `category_details`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cocomp_audit_bir_trg` BEFORE INSERT
    ON co_component FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cocomp_audit_bur_trg` BEFORE UPDATE
    ON co_component FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cocounter_audit_bir_trg` BEFORE INSERT
    ON co_counter FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cocounter_audit_bur_trg` BEFORE UPDATE
    ON co_counter FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `co_line_bfi_row_audit` BEFORE INSERT
    ON co_line FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `co_line_bfu_row_audit` BEFORE UPDATE
    ON co_line FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;



--
-- Temporary table structure for view `datanode_ev`
--


--
-- Temporary table structure for view `datanodeagent_ev`
--


--
-- Temporary table structure for view `datapoint_ev_01`
--


--
-- Temporary table structure for view `datapoint_ev_02`
--


--
-- Temporary table structure for view `detailed_fault_view`
--


--
-- Temporary table structure for view `dp_is_manually_dressed_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `drdns_bir_trg` BEFORE INSERT
    ON dr_datanode_state FOR EACH ROW
BEGIN
  SET NEW.UPDATETIME = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `drdns_bur_trg` BEFORE UPDATE
    ON dr_datanode_state FOR EACH ROW
BEGIN
  SET NEW.UPDATETIME = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `dr_datapoint_12min_view`
--


--
-- Temporary table structure for view `dr_datapoint_1min_view`
--


--
-- Temporary table structure for view `dr_datapoint_2min_view`
--



--
-- Temporary table structure for view `dr_datapoint_3min_view`
--



--
-- Temporary table structure for view `dr_datapoint_4min_view`
--


--
-- Temporary table structure for view `dr_datapoint_5min_view`
--


--
-- Temporary table structure for view `dr_datapoint_6min_view`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER dr_datapoint_data_trg
BEFORE INSERT ON dr_datapoint_data FOR EACH ROW
BEGIN
DECLARE v_sourcedate date DEFAULT NULL;
DECLARE no_data_found boolean DEFAULT FALSE;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET no_data_found=TRUE;

   SET NEW.logtime = SYSDATE();
   SET NEW.timeofday = ifnull(NEW.timeofday,0);
 IF NEW.sourcedate IS NULL or NEW.sourcedate = '' OR NEW.sourcedate = str_to_date('01/01/1970','%d/%m/%Y') THEN
  SET NEW.sourcedate = date(NEW.sourcetime);
  SET NEW.timeofday = timestampdiff(second,NEW.sourcedate,NEW.sourcetime);#(:NEW.sourcetime - :NEW.sourcedate) * 86400;
 ELSE
  SET NEW.sourcedate = date(NEW.sourcedate);
 END IF;

    BEGIN
        SELECT sourcedate INTO v_sourcedate FROM dr_datapoint_date WHERE sourcedate=NEW.sourcedate;
    IF no_data_found THEN
      SET v_sourcedate=NULL;
    END IF;
    END;

    IF (v_sourcedate IS NULL or v_sourcedate = '') THEN
        INSERT INTO dr_datapoint_date(sourcedate) VALUES(NEW.sourcedate);
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;



--
-- Temporary table structure for view `dr_datapoint_real_view`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER drps_bir_trg

BEFORE INSERT ON dr_datapoint_state FOR EACH ROW
BEGIN
	SET NEW.UPDATETIME = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ddrdps_air_general_power_hdl_setp_trg` AFTER INSERT ON dr_datapoint_state FOR EACH ROW
BEGIN
# Modified by Will Sept 2011
  # not_a_number        EXCEPTION;
  # PRAGMA EXCEPTION_INIT (not_a_number, -1722);
  DECLARE v_sourcetime        DATETIME;
  DECLARE v_entityname        VARCHAR (85);
  DECLARE v_value             INT(11);
  DECLARE v_quality           INT(11);
  DECLARE v_new_record        BOOLEAN;
  DECLARE v_demand            INT(11);
  DECLARE v_tariff            INT(2);
  DECLARE v_setpoint          DECIMAL(22, 0);
  DECLARE v_setpointname      VARCHAR (85);
  DECLARE v_int               INT(5);
  DECLARE v_old               INT(11);
  DECLARE v_new               INT(11);
  DECLARE v_counter           INT(11);
  DECLARE v_loop              INT(11);
  DECLARE v_diff              BIGINT(22);
  DECLARE v_head              BIGINT(22);
  DECLARE v_end               BIGINT(22);
  DECLARE v_demandpersecond   decimal(38,30);
  DECLARE v_head_demand       decimal(38,30);
  DECLARE v_end_demand        decimal(38,30);
  DECLARE my_demand           decimal(38,30);
  DECLARE v_time              DATETIME;
  DECLARE v_newint            INT(11);
   
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';
DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';

# begin of the oracle trigger drdps_air_general_trg
# inserting a record for the first time, evaluate VALUE column and process insert if it is a number
   IF NEW.value <> '' THEN
      INSERT INTO dr_datapoint_data (sourcetime,entitykey,sourcedate,timeofday,logtime,value)
               VALUES (NEW.sourcetime,NEW.entitykey,NULL,NULL,SYSDATE(),NEW.value);
   END IF;
# end of the oracle trigger drdps_air_general_trg

  # Start Trigger DRDPS_AIR_PWR_TRG



      IF func_dr_pwr_api_is_pwr_point (NEW.entitykey)
      THEN
         # called dr_pwr_api_pkg.ispwrpoint
        set v_int = func_dr_pwr_api_get_interval (NEW.sourcetime);

   # dr_pwr_api_pkg.get_tariff_setpoint(:NEW.entitykey,v_tariff,v_setpoint);
# v_tariff := dr_pwr_api_pkg.get_tariff(:NEW.entitykey);
# v_setpoint := dr_pwr_api_pkg.get_setpoint(:NEW.entitykey);
         IF func_dr_pwr_api_is_pwr_point_exist (NEW.entitykey)
         THEN
           call prc_dr_pwr_api_get_tariff_setpoint (NEW.entitykey,
                                                v_tariff,
                                                v_setpoint
                                               );
             /* ( 'Power record with the entity key '
                                  || :NEW.entitykey
                                  || ' already exist'
                                 );
             */
            IF func_dr_pwr_api_is_pwr_point_same (NEW.entitykey,
                                                 NEW.sourcetime
                                                )
                                                
            then
              begin end;
               /* (   'Power recod with the entitykey '
                                     || :NEW.entitykey
                                     || ' and sourcetime  '
                                     || :NEW.sourcetime
                                     || ' already exist.'
                                    );
               */
            ELSE
              call prc_dr_pwr_api_upd_pwr_point (NEW.entitykey,
                                             NEW.sourcetime,
                                             NEW.VALUE,
                                             v_demand
                                            );
              call prc_dr_pwr_api_get_interval_diff (null,
                                                 NEW.sourcetime,
                                                 v_old,
                                                 v_new,
                                                 v_counter
                                                );

               
                              /*  (   'after get_interval_diff, before if :::::'
                                 || TO_CHAR (v_counter - 1)
                                );
                              */

               IF v_counter > 0
               THEN
                  /* (   'begin time diff  :: '
                                        || TO_CHAR (:OLD.sourcetime,
                                                    'MM/DD/YYYY HH24:MI:SS'
                                                   )
                                        || ',   '
                                        || TO_CHAR (:NEW.sourcetime,
                                                    'MM/DD/YYYY HH24:MI:SS'
                                                   )
                                       );
                  */
                  
                  set v_diff = timestampdiff(second,null,NEW.sourcetime);
                  # end time diff: 
                  set v_demandpersecond = v_demand / v_diff;
                  /*   'begin convert '
                                        || v_diff
                                        || '  :  '
                                        || v_demandpersecond
                  */
                  set v_head =
                       v_old * 1800
                     - HOUR(null) * 60 * 60
                     - MINUTE(null) * 60
                     - SECOND(null)
                     - 1;
                  set v_end =
                       HOUR (NEW.sourcetime) * 60 * 60
                     + MINUTE (NEW.sourcetime) * 60
                     + SECOND (NEW.sourcetime)
                     - (v_new - 1) * 1800
                     + 1;
                  /* (   'here:  v_head: '
                                        || v_head
                                        || ' and v_end: '
                                        || v_end
                                       );
                  */
                  # convert done
                  set v_head_demand = v_demandpersecond * v_head;
                  set v_end_demand = v_demandpersecond * v_end;
                  set v_loop = 1;

                  WHILE v_loop < v_counter DO
                  
                    set v_time =
                              date(null)
                            + (v_old + v_loop - 1) / 48;
                    set my_demand = v_demandpersecond * 1800;
                    set v_newint = v_old + v_loop;

                     IF (v_newint >= 49)
                     THEN
                       set v_newint = MOD (v_newint, 49) + 1;
                     END IF;

                    call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                       v_time,
                                                       v_newint,
                                                       v_tariff,
                                                       v_setpoint,
                                                       v_setpointname,
                                                       my_demand
                                                      );
                     set v_loop = v_loop + 1;
                  END WHILE;

                  #after while loop
                  set v_time = date(NEW.sourcetime) + (v_new - 1) / 48;
                  call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                    v_time,
                                                    v_new,
                                                    v_tariff,
                                                    v_setpoint,
                                                    v_setpointname,
                                                    v_end_demand
                                                   );
                  set v_time = date(null) + (v_old - 1) / 48;
                  call dr_pwr_api_upd_30min_pwr_point (NEW.entitykey,
                                                      v_time,
                                                      v_old,
                                                      v_head_demand
                                                     );



               ELSEIF (func_dr_pwr_api_is_30min_pwr_point_exist
                                                             (NEW.entitykey,
                                                              NEW.sourcetime,
                                                              v_int
                                                             )
                     )
               THEN
                  # in trigger, insert 30min talbe
                  call prc_dr_pwr_api_upd_30min_pwr_point (NEW.entitykey,
                                                      NEW.sourcetime,
                                                      v_int,
                                                      v_demand
                                                     );
               ELSE
                  call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                    NEW.sourcetime,
                                                    v_int,
                                                    v_tariff,
                                                    v_setpoint,
                                                    v_setpointname,
                                                    0
                                                   );
               END IF;
            END IF;
         ELSE
         /*
            EXECUTE IMMEDIATE 'INSERT INTO dr_pwrdmd_data values(:b1,:b2,:b3)'
                        USING :NEW.entitykey, :NEW.sourcetime, :NEW.VALUE;
         */

         insert into dr_pwrdmd_data values (new.entitykey,new.sourcetime,new.value);

          call prc_dr_pwr_api_get_tariff_setpoint (NEW.entitykey,
                                                v_tariff,
                                                v_setpoint
                                               );
            # 'done my set point'
            #'Inserting new record into pwr_dmd_30min_table'
          call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                              NEW.sourcetime,
                                              v_int,
                                              v_tariff,
                                              v_setpoint,
                                              v_setpointname,
                                              0
                                             );
         END IF;
#           EXECUTE IMMEDIATE 'insert into pwr_dmd_log values (:b1,
# :b2,
# :b3,
# :b4,
# :b5,
# :b6,
# :b7,
# :b8,
# :b9,
# :b10,
# :b11,
# :b12,
# :b13,
# :b14,
# :b15,
# :b16,
# :b17,
# :b18,
# :b19,
# :b20,
# :b21,
# :b22,
# :b23,
# :b24
# )'
#                            USING :OLD.sourcetime,
#                                  :NEW.sourcetime,
#                                  :NEW.entitykey,
#                                  :NEW.VALUE,
#                                  v_quality,
#                                  v_demand,
#                                  v_tariff,
#                                  v_setpoint,
#                                  v_setpointname,
#                                  v_int,
#                                  v_old,
#                                  v_new,
#                                  v_counter,
#                                  v_loop,
#                                  v_diff,
#                                  v_head,
#                                  v_end,
#                                  v_demandpersecond,
#                                  v_head_demand,
#                                  v_end_demand,
#                                  my_demand,
#                                  v_time,
#                                  v_newint,
# 								 :old.value;
   END IF;

# Start of trigger handle_setpoint_tariff_ai_trg
BEGIN
   DECLARE v_entityname    VARCHAR(85);
   DECLARE v_value         int(11);
   DECLARE v_tariff        int(11);
   DECLARE v_setpoint      int(11);
   DECLARE v_what          varchar(20);
   DECLARE v_len           int(11);
   DECLARE v_location      varchar(20);
   DECLARE v_locationkey   int(11);
   DECLARE v_num           int(11);

   SELECT name
     INTO v_entityname
     FROM entity
    WHERE pkey = NEW.entitykey;

   # dbms_output.put_line('in trigger: handle_setpoint_tariff_trg, the entityname is: ' || v_entityname);
   IF v_entityname LIKE '%SYS.PWR.DMD.diiSYS-PwrDmdTariffOffOnPeak'
   THEN
      SET v_what = 'tariff';
      SET v_len = instr(binary v_entityname, '.');
      SET v_location = substr(v_entityname, 1, v_len - 1);

      SELECT pkey
        INTO v_locationkey
        FROM location
       WHERE upper(name) = upper(v_location);

      SELECT count(*)
        INTO v_num
        FROM dr_pwrdmd_config
       WHERE locationkey = v_locationkey;

      IF v_num = 1
      THEN
         UPDATE dr_pwrdmd_config
            SET tariff = new.value
          WHERE locationkey = v_locationkey;
      ELSE
         INSERT INTO dr_pwrdmd_config(locationkey, location, tariff)
         VALUES (v_locationkey, v_location, new.value);
      END IF;
   ELSEIF v_entityname LIKE '%SYS.PWR.DMDSP.miiSYS-PwrDmdSetPoint'
   THEN
      SET v_what = 'setpoint';
      SET v_len = instr(binary v_entityname, '.');
      SET v_location = substr(v_entityname, 1, v_len - 1);

      SELECT pkey
        INTO v_locationkey
        FROM location
       WHERE upper(name) = upper(v_location);

      SELECT count(*)
        INTO v_num
        FROM dr_pwrdmd_config
       WHERE locationkey = v_locationkey;

      IF v_num = 1
      THEN
         UPDATE dr_pwrdmd_config
            SET setpoint = new.value
          WHERE locationkey = v_locationkey;
      ELSE
         INSERT INTO dr_pwrdmd_config(locationkey, location, setpoint)
         VALUES (v_locationkey, v_location, new.value);
      END IF;
   ELSE
      SET v_what = 'none';
   END IF;
#dbms_output.put_line('done handle_tariff_setpoint_trg');
END;
# end of the trigger handle_setpoint_tariff_ai_trg

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER drps_bur_trg

BEFORE UPDATE ON dr_datapoint_state FOR EACH ROW
BEGIN
	SET NEW.UPDATETIME = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `drdps_aur_general_power_hdl_setp_trg` AFTER UPDATE ON dr_datapoint_state FOR EACH ROW
BEGIN
# Modified by Will Sept 2011
  # not_a_number        EXCEPTION;
  # PRAGMA EXCEPTION_INIT (not_a_number, -1722);
  DECLARE v_sourcetime        DATETIME;
  DECLARE v_entityname        VARCHAR (85);
  DECLARE v_value             INT(11);
  DECLARE v_quality           INT(11);
  DECLARE v_new_record        BOOLEAN;
  DECLARE v_demand            INT(11);
  DECLARE v_tariff            INT(2);
  DECLARE v_setpoint          DECIMAL(22, 0);
  DECLARE v_setpointname      VARCHAR (85);
  DECLARE v_int               INT(5);
  DECLARE v_old               INT(11);
  DECLARE v_new               INT(11);
  DECLARE v_counter           INT(11);
  DECLARE v_loop              INT(11);
  DECLARE v_diff              BIGINT(22);
  DECLARE v_head              BIGINT(22);
  DECLARE v_end               BIGINT(22);
  DECLARE v_demandpersecond   decimal(38,30);
  DECLARE v_head_demand       decimal(38,30);
  DECLARE v_end_demand        decimal(38,30);
  DECLARE my_demand           decimal(38,30);
  DECLARE v_time              DATETIME;
  DECLARE v_newint            INT(11);
   
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';
DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';

# Start the trigger drdps_aur_general_trg
# inserting a record for the first time, evaluate VALUE column and process insert if it is a number--

   IF OLD.value != NEW.value THEN
      INSERT INTO DR_DATAPOINT_DATA (sourcetime,entitykey,sourcedate,timeofday,logtime,value)
              VALUES (NEW.sourcetime,NEW.entitykey,NULL,NULL,SYSDATE(),NEW.value);
   END IF;
# end the trigger drdps_aur_general_trg   

  # Start Trigger DRDPS_AUR_PWR_TRG



      IF func_dr_pwr_api_is_pwr_point (NEW.entitykey)
      THEN
         # called dr_pwr_api_pkg.ispwrpoint
        set v_int = func_dr_pwr_api_get_interval (NEW.sourcetime);

   # dr_pwr_api_pkg.get_tariff_setpoint(:NEW.entitykey,v_tariff,v_setpoint);
# v_tariff := dr_pwr_api_pkg.get_tariff(:NEW.entitykey);
# v_setpoint := dr_pwr_api_pkg.get_setpoint(:NEW.entitykey);
         IF func_dr_pwr_api_is_pwr_point_exist (NEW.entitykey)
         THEN
           call prc_dr_pwr_api_get_tariff_setpoint (NEW.entitykey,
                                                v_tariff,
                                                v_setpoint
                                               );
             /* ( 'Power record with the entity key '
                                  || :NEW.entitykey
                                  || ' already exist'
                                 );
             */
            IF func_dr_pwr_api_is_pwr_point_same (NEW.entitykey,
                                                 NEW.sourcetime
                                                )
                                                
            then
              begin end;
               /* (   'Power recod with the entitykey '
                                     || :NEW.entitykey
                                     || ' and sourcetime  '
                                     || :NEW.sourcetime
                                     || ' already exist.'
                                    );
               */
            ELSE
              call prc_dr_pwr_api_upd_pwr_point (NEW.entitykey,
                                             NEW.sourcetime,
                                             NEW.VALUE,
                                             v_demand
                                            );
              call prc_dr_pwr_api_get_interval_diff (OLD.sourcetime,
                                                 NEW.sourcetime,
                                                 v_old,
                                                 v_new,
                                                 v_counter
                                                );

               
                              /*  (   'after get_interval_diff, before if :::::'
                                 || TO_CHAR (v_counter - 1)
                                );
                              */

               IF v_counter > 0
               THEN
                  /* (   'begin time diff  :: '
                                        || TO_CHAR (:OLD.sourcetime,
                                                    'MM/DD/YYYY HH24:MI:SS'
                                                   )
                                        || ',   '
                                        || TO_CHAR (:NEW.sourcetime,
                                                    'MM/DD/YYYY HH24:MI:SS'
                                                   )
                                       );
                  */
                  
                  set v_diff = timestampdiff(second,OLD.sourcetime,NEW.sourcetime);
                  # end time diff: 
                  set v_demandpersecond = v_demand / v_diff;
                  /*   'begin convert '
                                        || v_diff
                                        || '  :  '
                                        || v_demandpersecond
                  */
                  set v_head =
                       v_old * 1800
                     - HOUR(OLD.sourcetime) * 60 * 60
                     - MINUTE(OLD.sourcetime) * 60
                     - SECOND(OLD.sourcetime)
                     - 1;
                  set v_end =
                       HOUR (NEW.sourcetime) * 60 * 60
                     + MINUTE (NEW.sourcetime) * 60
                     + SECOND (NEW.sourcetime)
                     - (v_new - 1) * 1800
                     + 1;
                  /* (   'here:  v_head: '
                                        || v_head
                                        || ' and v_end: '
                                        || v_end
                                       );
                  */
                  # convert done
                  set v_head_demand = v_demandpersecond * v_head;
                  set v_end_demand = v_demandpersecond * v_end;
                  set v_loop = 1;

                  WHILE v_loop < v_counter DO
                  
                    set v_time =
                              date(OLD.sourcetime)
                            + (v_old + v_loop - 1) / 48;
                    set my_demand = v_demandpersecond * 1800;
                    set v_newint = v_old + v_loop;

                     IF (v_newint >= 49)
                     THEN
                       set v_newint = MOD (v_newint, 49) + 1;
                     END IF;

                    call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                       v_time,
                                                       v_newint,
                                                       v_tariff,
                                                       v_setpoint,
                                                       v_setpointname,
                                                       my_demand
                                                      );
                     set v_loop = v_loop + 1;
                  END WHILE;

                  #after while loop
                  set v_time = date(NEW.sourcetime) + (v_new - 1) / 48;
                  call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                    v_time,
                                                    v_new,
                                                    v_tariff,
                                                    v_setpoint,
                                                    v_setpointname,
                                                    v_end_demand
                                                   );
                  set v_time = date(OLD.sourcetime) + (v_old - 1) / 48;
                  call dr_pwr_api_upd_30min_pwr_point (NEW.entitykey,
                                                      v_time,
                                                      v_old,
                                                      v_head_demand
                                                     );



               ELSEIF (func_dr_pwr_api_is_30min_pwr_point_exist
                                                             (NEW.entitykey,
                                                              NEW.sourcetime,
                                                              v_int
                                                             )
                     )
               THEN
                  # in trigger, insert 30min talbe
                  call prc_dr_pwr_api_upd_30min_pwr_point (NEW.entitykey,
                                                      NEW.sourcetime,
                                                      v_int,
                                                      v_demand
                                                     );
               ELSE
                  call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                                    NEW.sourcetime,
                                                    v_int,
                                                    v_tariff,
                                                    v_setpoint,
                                                    v_setpointname,
                                                    0
                                                   );
               END IF;
            END IF;
         ELSE
         /*
            EXECUTE IMMEDIATE 'INSERT INTO dr_pwrdmd_data values(:b1,:b2,:b3)'
                        USING :NEW.entitykey, :NEW.sourcetime, :NEW.VALUE;
         */
        insert into dr_pwrdmd_data values (new.entitykey,new.sourcetime,new.value);

          call prc_dr_pwr_api_get_tariff_setpoint (NEW.entitykey,
                                                v_tariff,
                                                v_setpoint
                                               );
            # 'done my set point'
            #'Inserting new record into pwr_dmd_30min_table'
          call prc_dr_pwr_api_ins_new_30min_rec (NEW.entitykey,
                                              NEW.sourcetime,
                                              v_int,
                                              v_tariff,
                                              v_setpoint,
                                              v_setpointname,
                                              0
                                             );
         END IF;
#           EXECUTE IMMEDIATE 'insert into pwr_dmd_log values (:b1,
# :b2,
# :b3,
# :b4,
# :b5,
# :b6,
# :b7,
# :b8,
# :b9,
# :b10,
# :b11,
# :b12,
# :b13,
# :b14,
# :b15,
# :b16,
# :b17,
# :b18,
# :b19,
# :b20,
# :b21,
# :b22,
# :b23,
# :b24
# )'
#                            USING :OLD.sourcetime,
#                                  :NEW.sourcetime,
#                                  :NEW.entitykey,
#                                  :NEW.VALUE,
#                                  v_quality,
#                                  v_demand,
#                                  v_tariff,
#                                  v_setpoint,
#                                  v_setpointname,
#                                  v_int,
#                                  v_old,
#                                  v_new,
#                                  v_counter,
#                                  v_loop,
#                                  v_diff,
#                                  v_head,
#                                  v_end,
#                                  v_demandpersecond,
#                                  v_head_demand,
#                                  v_end_demand,
#                                  my_demand,
#                                  v_time,
#                                  v_newint,
# 								 :old.value;
   END IF;

# Start of the trigger handle_setpoint_tariff_au_trg
BEGIN
   DECLARE v_entityname    VARCHAR(85);
   DECLARE v_value         int(11);
   DECLARE v_tariff        int(11);
   DECLARE v_setpoint      int(11);
   DECLARE v_what          varchar(20);
   DECLARE v_len           int(11);
   DECLARE v_location      varchar(20);
   DECLARE v_locationkey   int(11);
   DECLARE v_num           int(11);

   SELECT name
     INTO v_entityname
     FROM entity
    WHERE pkey = NEW.entitykey;

   # dbms_output.put_line('in trigger: handle_setpoint_tariff_trg, the entityname is: ' || v_entityname);
   IF v_entityname LIKE '%SYS.PWR.DMD.diiSYS-PwrDmdTariffOffOnPeak'
   THEN
      SET v_what = 'tariff';
      SET v_len = instr(binary v_entityname, '.');
      SET v_location = substr(v_entityname, 1, v_len - 1);

      SELECT pkey
        INTO v_locationkey
        FROM location
       WHERE upper(name) = upper(v_location);

      SELECT count(*)
        INTO v_num
        FROM dr_pwrdmd_config
       WHERE locationkey = v_locationkey;

      IF v_num = 1
      THEN
         UPDATE dr_pwrdmd_config
            SET tariff = new.value
          WHERE locationkey = v_locationkey;
      ELSE
         INSERT INTO dr_pwrdmd_config(locationkey, location, tariff)
         VALUES (v_locationkey, v_location, new.value);
      END IF;
   ELSEIF v_entityname LIKE '%SYS.PWR.DMDSP.miiSYS-PwrDmdSetPoint'
   THEN
      SET v_what = 'setpoint';
      SET v_len = instr(binary v_entityname, '.');
      SET v_location = substr(v_entityname, 1, v_len - 1);

      SELECT pkey
        INTO v_locationkey
        FROM location
       WHERE upper(name) = upper(v_location);

      SELECT count(*)
        INTO v_num
        FROM dr_pwrdmd_config
       WHERE locationkey = v_locationkey;

      IF v_num = 1
      THEN
         UPDATE dr_pwrdmd_config
            SET setpoint = new.value
          WHERE locationkey = v_locationkey;
      ELSE
         INSERT INTO dr_pwrdmd_config(locationkey, location, setpoint)
         VALUES (v_locationkey, v_location, new.value);
      END IF;
   ELSE
      SET v_what = 'none';
   END IF;
#dbms_output.put_line('done handle_tariff_setpoint_trg');
END;
# end of the trigger handle_setpoint_tariff_au_trg

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER drdps_adr_general_power_trg
   AFTER DELETE 
   ON dr_datapoint_state
   FOR EACH ROW
BEGIN
# Modified by Will Sept 2011
  # not_a_number        EXCEPTION;
  # PRAGMA EXCEPTION_INIT (not_a_number, -1722);
  /*
  DECLARE v_sourcetime        DATETIME;
  DECLARE v_entityname        VARCHAR (85);
  DECLARE v_value             INT(11);
  DECLARE v_quality           INT(11);
  DECLARE v_new_record        BOOLEAN;
  DECLARE v_demand            INT(11);
  DECLARE v_tariff            INT(2);
  DECLARE v_setpoint          DECIMAL(22, 0);
  DECLARE v_setpointname      VARCHAR (85);
  DECLARE v_int               INT(5);
  DECLARE v_old               INT(11);
  DECLARE v_new               INT(11);
  DECLARE v_counter           INT(11);
  DECLARE v_loop              INT(11);
  DECLARE v_diff              BIGINT(22);
  DECLARE v_head              BIGINT(22);
  DECLARE v_end               BIGINT(22);
  DECLARE v_demandpersecond   decimal(38,30);
  DECLARE v_head_demand       decimal(38,30);
  DECLARE v_end_demand        decimal(38,30);
  DECLARE my_demand           decimal(38,30);
  DECLARE v_time              DATETIME;
  DECLARE v_newint            INT(11);
  */
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';
DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';



  # Start Trigger DRDPS_ADR_PWR_TRG

IF func_dr_pwr_api_is_pwr_point (OLD.entitykey)
      THEN
         # Find out whether a record is already being entered with the same entitykey--
         IF func_dr_pwr_api_is_pwr_point_exist (OLD.entitykey)
         THEN
            /* (   'Power record with the entity key '
                                  || :OLD.entitykey
                                  || ' already exist'
                                 );
            */                                 

           
            DELETE FROM dr_pwrdmd_data where entitykey = OLD.entitykey;
            
            DELETE FROM pwr_dmd_30min_table where entitykey = OLD.entitykey;

         END IF;
      END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER drlp_bir_trg
   BEFORE INSERT
   ON dr_live_property
   FOR EACH ROW
BEGIN
   DECLARE v_table   VARCHAR(30);

   IF NEW.DRLP_TABLE <> ''
   THEN
      # check if drlp_table already exists:

      SELECT table_name
        INTO v_table
        FROM information_schema.tables
       WHERE table_name = NEW.drlp_table;

      IF v_table <> ''
      THEN                           # table already exists, fail the trigger.
          SELECT concat('Cannot enter this record, because specified table ',
                       NEW.drlp_table,
                       ' already exists. Drop existing table first.') into @err_message;
          select 1 into @1 from Err_TheSpecifiedTableAlreadyExists;            
                       
      # RAISE_APPLICATION_ERROR(-20021,'Cannot enter this record, because specified table '||:NEW.drlp_table||' already exists. Drop existing table first.');
      ELSE
         SET NEW.drlp_status = 'PENDING';
      # set new drlp_status to 'PENDING'
      END IF;
   END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `drlp_air_trg`
   AFTER INSERT
   ON dr_live_property
   FOR EACH ROW
BEGIN
   IF NEW.drlp_table <> ''
   THEN
      IF 1 <= NEW.min_summary_interval AND NEW.min_summary_interval < 300
      THEN
         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('REALTIME',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 'REAL',
                 0,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 '',
                 '1',
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1MIN',
                 60,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT1MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '2MIN',
                 120,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT2MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '3MIN',
                 180,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT3MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '4MIN',
                 240,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT4MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '5MIN',
                 300,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT5MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'TABLE',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '5MIN',
                 300,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_VIEW'),
                 NULL,
                 'INT5MIN',
                 'SUM(icount)',
                 'IF(SUM(icount) = 0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '6MIN',
                 360,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT6MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '12MIN',
                 720,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT12MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '10MIN',
                 600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT10MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '15MIN',
                 900,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT15MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '20MIN',
                 1200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT20MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT30MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'TABLE',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_VIEW'),
                 NULL,
                 'INT30MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '40MIN',
                 2400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT40MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '45MIN',
                 2700,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '5MIN_TABLE'),
                 NULL,
                 'INT45MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1HRS',
                 3600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '2HRS',
                 7200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT2HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '3HRS',
                 10800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT3HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '4HRS',
                 14400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT4HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '6HRS',
                 21600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT6HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '8HRS',
                 28800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT8HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '12HRS',
                 43200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT12HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1DAY',
                 86400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1DAY',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');
      END IF;

      IF 300 <= NEW.min_summary_interval AND NEW.min_summary_interval < 1800
      THEN
         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('REALTIME',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '',
                 0,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 '',
                 '1',
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '5MIN',
                 300,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT5MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '10MIN',
                 600,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT10MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '15MIN',
                 900,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT15MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '20MIN',
                 1200,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT20MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT30MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'TABLE',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_VIEW'),
                 NULL,
                 'INT30MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1HRS',
                 3600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '2HRS',
                 7200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT2HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '3HRS',
                 10800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT3HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '4HRS',
                 14400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT4HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '6HRS',
                 21600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT6HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '8HRS',
                 28800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT8HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '12HRS',
                 43200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT12HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1DAY',
                 86400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1DAY',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');
      END IF;

      IF NEW.min_summary_interval >= 1800
      THEN
         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('REALTIME',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '',
                 0,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 '',
                 '1',
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 NEW.drlp_column,
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('BASE',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 NEW.drlp_table,
                 NEW.drlp_column,
                 'INT30MIN',
                 CONCAT('COUNT(', NEW.drlp_column, ')'),
                 CONCAT('AVG(', NEW.drlp_column, ')'),
                 CONCAT('MIN(', NEW.drlp_column, ')'),
                 CONCAT('MAX(', NEW.drlp_column, ')'),
                 CONCAT('SUM(', NEW.drlp_column, ')'),
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'TABLE',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '30MIN',
                 1800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_VIEW'),
                 NULL,
                 'INT30MIN',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1HRS',
                 3600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '2HRS',
                 7200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT2HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '3HRS',
                 10800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT3HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '4HRS',
                 14400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT4HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '6HRS',
                 21600,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT6HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '8HRS',
                 28800,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT8HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '12HRS',
                 43200,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT12HRS',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'VIEW',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1DAY',
                 86400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '30MIN_TABLE'),
                 NULL,
                 'INT1DAY',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');

         INSERT INTO dr_trend_config(dr_type1,
                                     dr_type2,
                                     property_category,
                                     property_name,
                                     property_identifier,
                                     `interval`,
                                     interval_seconds,
                                     source_name,
                                     source_column,
                                     interval_column,
                                     icount_column,
                                     iavg_column,
                                     imin_column,
                                     imax_column,
                                     isum_column,
                                     object_name)
         VALUES ('SUMMARY',
                 'TABLE',
                 NEW.drlp_category,
                 NEW.drlp_name,
                 NEW.drlp_identifier,
                 '1DAY',
                 86400,
                 CONCAT('DR_',
                        NEW.drlp_identifier,
                        '_',
                        '1DAY_VIEW'),
                 NULL,
                 'INT1DAY',
                 'SUM(icount)',
                 'IF(SUM(icount)=0,0,SUM(isum)/SUM(icount))',
                 'MIN(imin)',
                 'MAX(imax)',
                 'SUM(isum)',
                 '-1');
      END IF;
   END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `dr_mmsinhibit_summary_view`
--


--
-- Temporary table structure for view `dr_plcfailure_status_view`
--



--
-- Temporary table structure for view `dr_plcstatus_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_1day_view`
--




--
-- Temporary table structure for view `dr_pwrdmd_30min_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_30min_view1`
--





--
-- Temporary table structure for view `dr_pwrdmd_data_v`
--



--
-- Temporary table structure for view `dr_pwrdmd_day_sum_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_daymax_02_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_daymax_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_daysum_view`
--



--
-- Temporary table structure for view `dr_pwrdmd_hoursum_view`
--


--
-- Temporary table structure for view `dr_pwrdmd_monthsum_view`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_off_dt2_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_off_dt3_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_off_maxdemand_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_on_dt2_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_on_dt3_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_on_maxdemand_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_overall_summary_v`
--


--
-- Temporary table structure for view `dr_pwrdmd_weeksum_view`
--


--
-- Temporary table structure for view `dr_pwrdmd_yearmax_tiff0_view`
--

--
-- Temporary table structure for view `dr_pwrdmd_yearmax_tiff1_view`
--


--
-- Temporary table structure for view `dr_pwrdmd_yearmax_view`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER drtc_bir_trg
   BEFORE INSERT
   ON dr_trend_config
   FOR EACH ROW
BEGIN
   DECLARE v_nextnumber          int(11);
   DECLARE v_objectname          VARCHAR(30);
   DECLARE v_objectdescription   VARCHAR(100);
   DECLARE v_objectselect1       VARCHAR(2000);
   DECLARE v_objectselect2       VARCHAR(2000) DEFAULT 'begin null; end;';
   DECLARE v_objectjob           VARCHAR(2000);

   SELECT func_seq_get_next_number('dr_seq') INTO v_nextnumber FROM dual;

   SET v_objectname =
          lower(concat('DR_',
                 NEW.property_identifier,
                 '_',
                 NEW.interval,
                 '_',
                 NEW.dr_type2));
   SET v_objectdescription =
          concat(NEW.property_category,
                 ' ',
                 NEW.property_name,
                 ' ',
                 NEW.interval,
                 ' ',
                 NEW.dr_type2);

   IF concat(NEW.dr_type1, NEW.dr_type2) = 'REALTIMEVIEW'
   THEN
      SET v_objectjob =
             concat('BEGIN Dr_Api_Pkg.Populate_Base_With_Snapshot(''',
                    v_objectname,
                    '''); COMMIT; END;');
      SET v_objectselect1 =
             concat(
                'CREATE OR REPLACE VIEW ',
                v_objectname,
                '(sourcedate,startsecond,endsecond,startdatetime,enddatetime,entitykey,iavg) ');
      SET v_objectselect1 =
             concat(
                v_objectselect1,
                ' AS SELECT sourcedate, timeofday AS startsecond, timeofday AS endsecond, sourcetime AS startdatetime, sourcetime AS enddatetime, entitykey, ',
                NEW.iavg_column,
                ' AS iavg FROM (SELECT sourcedate,timeofday,entitykey,sourcetime,',
                NEW.source_column,
                ' FROM ',
                lower(NEW.source_name),
                ') ');
      SET v_objectselect2 =
             concat(
                'CREATE OR REPLACE TRIGGER ',
                v_objectname,
                '_iir_trg INSTEAD OF INSERT ON ',
                v_objectname,
                ' FOR EACH ROW
DECLARE
BEGIN
IF NOT func_dr_api_check_base_record(''',
                lower(NEW.source_name),
                ''',NEW.sourcedate,NEW.startsecond,NEW.entitykey) THEN
INSERT INTO ',
                lower(NEW.source_name),
                '(sourcedate,timeofday,entitykey,sourcetime,',
                NEW.source_column,
                ')
VALUES (NEW.sourcedate,NEW.startsecond,NEW.entitykey,NEW.startdatetime,NEW.iavg);
ELSE
UPDATE ',
                lower(NEW.source_name),
                ' SET ',
                NEW.source_column,
                ' = NEW.iavg
WHERE sourcedate = NEW.sourcedate AND timeofday = NEW.startsecond AND entitykey = NEW.entitykey;
END IF;
END;
');
   END IF;

   # New definition of Base View, returns nulls if value in base table not found. Only looks up entities that are currently enabled for trending. (as per modified design, applicable to 1TS-4669-F)
   IF concat(NEW.dr_type1, NEW.dr_type2) = 'BASEVIEW'
   THEN
      SET v_objectselect1 =
             concat(
                'CREATE OR REPLACE VIEW ',
                v_objectname,
                '(sourcedate,startsecond,endsecond,startdatetime,enddatetime,entitykey,iavg) ');
      SET v_objectselect1 =
             concat(
                v_objectselect1,
                ' AS SELECT t2.sourcedate, t1.startsecond, t1.endsecond, (t2.sourcedate + t1.startsecond / 86400), (t2.sourcedate + t1.endsecond / 86400), t1.entitykey, ',
                '(SELECT max(',
                NEW.source_column,
                ') KEEP(DENSE_RANK LAST ORDER BY timeofday) FROM ',
                lower(NEW.source_name),
                ' WHERE sourcedate = t2.sourcedate AND timeofday BETWEEN t1.startsecond AND t1.endsecond AND entitykey = t1.entitykey) AS iavg ',
                'FROM (SELECT startsecond, ',
                NEW.interval_column,
                ' AS endsecond,entitykey FROM dr_trend_interval,entityparametervalue_v WHERE ',
                NEW.interval_column,
                ' >0 ',
                'AND typename LIKE ''',
                NEW.property_category,
                ''' AND parametername = ''EnableTrending'' AND value=''1'') t1, DR_DATAPOINT_DATE t2 ');
   END IF;


   /*--Old definition of Base View-- (as per initial KPE desin, applicable to 1TS-4619-F)
   IF :NEW.dr_type1 || :NEW.dr_type2 = 'BASEVIEW' THEN
   v_objectselect1 := 'CREATE OR REPLACE VIEW '||v_objectname||'(sourcedate,startsecond,endsecond,startdatetime,enddatetime,entitykey,icount,iavg,imin,imax,isum) ';
   v_objectselect1 := v_objectselect1 || ' AS SELECT sourcedate, startsecond, endsecond, (sourcedate + startsecond / 86400), (sourcedate + endsecond / 86400), entitykey, '||
   :NEW.icount_column ||' AS icount, '||
   :NEW.iavg_column ||' AS iavg, '||
   :NEW.imin_column ||' AS imin, '||
   :NEW.imax_column ||' AS imax, '||
   :NEW.isum_column ||' AS isum FROM (SELECT startsecond, INT' ||:NEW.interval||
   ' AS endsecond FROM DR_TREND_INTERVAL WHERE INT' ||:NEW.interval||
   ' >0), (SELECT sourcedate,timeofday,entitykey,'||:NEW.source_column||
   ' FROM '||:NEW.source_name||') WHERE timeofday BETWEEN startsecond AND endsecond GROUP BY sourcedate,startsecond,endsecond,entitykey ';
   END IF;
   */

   IF concat(NEW.dr_type1, NEW.dr_type2) = 'SUMMARYVIEW'
   THEN
      SET v_objectselect1 =
             concat(
                'CREATE OR REPLACE VIEW ',
                v_objectname,
                '(sourcedate,startsecond,endsecond,startdatetime,enddatetime,entitykey,iavg) ');
      SET v_objectselect1 =
             concat(
                v_objectselect1,
                ' AS SELECT sourcedate, startsecond, endsecond, (sourcedate + startsecond / 86400), (sourcedate + endsecond / 86400), entitykey, ',
                NEW.iavg_column,
                ' AS iavg FROM (SELECT startsecond, INT',
                NEW.interval,
                ' AS endsecond FROM dr_trend_interval WHERE INT',
                NEW.interval,
                ' >0), (SELECT sourcedate,timeofday,entitykey,iavg ',
                ' FROM ',
                lower(NEW.source_name),
                ') WHERE timeofday BETWEEN startsecond AND endsecond GROUP BY sourcedate,startsecond,endsecond,entitykey');
   END IF;

   IF concat(NEW.dr_type1, NEW.dr_type2) = 'SUMMARYTABLE'
   THEN
      SET v_objectjob =
             concat('BEGIN Dr_Api_Pkg.populate_summary_table(''',
                    v_objectname,
                    '''); COMMIT; END;');
      SET v_objectselect1 =
             concat(
                'CREATE TABLE ',
                v_objectname,
                '(sourcedate,timeofday,entitykey,iavg, PRIMARY KEY (sourcedate,timeofday,entitykey) USING INDEX TABLESPACE hist_indx) TABLESPACE HIST_DAT ');
      SET v_objectselect1 =
             concat(
                v_objectselect1,
                ' AS (SELECT sourcedate, timeofday, entitykey, ',
                NEW.iavg_column,
                ' AS iavg FROM (SELECT startsecond, INT',
                NEW.interval,
                ' AS endsecond FROM dr_trend_interval WHERE INT',
                NEW.interval,
                ' >0), (SELECT sourcedate,startsecond AS timeofday,entitykey,iavg ',
                ' FROM ',
                lower(NEW.source_name),
                ') WHERE sourcedate = TRUNC(SYSDATE-1) AND timeofday BETWEEN startsecond AND endsecond GROUP BY sourcedate,timeofday,entitykey) ');
   END IF;

   IF concat(NEW.dr_type1, NEW.dr_type2) = 'BASEDERIV'
   THEN
      SET v_objectjob =
             concat('BEGIN Dr_Api_Pkg.populate_derived_table(''',
                    v_objectname,
                    '''); COMMIT; END;');
      SET v_objectselect1 =
             concat(
                'CREATE TABLE ',
                v_objectname,
                '(sourcedate DATE,timeofday NUMBER,entitykey NUMBER(9),sourcetime DATE,iavg NUMBER, PRIMARY KEY (sourcedate,timeofday,entitykey) USING INDEX TABLESPACE hist_indx) TABLESPACE HIST_BASE ');
   END IF;

   SET NEW.dr_id = v_nextnumber;
   SET NEW.object_name = v_objectname;
   SET NEW.object_description = v_objectdescription;
   SET NEW.object_select1 = v_objectselect1;
   SET NEW.object_select2 = v_objectselect2;
   SET NEW.object_job = v_objectjob;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecmmod_bir_trg` BEFORE INSERT
    ON ec_master_mode FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecmmod_bur_trg` BEFORE UPDATE
    ON ec_master_mode FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecmmhe_bif_trg` BEFORE INSERT
    ON ec_master_mode_helper FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecmmhe_buf_trg` BEFORE UPDATE
    ON ec_master_mode_helper FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecscol_bir_trg` BEFORE INSERT
    ON ec_station_colour FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecscol_bur_trg` BEFORE UPDATE
    ON ec_station_colour FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecsmod_bif_trg` BEFORE INSERT
    ON ec_station_mode FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ecsmod_buf_trg` BEFORE UPDATE
    ON ec_station_mode FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eczone_bif_trg` BEFORE INSERT
    ON ec_zone FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eczone_buf_trg` BEFORE UPDATE
    ON ec_zone FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entity_bif_row_audit` BEFORE INSERT
    ON entity FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
  SET NEW.SEREGI_ID = NEW.LOCATIONKEY;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entity_buf_row_audit` BEFORE UPDATE
    ON entity FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
  SET NEW.SEREGI_ID = NEW.LOCATIONKEY ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cascade_del_entity` BEFORE DELETE
    ON entity FOR EACH ROW
BEGIN
    DELETE from entityparametervalue  WHERE EntityKey = OLD.PKey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;



--
-- Temporary table structure for view `entity_v`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `enparam_bif_row_audit` BEFORE INSERT
    ON entityparameter FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `enparam_buf_row_audit` BEFORE UPDATE
    ON entityparameter FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `cascade_del_entparam` BEFORE DELETE
    ON entityparameter FOR EACH ROW
BEGIN
    DELETE from entityparametervalue WHERE ParameterKey = OLD.PKey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `entityparameter_v`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `epv_bif_row_audit` BEFORE INSERT
    ON entityparametervalue FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `epv_buf_row_audit` BEFORE UPDATE
    ON entityparametervalue FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `entityparametervalue_v`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entitystatusdata_bif_row_audit` BEFORE INSERT
    ON entitystatusdata FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entitystatusdata_buf_row_audit` BEFORE UPDATE
    ON entitystatusdata FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `etype_bir_audit_trg` BEFORE INSERT
    ON entitytype FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `etype_bur_audit_trg` BEFORE UPDATE
    ON entitytype FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER cascade_del_enttype
 BEFORE DELETE ON entitytype FOR EACH ROW
BEGIN
    DELETE from entity WHERE TypeKey = OLD.PKey;
    DELETE from entityparameter  WHERE TypeKey = OLD.PKey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `entitytype_v`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entypepar_bif_row_audit` BEFORE INSERT
    ON entitytypeparent FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `entypepar_buf_row_audit` BEFORE UPDATE
    ON entitytypeparent FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `evcom_event_trg` BEFORE INSERT ON ev_combined FOR EACH ROW
BEGIN

DECLARE  p_subsystem_key          INT(9);
DECLARE  p_physical_subsystem_key INT(9);
DECLARE  p_location_key           INT(9);
DECLARE  p_event_type_name        VARCHAR(256);
DECLARE  p_event_view_level       INT(1);
DECLARE  p_operator_key           INT(9);
DECLARE  p_operator_name          VARCHAR(85);
DECLARE  p_severity_name          VARCHAR(20);
DECLARE  p_severity_key           INT(9);
DECLARE  p_alarm_comment          VARCHAR(2000);
DECLARE  v_normalised             VARCHAR(20) DEFAULT ' - Normalised';
DECLARE  v_acknowledged           VARCHAR(20) DEFAULT ' - Acknowledged';
DECLARE  v_omflag_param_list      VARCHAR(2000) DEFAULT NULL;
DECLARE  v_dp_param_list          VARCHAR(2000) DEFAULT NULL;
DECLARE  v_dp_ev_param_list       VARCHAR(2000) DEFAULT NULL;
DECLARE  p_entity_location_key    INT(9) DEFAULT 0;
DECLARE  p_session_LOCATION       INT(9) DEFAULT NULL;
DECLARE  p_profile_id             INT(9) DEFAULT -1;
DECLARE  is_system                INT(9);
DECLARE  p_action_id              INT(9);
DECLARE  p_pkey                   INT(9);


DECLARE cu_entity CURSOR FOR 
    SELECT subsystemkey           AS SUBSYSTEM_KEY,
           physical_subsystem_key AS PHYSICAL_SUBSYSTEM_KEY,
           locationkey            AS LOCATION_KEY
      FROM entity
     WHERE pkey = NEW.entity_key;

DECLARE cu_event CURSOR FOR
    SELECT type_name AS EVENT_TYPE_NAME,
           view_level AS EVENT_VIEW_LEVEL,
           (SELECT operatorkey FROM ta_session WHERE pkey = NEW.session_key) AS OPERATOR_KEY,
           (SELECT name FROM operator
            WHERE is_system <> 1
            	and pkey = (SELECT operatorkey FROM ta_session
                          WHERE pkey = NEW.session_key)) AS OPERATOR_NAME,
			(select ifnull((SELECT pkey from location where name = 'OCC'),0)) AS LOCATION_KEY
    FROM me_message_type
    WHERE memtyp_id = NEW.event_type_key ;

DECLARE  cu_session CURSOR FOR
    SELECT consolekey as session_location, SEPROF_ID as profile_id
    FROM ta_session WHERE pkey = NEW.session_key;

DECLARE  cu_alarm CURSOR FOR
    SELECT a.comments AS ALARM_COMMENT
    FROM alarm a
    WHERE a.alarm_id = NEW.alarm_id;

DECLARE  cu_sverity CURSOR FOR
    SELECT name AS SEVERITY_NAME
    FROM ALARMSEVERITY WHERE pkey = NEW.Severity_Key;
    
DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';
DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';
	
 # Fired if it's a alarm message.
 # add and :NEW.entity_key <> '' for C830, If the alarm agent have been changed to latest one, the entity_key will be NULL  
  
  IF new.alarm_id <> '' and new.source_table = '100' and NEW.entity_key <> '' THEN
  
    OPEN cu_entity;
    FETCH cu_entity INTO p_subsystem_key, p_physical_subsystem_key, p_entity_location_key;
    CLOSE cu_entity;
    BEGIN
      OPEN cu_event;
      FETCH cu_event
        INTO p_event_type_name,
             p_event_view_level,
             p_operator_key,
             p_operator_name,
             p_location_key;
      CLOSE cu_event;
      OPEN cu_alarm;
      FETCH cu_alarm INTO p_alarm_comment;
      CLOSE cu_alarm;
      OPEN cu_sverity;
      FETCH cu_sverity INTO p_severity_name;
      CLOSE cu_sverity;    
    END;

    BEGIN
      # dbms_output.enable(10000);
      IF NEW.session_key IS NULL or NEW.session_key = '' OR
         NEW.session_key = 'InternalProcessing' OR
         TRIM(NEW.session_key) = '' THEN
			SET p_profile_id = -1;
      # dbms_output.put_line('sessionkey is null here');  
      ELSE
      # dbms_output.put_line('sessionkey is ::' || :new.session_key);  
        OPEN cu_session;
        FETCH cu_session INTO p_session_location, p_profile_id;
        CLOSE cu_session;

        SELECT is_system INTO is_system  FROM se_profile s
        WHERE s.seprof_id = p_profile_id;

        if is_system = 1 then
          SET p_profile_id = -1;
        end if; 
        /*
               if  p_physical_subsystem_key <> '' then
                p_profile_id := -1;
               end if;
        */
      END IF;    
    END;

    select SEACTI_ID into p_action_id
    from se_action
    where MEMTYP_ID = CAST(NEW.event_type_key AS UNSIGNED);
 
    # ++ CF : TD13673
    IF (p_entity_location_key != 0) THEN
      SET p_location_key = p_entity_location_key;
    ELSEIF (NEW.location_key != 0) THEN
      SET p_location_key = NEW.location_key;
    END IF;  
    # ++ CF : TD13673
    
    # TD19052

    if p_physical_subsystem_key <> '' then
      SET p_subsystem_key = p_physical_subsystem_key;
    end if;

    # :new.source_table := '100';
    SELECT func_seq_get_next_number('EV_COMBINED_SEQ') INTO  p_pkey;
	  SET NEW.PKEY                   = CAST(p_pkey AS UNSIGNED);
    SET NEW.createdatetime         = str_to_date(NEW.createtime,'%Y-%m-%d %H:%i:%s');
    SET NEW.subsystem_key          = p_subsystem_key;
    SET NEW.physical_subsystem_key = ifnull(p_physical_subsystem_key, -1);
    SET NEW.location_key           = p_location_key;
    SET NEW.severity_name          = p_severity_name;
    SET NEW.event_type_key         = CAST(NEW.event_type_key as unsigned);
    SET NEW.event_type_name        = p_event_type_name;
    SET NEW.operator_key           = p_operator_key;
    SET NEW.operator_name          = p_operator_name;
    SET NEW.alarm_comment          = p_alarm_comment;
    SET NEW.event_level            = p_event_view_level;
    SET NEW.session_location       = p_session_location;
    SET NEW.profile_id             = p_profile_id;
    SET NEW.action_id              = p_action_id;

  END IF; 

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `evcom_printevent_trg` AFTER INSERT ON ev_combined FOR EACH ROW
BEGIN
 DECLARE  v_pkey        INT(9);
 DECLARE  v_printmessage  INT(9) DEFAULT 0;
 DECLARE  occ_locationkey INT(9);
 DECLARE  v_printer       varchar(50)DEFAULT NULL;
 DECLARE  v_occ_printer   varchar(50)DEFAULT NULL;
 DECLARE  v_eventtype     varchar(30);
 DECLARE  v_dssstate      varchar(30);
 DECLARE  v_mmsstate     varchar(30);
 DECLARE  v_avlstate     varchar(30);

  DECLARE  no_data_found   boolean DEFAULT FALSE;
 DECLARE  CONTINUE HANDLER FOR NOT FOUND SET no_data_found = TRUE;
  # optimize the trigger performance
    BEGIN
        SELECT print_message INTO v_printmessage FROM me_message_type WHERE memtyp_id = NEW.event_type_key;
        IF no_data_found THEN
          SET v_printmessage = 0;
        END IF;
    END;

    IF (v_printmessage = 1) THEN
            # get printer name
# ++ AZ : TD14242
    SET no_data_found = FALSE;
        BEGIN
            IF (NEW.PHYSICAL_SUBSYSTEM_KEY <> '') THEN
                SELECT printer INTO v_printer FROM online_printer
                WHERE LOCATIONKEY = NEW.LOCATION_KEY AND IS_ALARM = 0 AND SUBSYSTEMKEY = NEW.PHYSICAL_SUBSYSTEM_KEY;
            END IF;

            IF ((v_printer IS NULL or v_printer = '') AND NEW.SUBSYSTEM_KEY <> '') THEN
                SELECT printer INTO v_printer FROM online_printer
                WHERE LOCATIONKEY = NEW.LOCATION_KEY AND IS_ALARM = 0 AND SUBSYSTEMKEY = NEW.SUBSYSTEM_KEY;
            END IF;

            IF (v_printer IS NULL or v_printer = '') THEN
                SELECT def_printer INTO v_printer FROM online_printcfg
                WHERE LOCATIONKEY = NEW.LOCATION_KEY;
            END IF;
         IF no_data_found THEN
            SELECT def_printer INTO v_printer FROM online_printcfg
            WHERE LOCATIONKEY = NEW.LOCATION_KEY;
         END IF;
        END;
# AZ ++ : TD14242

        # get event type
        SELECT (
           CASE NEW.event_type_key
            WHEN 30022 THEN  'ALM'
            WHEN 30023 THEN  'SUP'
            WHEN 30013 THEN  'ACK'
            WHEN 30016 THEN  'CLS'
            ELSE  ' '
           END)
         INTO v_eventtype;

        #get DSS state
        SELECT (
           CASE NEW.DSS_STATE
            WHEN 'NoAssociatedPlan' THEN ' '
            WHEN 'AutoPlansNotRun' THEN 'A'
            WHEN 'SemiAutoPlansNotRun' THEN 'S'
            WHEN 'PlansRun' THEN 'R'
            WHEN 'PlanPostponed' THEN 'X'
            ELSE ' '
           END)
        INTO v_dssstate;

# ++ CF : TD14536
        # get MMS state
        SELECT (
         CASE NEW.MMS_STATE
            WHEN '0' THEN ' '
            WHEN '1' THEN 'S'
            WHEN '2' THEN 'A'
            WHEN '3' THEN 'R'
            WHEN '4' THEN ' '
            WHEN '5' THEN 'I'
            WHEN '6' THEN 'D'
            ELSE ' '
         END)
        INTO v_mmsstate;


        # get AVL state
        SELECT (
         CASE NEW.AVL_STATE
            WHEN '0' THEN ' '
            WHEN '1' THEN 'H'
            WHEN '2' THEN 'F'
            ELSE ' '
         END)
        INTO v_avlstate;

# CF ++ : TD14536

        # all nonOCC event or alarm must send to OCC
        SELECT pkey INTO occ_locationkey FROM location WHERE name='OCC';
      SET no_data_found = FALSE;
        IF (NEW.LOCATION_KEY != occ_locationkey) THEN
# ++ AZ : TD14242
            BEGIN
                IF (NEW.PHYSICAL_SUBSYSTEM_KEY <> '') THEN
                    SELECT printer INTO v_occ_printer FROM online_printer
                    WHERE LOCATIONKEY = occ_locationkey AND IS_ALARM = 0 AND SUBSYSTEMKEY = NEW.PHYSICAL_SUBSYSTEM_KEY;
                END IF;

                IF ((v_occ_printer IS NULL or v_occ_printer = '') AND NEW.SUBSYSTEM_KEY <> '') THEN
                    SELECT printer INTO v_occ_printer FROM online_printer
                    WHERE LOCATIONKEY = occ_locationkey AND IS_ALARM = 0 AND SUBSYSTEMKEY = NEW.SUBSYSTEM_KEY;
                END IF;

                IF (v_occ_printer IS NULL or v_occ_printer = '') THEN
                    SELECT def_printer INTO v_occ_printer FROM online_printcfg
                    WHERE LOCATIONKEY = occ_locationkey;
                END IF;
              IF no_data_found THEN
                SELECT def_printer INTO v_occ_printer FROM online_printcfg
                WHERE LOCATIONKEY = occ_locationkey;
              END IF;
            END;
# AZ ++ : TD14242
        # TD17780 If Printer is none, then prevent insertion to printable_event table
        IF (v_occ_printer != 'None') THEN
       BEGIN
                SELECT func_seq_get_next_number('PRINTABLE_EVENT_SEQ') INTO v_pkey;
            INSERT INTO printable_event(pkey,alarm_id,event_id,printer,alarmflag,createtime,severity,
                    asset,description,`value`,mms,dss,avalanche,operatorname,alarm_comment,alm,location_key)
             VALUES(v_pkey,NEW.ALARM_ID,NEW.PKEY,v_occ_printer,/*++ CF : TD14755 */IF(v_eventtype = ' ','EVENT','ALARMEVENT'),
                    /*CF ++ : TD14755*/date_format(NEW.CREATETIME,'%d-%m-%y %H:%i:%s'),NEW.SEVERITY_NAME,NEW.ASSET_NAME,NEW.DESCRIPTION,NEW.VALUE,v_mmsstate,v_dssstate,
                    v_avlstate,NEW.OPERATOR_NAME,NEW.ALARM_COMMENT,v_eventtype,occ_locationkey);
       END;
        END IF;
     END IF;

#   TD17780 If Printer is none, then prevent insertion to printable_event table
  IF (v_printer != 'None') THEN
   BEGIN
     # all event/alarm should send to their owner
    SELECT func_seq_get_next_number('PRINTABLE_EVENT_SEQ') INTO v_pkey;
    INSERT INTO PRINTABLE_EVENT(pkey,alarm_id,event_id,printer,alarmflag,createtime,severity,
     asset,description,value,mms,dss,avalanche,operatorname,alarm_comment,alm,location_key)
    VALUES(v_pkey,NEW.ALARM_ID,NEW.PKEY,v_printer,/*++ CF : TD14755*/if(v_eventtype = ' ','EVENT','ALARMEVENT'),
           /*F ++ : TD14755*/date_format(NEW.CREATETIME,'%d-%m-%y %H:%:%s'),NEW.SEVERITY_NAME,NEW.ASSET_NAME,NEW.DESCRIPTION,NEW.VALUE,v_mmsstate,
           v_dssstate,v_avlstate,NEW.OPERATOR_NAME,NEW.ALARM_COMMENT,v_eventtype,NEW.LOCATION_KEY);
   END;
  END IF;

 END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `event_bir_trg` BEFORE INSERT ON event FOR EACH ROW
BEGIN
   DECLARE   v_pkey           INT(9);
   DECLARE   v_locationkey    INT(9);
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_locationkey = 0;
   SELECT func_seq_get_next_number('EV_COMBINED_SEQ') INTO v_pkey;
   SET new.pkey = v_pkey;
   IF (NEW.SESSIONKEY <> '') THEN
  BEGIN
   SELECT IFnull(locationkey,0) INTO v_locationkey FROM entity
   WHERE pkey = (SELECT consolekey FROM ta_session WHERE pkey = NEW.SESSIONKEY);
   SET NEW.locationkey = v_locationkey;
  END;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `event_evcom_air_trg` AFTER INSERT
    ON event FOR EACH ROW
BEGIN

   DECLARE p_subsystem_key int(9);
   DECLARE p_physical_subsystem_key INT(9);
   DECLARE p_location_key INT(9);
   DECLARE p_event_type_name VARCHAR(256);
   DECLARE p_event_view_level INT(1);
   DECLARE p_operator_key INT(9);
   DECLARE p_operator_name VARCHAR(85);
   DECLARE p_severity_key INT(9);
   DECLARE p_severity_name VARCHAR(20);
   DECLARE p_alarm_type_key INT;
   DECLARE p_alarm_type_name VARCHAR(256);
   DECLARE p_alarm_comment VARCHAR(2000);
   DECLARE p_alarm_mms_state VARCHAR(100);
   DECLARE p_alarm_dss_state VARCHAR(30);
   DECLARE p_alarm_avl_state VARCHAR(100);
   DECLARE p_alarm_param_list VARCHAR(2000);
   DECLARE p_alarm_value VARCHAR(2000);
   DECLARE p_alarm_desc VARCHAR(2000);
   DECLARE p_alarm_ack VARCHAR(38);
   DECLARE p_alarm_status VARCHAR(2);
   DECLARE v_normalised VARCHAR(20) DEFAULT ' - Normalised';
   DECLARE v_acknowledged VARCHAR(20) DEFAULT ' - Acknowledged';
   DECLARE v_omflag_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE v_dp_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE v_dp_ev_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE p_entity_location_key INT(9) DEFAULT 0;
   DECLARE p_session_LOCATION        INT(9) DEFAULT NULL;
   DECLARE p_profile_id        INT(9) DEFAULT -1;
   DECLARE is_system   INT(9);
   DECLARE p_action_id INT(9);
   DECLARE p_operation_mode VARCHAR(2);

   DECLARE  cu_entity CURSOR FOR
      SELECT
         subsystemkey AS SUBSYSTEM_KEY,
         physical_subsystem_key AS PHYSICAL_SUBSYSTEM_KEY,
         locationkey AS LOCATION_KEY
      FROM entity
      WHERE pkey = NEW.entitykey;

   DECLARE cu_event CURSOR FOR
      SELECT
         type_name AS EVENT_TYPE_NAME,
         view_level AS EVENT_VIEW_LEVEL,
         (SELECT operatorkey FROM ta_session WHERE pkey = NEW.sessionkey ) AS OPERATOR_KEY,
         (SELECT NAME FROM operator WHERE pkey = (SELECT operatorkey FROM ta_session WHERE pkey = NEW.sessionkey)) AS OPERATOR_NAME,
         (SELECT (ifnull((SELECT pkey FROM location WHERE NAME='OCC'),0))) AS LOCATION_KEY
      FROM me_message_type
      WHERE memtyp_id = NEW.eventtype;

   DECLARE cu_session CURSOR FOR
        SELECT
        consolekey AS session_location,
        SEPROF_ID  AS profile_id
        FROM ta_session
        WHERE pkey = NEW.sessionkey;

   DECLARE cu_alarm CURSOR FOR
      SELECT
         a.SEVERITY AS SEVERITY_KEY,
         (SELECT NAME FROM alarmseverity WHERE pkey = a.SEVERITY) AS SEVERITY_NAME,
         a.param_list AS ALARM_PLIST,
         t.meatyp_id AS ALARM_TYPE_KEY,
         ifnull(t.type_name,'') AS ALARM_TYPE_NAME,
         a.comments AS ALARM_COMMENT,
         a.mms_state_type AS ALARM_MMS_STATE,
         a.planstatus AS ALARM_DSS_STATE,
         a.avl_status AS ALARM_AVL_STATE,
         a.acknowledged_by AS ALARM_ACK,
         a.state AS ALARM_STATUS
      FROM alarm a, me_alarm_type t
      WHERE a.alarm_id = NEW.alarm_id AND meatyp_id = cast(a.TYPE AS UNSIGNED INT);

   DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';


   OPEN cu_entity;
        FETCH cu_entity INTO p_subsystem_key,p_physical_subsystem_key,p_entity_location_key;
   CLOSE cu_entity;
BEGIN
   DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
   DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';

   OPEN cu_event;
    FETCH cu_event INTO p_event_type_name,p_event_view_level,p_operator_key,p_operator_name,p_location_key;
   CLOSE cu_event;
   OPEN cu_alarm;
         FETCH cu_alarm INTO p_severity_key,p_severity_name,p_alarm_param_list,p_alarm_type_key,p_alarm_type_name,p_alarm_comment,p_alarm_mms_state,p_alarm_dss_state,p_alarm_avl_state,p_alarm_ack,p_alarm_status;
   CLOSE cu_alarm;
END;

BEGIN
   DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
   DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';
# dbms_output.enable(10000);
   IF NEW.sessionkey IS  NULL OR NEW.sessionkey = 'InternalProcessing'  or trim(NEW.sessionkey) = '' THEN
    set p_profile_id = -1;
#    dbms_output.put_line('sessionkey is null here');
   ELSE
#    dbms_output.put_line('sessionkey is ::' || :new.sessionkey);
       OPEN cu_session;
        FETCH cu_session INTO p_session_location,p_profile_id;
       CLOSE cu_session;

        SELECT is_system INTO is_system FROM se_profile s WHERE s.seprof_id = p_profile_id;

       IF is_system = 1 THEN
        SET p_profile_id = -1;
       END IF;
/*
       if  p_physical_subsystem_key <> '' then
        p_profile_id := -1;
       end if;
*/
    END IF;
END;

CALL prc_omflag_param_list(p_alarm_param_list, v_omflag_param_list);
# prepare for variable p_operation_mode
IF (v_omflag_param_list <> '') THEN
    IF (v_omflag_param_list = 'N') THEN
        SET p_operation_mode ='';
    ELSE
        SET p_operation_mode = v_omflag_param_list;
    END IF;
ELSE  # if There is no param string 'OMFlag' in param_list of alarm table
   SET p_operation_mode ='';
END IF;

SELECT SEACTI_ID
  INTO p_action_id
  FROM se_action
 WHERE MEMTYP_ID = cast(NEW.eventtype AS UNSIGNED INT);

CALL prc_dp_param_list(p_alarm_param_list, v_dp_param_list);
IF(NEW.eventtype = '30022') THEN                               #30022 => SUBMITTED
      IF(p_alarm_type_key IN('50008','50009','50010'))THEN         #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE
         set p_alarm_desc = NEW.description;
         set p_alarm_value = v_dp_param_list;
      ELSE
         set p_alarm_desc = NEW.description;
         set p_alarm_value = concat(p_alarm_type_name,' ',v_dp_param_list);
      END IF;
   ELSEIF(NEW.eventtype = '30013') THEN                             #30013 => ACKNOWLEDGED
      IF(p_alarm_type_key IN('50008','50009','50010'))THEN          #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE
         SET p_alarm_desc = concat(NEW.description,v_acknowledged);
SET p_alarm_value = v_dp_param_list;
      ELSE
         SET p_alarm_desc = concat(NEW.description,v_acknowledged);
SET p_alarm_value = concat(p_alarm_type_name, ' ', v_dp_param_list);
      END IF;
    ELSEIF(NEW.eventtype = '30016') THEN                             #30016 => NORMALISED
       #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE, OH, VH, HI, LO, VL, OL
#        IF(p_alarm_type_key IN('50008','50009','50010','50011','50012','50013','50014','50015','50016'))THEN
#           p_alarm_desc := NULL;
#           p_alarm_value:= NULL;
#        ELSE
          SET p_alarm_desc = concat(NEW.description,v_normalised);
#          p_alarm_value:= p_alarm_type_name||' '||v_dp_param_list;
SET p_alarm_value = v_dp_param_list;
#        END IF;
# ++LC : TD17292
    ELSEIF (NEW.eventtype IN ('30306','30291','30304','30310')) THEN
      SET p_alarm_desc = NEW.description;
SET p_alarm_value = 'Successfull';
# ++LC : TD17292
   ELSE
      SET p_alarm_desc= NEW.description;

CALL prc_dp_param_list(NEW.param_list, v_dp_ev_param_list);
      IF (NEW.param_list <> v_dp_ev_param_list) THEN
         SET p_alarm_value= v_dp_ev_param_list;
# Need to put DP value ("DataPointValue" parameter) into value column if it exists for any type.
      ELSE
          SET p_alarm_value= concat(p_event_type_name,' ',p_alarm_type_name);
# Same as before with all other ALARM_TYPES
      END IF;
   END IF;

# ++ CF : TD13673
   IF (p_entity_location_key != 0) THEN
      SET p_location_key = p_entity_location_key;
   ELSEIF (NEW.locationkey != 0) THEN
      SET p_location_key = NEW.locationkey;
   END IF;
# ++ CF : TD13673
# TD18052
   IF ( NEW.eventtype IN ('30253', '30232') ) THEN
         SET p_alarm_value = 'Bad Launch';
   ELSEIF ( NEW.eventtype IN ('30254', '30233') ) THEN
         SET p_alarm_value = 'Bad Return';
   END IF;
# TD19052

  #TD20476  hyl add
  #DTL-822 Comment out
  #IF ( :NEW.eventtype ='30463' ) THEN
  #      dp_value_from_param_list(:NEW.param_list,p_alarm_value);
  #END IF;
  #DTL-822
  #TD20476

   IF p_alarm_desc <> '' THEN
    IF p_physical_subsystem_key <> '' THEN
        SET p_subsystem_key = p_physical_subsystem_key;
    END IF;

CALL prc_ev_api_populate_ev_combined(
        '100',
        NEW.pkey,
        str_to_date(NEW.createtime, '%Y-%m-%d %H:%i:%s'),
        NEW.createtime,
        p_subsystem_key,
        ifnull(p_physical_subsystem_key, -1),
        p_location_key,
        p_severity_key,
        p_severity_name,
        NEW.asset_name,
        p_alarm_desc,
        cast(NEW.eventtype AS UNSIGNED INT),
        p_event_type_name,
        NEW.alarm_id,
        p_alarm_type_key,
        p_alarm_value,
        p_alarm_mms_state,
        p_alarm_dss_state,
        p_alarm_avl_state,
        p_operator_key,
        p_operator_name,
        p_alarm_comment,
        p_event_view_level,
        p_alarm_ack,
        p_alarm_status,
        NEW.sessionkey,
        p_session_location,
        p_profile_id,
        p_action_id,
        p_operation_mode);
  END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `event_evcom_aur_trg` AFTER UPDATE
    ON event FOR EACH ROW
BEGIN

   DECLARE p_subsystem_key int(9);
   DECLARE p_physical_subsystem_key INT(9);
   DECLARE p_location_key INT(9);
   DECLARE p_event_type_name VARCHAR(256);
   DECLARE p_event_view_level INT(1);
   DECLARE p_operator_key INT(9);
   DECLARE p_operator_name VARCHAR(85);
   DECLARE p_severity_key INT(9);
   DECLARE p_severity_name VARCHAR(20);
   DECLARE p_alarm_type_key INT;
   DECLARE p_alarm_type_name VARCHAR(256);
   DECLARE p_alarm_comment VARCHAR(2000);
   DECLARE p_alarm_mms_state VARCHAR(100);
   DECLARE p_alarm_dss_state VARCHAR(30);
   DECLARE p_alarm_avl_state VARCHAR(100);
   DECLARE p_alarm_param_list VARCHAR(2000);
   DECLARE p_alarm_value VARCHAR(2000);
   DECLARE p_alarm_desc VARCHAR(2000);
   DECLARE p_alarm_ack VARCHAR(38);
   DECLARE p_alarm_status VARCHAR(2);
   DECLARE v_normalised VARCHAR(20) DEFAULT ' - Normalised';
   DECLARE v_acknowledged VARCHAR(20) DEFAULT ' - Acknowledged';
   DECLARE v_omflag_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE v_dp_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE v_dp_ev_param_list VARCHAR(2000) DEFAULT NULL;
   DECLARE p_entity_location_key INT(9) DEFAULT 0;
   DECLARE p_session_LOCATION        INT(9) DEFAULT NULL;
   DECLARE p_profile_id        INT(9) DEFAULT -1;
   DECLARE is_system   INT(9);
   DECLARE p_action_id INT(9);
   DECLARE p_operation_mode VARCHAR(2);

   DECLARE  cu_entity CURSOR FOR
      SELECT
         subsystemkey AS SUBSYSTEM_KEY,
         physical_subsystem_key AS PHYSICAL_SUBSYSTEM_KEY,
         locationkey AS LOCATION_KEY
      FROM entity
      WHERE pkey = NEW.entitykey;

   DECLARE cu_event CURSOR FOR
      SELECT
         type_name AS EVENT_TYPE_NAME,
         view_level AS EVENT_VIEW_LEVEL,
         (SELECT operatorkey FROM ta_session WHERE pkey = NEW.sessionkey ) AS OPERATOR_KEY,
         (SELECT NAME FROM operator WHERE pkey = (SELECT operatorkey FROM ta_session WHERE pkey = NEW.sessionkey)) AS OPERATOR_NAME,
         (SELECT (ifnull((SELECT pkey FROM location WHERE NAME='OCC'),0))) AS LOCATION_KEY
      FROM me_message_type
      WHERE memtyp_id = NEW.eventtype;

   DECLARE cu_session CURSOR FOR
        SELECT
        consolekey AS session_location,
        SEPROF_ID  AS profile_id
        FROM ta_session
        WHERE pkey = NEW.sessionkey;

   DECLARE cu_alarm CURSOR FOR
      SELECT
         a.SEVERITY AS SEVERITY_KEY,
         (SELECT NAME FROM alarmseverity WHERE pkey = a.SEVERITY) AS SEVERITY_NAME,
         a.param_list AS ALARM_PLIST,
         t.meatyp_id AS ALARM_TYPE_KEY,
         ifnull(t.type_name,'') AS ALARM_TYPE_NAME,
         a.comments AS ALARM_COMMENT,
         a.mms_state_type AS ALARM_MMS_STATE,
         a.planstatus AS ALARM_DSS_STATE,
         a.avl_status AS ALARM_AVL_STATE,
         a.acknowledged_by AS ALARM_ACK,
         a.state AS ALARM_STATUS
      FROM alarm a, me_alarm_type t
      WHERE a.alarm_id = NEW.alarm_id AND meatyp_id = cast(a.TYPE AS UNSIGNED INT);

   DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';



DELETE FROM ev_combined
 WHERE source_table = '100' AND pkey = OLD.pkey;

   OPEN cu_entity;
        FETCH cu_entity INTO p_subsystem_key,p_physical_subsystem_key,p_entity_location_key;
   CLOSE cu_entity;
BEGIN
   DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
   DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';

   OPEN cu_event;
    FETCH cu_event INTO p_event_type_name,p_event_view_level,p_operator_key,p_operator_name,p_location_key;
   CLOSE cu_event;
   OPEN cu_alarm;
         FETCH cu_alarm INTO p_severity_key,p_severity_name,p_alarm_param_list,p_alarm_type_key,p_alarm_type_name,p_alarm_comment,p_alarm_mms_state,p_alarm_dss_state,p_alarm_avl_state,p_alarm_ack,p_alarm_status;
   CLOSE cu_alarm;
END;

BEGIN
   DECLARE CONTINUE HANDLER FOR SQLEXCEPTION SET @1='err1';
   DECLARE CONTINUE HANDLER FOR SQLWARNING SET @3='err3';
# dbms_output.enable(10000);
   IF NEW.sessionkey IS  NULL OR NEW.sessionkey = 'InternalProcessing'  or trim(NEW.sessionkey) = '' THEN
    set p_profile_id = -1;
#    dbms_output.put_line('sessionkey is null here');
   ELSE
#    dbms_output.put_line('sessionkey is ::' || :new.sessionkey);
       OPEN cu_session;
        FETCH cu_session INTO p_session_location,p_profile_id;
       CLOSE cu_session;

        SELECT is_system INTO is_system FROM se_profile s WHERE s.seprof_id = p_profile_id;

       IF is_system = 1 THEN
        SET p_profile_id = -1;
       END IF;
/*
       if  p_physical_subsystem_key <> '' then
        p_profile_id := -1;
       end if;
*/
    END IF;
END;

CALL prc_omflag_param_list(p_alarm_param_list, v_omflag_param_list);
# prepare for variable p_operation_mode
IF (v_omflag_param_list <> '') THEN
    IF (v_omflag_param_list = 'N') THEN
        SET p_operation_mode ='';
    ELSE
        SET p_operation_mode = v_omflag_param_list;
    END IF;
ELSE  # if There is no param string 'OMFlag' in param_list of alarm table
   SET p_operation_mode ='';
END IF;

SELECT SEACTI_ID
  INTO p_action_id
  FROM se_action
 WHERE MEMTYP_ID = cast(NEW.eventtype AS UNSIGNED INT);

CALL prc_dp_param_list(p_alarm_param_list, v_dp_param_list);
IF(NEW.eventtype = '30022') THEN                               #30022 => SUBMITTED
      IF(p_alarm_type_key IN('50008','50009','50010'))THEN         #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE
         set p_alarm_desc = NEW.description;
         set p_alarm_value = v_dp_param_list;
      ELSE
         set p_alarm_desc = NEW.description;
         set p_alarm_value = concat(p_alarm_type_name,' ',v_dp_param_list);
      END IF;
   ELSEIF(NEW.eventtype = '30013') THEN                             #30013 => ACKNOWLEDGED
      IF(p_alarm_type_key IN('50008','50009','50010'))THEN          #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE
         SET p_alarm_desc = concat(NEW.description,v_acknowledged);
SET p_alarm_value = v_dp_param_list;
      ELSE
         SET p_alarm_desc = concat(NEW.description,v_acknowledged);
SET p_alarm_value = concat(p_alarm_type_name, ' ', v_dp_param_list);
      END IF;
    ELSEIF(NEW.eventtype = '30016') THEN                             #30016 => NORMALISED
       #IF THE ALARM_TYPE in DPGENERAL,DPTRUE,DPFALSE, OH, VH, HI, LO, VL, OL
#        IF(p_alarm_type_key IN('50008','50009','50010','50011','50012','50013','50014','50015','50016'))THEN
#           p_alarm_desc := NULL;
#           p_alarm_value:= NULL;
#        ELSE
          SET p_alarm_desc = concat(NEW.description,v_normalised);
#          p_alarm_value:= p_alarm_type_name||' '||v_dp_param_list;
SET p_alarm_value = v_dp_param_list;
#        END IF;
# ++LC : TD17292
    ELSEIF (NEW.eventtype IN ('30306','30291','30304','30310')) THEN
      SET p_alarm_desc = NEW.description;
SET p_alarm_value = 'Successfull';
# ++LC : TD17292
   ELSE
      SET p_alarm_desc= NEW.description;

CALL prc_dp_param_list(NEW.param_list, v_dp_ev_param_list);
      IF (NEW.param_list <> v_dp_ev_param_list) THEN
         SET p_alarm_value= v_dp_ev_param_list;
# Need to put DP value ("DataPointValue" parameter) into value column if it exists for any type.
      ELSE
          SET p_alarm_value= concat(p_event_type_name,' ',p_alarm_type_name);
# Same as before with all other ALARM_TYPES
      END IF;
   END IF;

# ++ CF : TD13673
   IF (p_entity_location_key != 0) THEN
      SET p_location_key = p_entity_location_key;
   ELSEIF (NEW.locationkey != 0) THEN
      SET p_location_key = NEW.locationkey;
   END IF;
# ++ CF : TD13673
# TD18052
   IF ( NEW.eventtype IN ('30253', '30232') ) THEN
         SET p_alarm_value = 'Bad Launch';
   ELSEIF ( NEW.eventtype IN ('30254', '30233') ) THEN
         SET p_alarm_value = 'Bad Return';
   END IF;
# TD19052

  #TD20476  hyl add
  #DTL-822 Comment out
  #IF ( :NEW.eventtype ='30463' ) THEN
  #      dp_value_from_param_list(:NEW.param_list,p_alarm_value);
  #END IF;
  #DTL-822
  #TD20476

   IF p_alarm_desc <> '' THEN
    IF p_physical_subsystem_key <> '' THEN
        SET p_subsystem_key = p_physical_subsystem_key;
    END IF;

CALL prc_ev_api_populate_ev_combined(
        '100',
        NEW.pkey,
        str_to_date(NEW.createtime, '%Y-%m-%d %H:%i:%s'),
        NEW.createtime,
        p_subsystem_key,
        ifnull(p_physical_subsystem_key, -1),
        p_location_key,
        p_severity_key,
        p_severity_name,
        NEW.asset_name,
        p_alarm_desc,
        cast(NEW.eventtype AS UNSIGNED INT),
        p_event_type_name,
        NEW.alarm_id,
        p_alarm_type_key,
        p_alarm_value,
        p_alarm_mms_state,
        p_alarm_dss_state,
        p_alarm_avl_state,
        p_operator_key,
        p_operator_name,
        p_alarm_comment,
        p_event_view_level,
        p_alarm_ack,
        p_alarm_status,
        NEW.sessionkey,
        p_session_location,
        p_profile_id,
        p_action_id,
        p_operation_mode);
  END IF;

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER event_evcom_adr_trg
 AFTER DELETE ON event FOR EACH ROW
BEGIN    
    DELETE FROM ev_combined WHERE source_table = '100' AND pkey = OLD.pkey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eventcolour_bfi_row_audit` BEFORE INSERT
    ON eventcolour FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eventcolour_bfu_row_audit` BEFORE UPDATE
    ON eventcolour FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eventplanmap_bfi_row_audit` BEFORE INSERT
    ON eventplanmaps FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `eventplanmap_bfu_row_audit` BEFORE UPDATE
    ON eventplanmaps FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `gparam_bfi_trg` BEFORE INSERT
    ON global_parameter FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `gparam_bfu_trg` BEFORE UPDATE
    ON global_parameter FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `guiapp_bfi_row_audit` BEFORE INSERT
    ON guiapplication FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `guiapp_bfu_row_audit` BEFORE UPDATE
    ON guiapplication FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ininci_bif_trg` BEFORE INSERT
    ON in_incident_report FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ininci_buf_trg` BEFORE UPDATE
    ON in_incident_report FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `inplan_bif_trg` BEFORE INSERT
    ON in_plan FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `inplan_buf_trg` BEFORE UPDATE
    ON in_plan FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `inrepo_bif_trg` BEFORE INSERT
    ON in_report_access FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `inrepo_buf_trg` BEFORE UPDATE
    ON in_report_access FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `instat_bif_trg` BEFORE INSERT
    ON in_station_report FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `instat_buf_trg` BEFORE UPDATE
    ON in_station_report FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `lodsch_bir_trg` BEFORE INSERT
    ON lo_datapt_state_change FOR EACH ROW
BEGIN
	DECLARE  p_ukey   INT(11);
	SELECT func_seq_get_next_number('EV_COMBINED_SEQ') INTO  p_ukey;  
	SET NEW.UKEY = p_ukey;   
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `lodsch_evcom_air_trg` AFTER INSERT
    ON lo_datapt_state_change FOR EACH ROW
BEGIN
   DECLARE p_subsystem_key            int(9);
   DECLARE p_physical_subsystem_key   int(9);
   DECLARE p_location_key             int(9);
   DECLARE p_asset_name               VARCHAR(1000);
   DECLARE p_description              VARCHAR(2000);
   DECLARE p_operator_key             int(9);
   DECLARE p_operator_name            VARCHAR(85);
   DECLARE p_event_type_name          VARCHAR(256);
   DECLARE p_event_view_level         int(9);
   DECLARE p_datapoint_name           VARCHAR(85);
   DECLARE p_alarm_status             VARCHAR(2);
   DECLARE p_session_LOCATION         int(9) DEFAULT NULL;
   DECLARE p_profile_id               int(9) DEFAULT -1;
   DECLARE is_system                  int(9);
   DECLARE p_action_id                int(9);

-- new parameter for mysql
   DECLARE p_operation_mode VARCHAR(2) DEFAULT NULL;

   DECLARE
      cu_event CURSOR FOR
         SELECT type_name AS EVENT_TYPE_NAME, view_level AS EVENT_VIEW_LEVEL
           FROM me_message_type
          WHERE memtyp_id = NEW.eventtypekey;

   DECLARE
      cu_entity CURSOR FOR SELECT e.subsystemkey AS SUBSYSTEM_KEY,
                                  e.physical_subsystem_key
                                     AS PHYSICAL_SUBSYSTEM_KEY,
                                  e.locationkey AS LOCATION_KEY,
                                  (SELECT value
                                     FROM entityparametervalue
                                    WHERE entitykey = e.parentkey
                                          AND parameterkey =
                                                 (SELECT pkey
                                                    FROM entityparameter
                                                   WHERE name = 'AssetName'
                                                         AND typekey IN
                                                                (SELECT pkey
                                                                   FROM entitytype
                                                                  WHERE name =
                                                                           'DataNode'))),
                                  e.NAME AS NAME
                             FROM entity e
                            WHERE e.pkey = NEW.entitykey;

   DECLARE
      cu_session CURSOR FOR
         SELECT operatorkey AS OPERATOR_KEY,
                consolekey AS session_location,
                SEPROF_ID AS profile_id,
                (SELECT name
                   FROM operator
                  WHERE pkey = (SELECT operatorkey
                                  FROM ta_session
                                 WHERE pkey = NEW.sessionkey))
                   AS OPERATOR_NAME
           FROM ta_session
          WHERE pkey = NEW.sessionkey;

   DECLARE
      cu_entityparametervalue CURSOR FOR SELECT value AS MESSAGE
                                           FROM entityparametervalue
                                          WHERE entitykey = NEW.entitykey
                                                AND parameterkey =
                                                       NEW.alarmmessagekey;

   DECLARE
      cu_sc_derived_state CURSOR FOR SELECT alarm_message AS MESSAGE
                                       FROM sc_derived_state
                                      WHERE derived_dp_pkey = NEW.entitykey
                                            AND state_value =
                                                   NEW.generalmessagekey;

   DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';
   
   OPEN cu_event;

   FETCH cu_event
     INTO p_event_type_name, p_event_view_level;

   CLOSE cu_event;

   OPEN cu_entity;

   FETCH cu_entity
     INTO p_subsystem_key,
          p_physical_subsystem_key,
          p_location_key,
          p_asset_name,
          p_datapoint_name;

   CLOSE cu_entity;

   OPEN cu_session;

   FETCH cu_session
     INTO p_operator_key, p_session_location, p_profile_id, p_operator_name;

   CLOSE cu_session;

   IF NEW.sessionkey IS NULL or NEW.sessionkey = '' OR NEW.sessionkey = 'InternalProcessing'
   THEN
      SET p_profile_id = -1;
   ELSE
      SELECT is_system
        INTO is_system
        FROM se_profile s
       WHERE s.seprof_id = p_profile_id;

      IF is_system = 1
      THEN
         SET p_profile_id = -1;
      END IF;
   /*
          if  p_physical_subsystem_key <> '' then
           p_profile_id := -1;
          end if;
   */
   END IF;

   SELECT SEACTI_ID
     INTO p_action_id
     FROM se_action
    WHERE MEMTYP_ID = cast(NEW.eventtypekey AS unsigned);

   IF NEW.alarmmessagekey <> ''
   THEN
      OPEN cu_entityparametervalue;

      FETCH cu_entityparametervalue INTO p_description;

      CLOSE cu_entityparametervalue;

      IF p_description IS NULL OR p_description = ''
      THEN
         SET p_description =
                concat('Description not set for datapoint ',
                       p_datapoint_name,
                       '(',
                       NEW.entitykey,
                       ') state: ',
                       NEW.alarmmessagekey);
      END IF;
   ELSEIF NEW.generalmessagekey <> ''
   THEN
      OPEN cu_sc_derived_state;

      FETCH cu_sc_derived_state INTO p_description;

      CLOSE cu_sc_derived_state;

      IF p_description IS NULL OR p_description = ''
      THEN
         SET p_description =
                concat('Description not set for derived datapoint ',
                       p_datapoint_name,
                       '(',
                       NEW.entitykey,
                       ') state: ',
                       NEW.generalmessagekey);
      END IF;
   ELSE
      SET p_description =
             concat(p_datapoint_name,
                    ' (',
                    NEW.entitykey,
                    ')');
   END IF;

   SET p_alarm_status = '';

   IF p_event_type_name = 'AlarmClosed'
   THEN
      -- take normalize event from alarm agent and supress normalize event from PMSAgent
      --       p_description := p_description || '-Normalised';
      --       p_alarm_status := '0';
      BEGIN
      END;
   ELSE
      IF p_physical_subsystem_key <> ''
      THEN
         SET p_subsystem_key = p_physical_subsystem_key;
      END IF;

      CALL prc_ev_api_populate_ev_combined(
              '200',
              NEW.ukey,
              NEW.timestamp,
              str_to_date(NEW.timestamp, '%Y-%m-%d %H:%i:%s'),
              p_subsystem_key,
              ifnull(p_physical_subsystem_key, -1),
              p_location_key,
              0,
              NULL,
              p_asset_name,
              p_description,
              NEW.eventtypekey,
              p_event_type_name,
              NULL,
              NULL,
              NEW.value,
              '',
              '',
              '',
              p_operator_key,
              p_operator_name,
              NULL,
              p_event_view_level,
              '',
              p_alarm_status,
              NEW.sessionkey,
              p_session_location,
              p_profile_id,
              p_action_id,
              p_operation_mode);
   END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `lodsch_evcom_aur_trg` AFTER UPDATE
    ON lo_datapt_state_change FOR EACH ROW
BEGIN
   DECLARE p_subsystem_key            int(9);
   DECLARE p_physical_subsystem_key   int(9);
   DECLARE p_location_key             int(9);
   DECLARE p_asset_name               VARCHAR(1000);
   DECLARE p_description              VARCHAR(2000);
   DECLARE p_operator_key             int(9);
   DECLARE p_operator_name            VARCHAR(85);
   DECLARE p_event_type_name          VARCHAR(256);
   DECLARE p_event_view_level         int(9);
   DECLARE p_datapoint_name           VARCHAR(85);
   DECLARE p_alarm_status             VARCHAR(2);
   DECLARE p_session_LOCATION         int(9) DEFAULT NULL;
   DECLARE p_profile_id               int(9) DEFAULT -1;
   DECLARE is_system                  int(9);
   DECLARE p_action_id                int(9);

-- new parameter for mysql
   DECLARE p_operation_mode VARCHAR(2) DEFAULT NULL;

   DECLARE
      cu_event CURSOR FOR
         SELECT type_name AS EVENT_TYPE_NAME, view_level AS EVENT_VIEW_LEVEL
           FROM me_message_type
          WHERE memtyp_id = NEW.eventtypekey;

   DECLARE
      cu_entity CURSOR FOR SELECT e.subsystemkey AS SUBSYSTEM_KEY,
                                  e.physical_subsystem_key
                                     AS PHYSICAL_SUBSYSTEM_KEY,
                                  e.locationkey AS LOCATION_KEY,
                                  (SELECT value
                                     FROM entityparametervalue
                                    WHERE entitykey = e.parentkey
                                          AND parameterkey =
                                                 (SELECT pkey
                                                    FROM entityparameter
                                                   WHERE name = 'AssetName'
                                                         AND typekey IN
                                                                (SELECT pkey
                                                                   FROM entitytype
                                                                  WHERE name =
                                                                           'DataNode'))),
                                  e.NAME AS NAME
                             FROM entity e
                            WHERE e.pkey = NEW.entitykey;

   DECLARE
      cu_session CURSOR FOR
         SELECT operatorkey AS OPERATOR_KEY,
                consolekey AS session_location,
                SEPROF_ID AS profile_id,
                (SELECT name
                   FROM operator
                  WHERE pkey = (SELECT operatorkey
                                  FROM ta_session
                                 WHERE pkey = NEW.sessionkey))
                   AS OPERATOR_NAME
           FROM ta_session
          WHERE pkey = NEW.sessionkey;

   DECLARE
      cu_entityparametervalue CURSOR FOR SELECT value AS MESSAGE
                                           FROM entityparametervalue
                                          WHERE entitykey = NEW.entitykey
                                                AND parameterkey =
                                                       NEW.alarmmessagekey;

   DECLARE
      cu_sc_derived_state CURSOR FOR SELECT alarm_message AS MESSAGE
                                       FROM sc_derived_state
                                      WHERE derived_dp_pkey = NEW.entitykey
                                            AND state_value =
                                                   NEW.generalmessagekey;
                                                   
   DECLARE CONTINUE HANDLER FOR NOT FOUND SET @2='err2';

   DELETE FROM ev_combined
    WHERE pkey = OLD.ukey;

   OPEN cu_event;

   FETCH cu_event
     INTO p_event_type_name, p_event_view_level;

   CLOSE cu_event;

   OPEN cu_entity;

   FETCH cu_entity
     INTO p_subsystem_key,
          p_physical_subsystem_key,
          p_location_key,
          p_asset_name,
          p_datapoint_name;

   CLOSE cu_entity;

   OPEN cu_session;

   FETCH cu_session
     INTO p_operator_key, p_session_location, p_profile_id, p_operator_name;

   CLOSE cu_session;

   IF NEW.sessionkey IS NULL or NEW.sessionkey = '' OR NEW.sessionkey = 'InternalProcessing'
   THEN
      SET p_profile_id = -1;
   ELSE
      SELECT is_system
        INTO is_system
        FROM se_profile s
       WHERE s.seprof_id = p_profile_id;

      IF is_system = 1
      THEN
         SET p_profile_id = -1;
      END IF;
   /*
          if  p_physical_subsystem_key <> '' then
           p_profile_id := -1;
          end if;
   */
   END IF;

   SELECT SEACTI_ID
     INTO p_action_id
     FROM se_action
    WHERE MEMTYP_ID = cast(NEW.eventtypekey AS unsigned);

   IF NEW.alarmmessagekey <> ''
   THEN
      OPEN cu_entityparametervalue;

      FETCH cu_entityparametervalue INTO p_description;

      CLOSE cu_entityparametervalue;

      IF p_description IS NULL OR p_description = ''
      THEN
         SET p_description =
                concat('Description not set for datapoint ',
                       p_datapoint_name,
                       '(',
                       NEW.entitykey,
                       ') state: ',
                       NEW.alarmmessagekey);
      END IF;
   ELSEIF NEW.generalmessagekey <> ''
   THEN
      OPEN cu_sc_derived_state;

      FETCH cu_sc_derived_state INTO p_description;

      CLOSE cu_sc_derived_state;

      IF p_description IS NULL OR p_description = ''
      THEN
         SET p_description =
                concat('Description not set for derived datapoint ',
                       p_datapoint_name,
                       '(',
                       NEW.entitykey,
                       ') state: ',
                       NEW.generalmessagekey);
      END IF;
   ELSE
      SET p_description =
             concat(p_datapoint_name,
                    ' (',
                    NEW.entitykey,
                    ')');
   END IF;

   SET p_alarm_status = '';

   IF p_event_type_name = 'AlarmClosed'
   THEN
      -- take normalize event from alarm agent and supress normalize event from PMSAgent
      --       p_description := p_description || '-Normalised';
      --       p_alarm_status := '0';
      BEGIN
      END;
   ELSE
      IF p_physical_subsystem_key <> ''
      THEN
         SET p_subsystem_key = p_physical_subsystem_key;
      END IF;

      CALL prc_ev_api_populate_ev_combined(
              '200',
              NEW.ukey,
              NEW.timestamp,
              str_to_date(NEW.timestamp, '%Y-%m-%d %H:%i:%s'),
              p_subsystem_key,
              ifnull(p_physical_subsystem_key, -1),
              p_location_key,
              0,
              NULL,
              p_asset_name,
              p_description,
              NEW.eventtypekey,
              p_event_type_name,
              NULL,
              NULL,
              NEW.value,
              '',
              '',
              '',
              p_operator_key,
              p_operator_name,
              NULL,
              p_event_view_level,
              '',
              p_alarm_status,
              NEW.sessionkey,
              p_session_location,
              p_profile_id,
              p_action_id,
              p_operation_mode);
   END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER lodsch_evcom_adr_trg
AFTER DELETE ON lo_datapt_state_change FOR EACH ROW
BEGIN
	DELETE FROM ev_combined WHERE  pkey = OLD.ukey;	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `loc_bif_row_audit` BEFORE INSERT
    ON location FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `loc_aifr_row` AFTER INSERT ON location FOR EACH ROW
BEGIN
# Start of the trigger loc_air_trg
 BEGIN
# This trigger will generate an sql for creation of a unique sequence per location, to be used instead of entity_seq, to generate primary keys for entities under specified location.
 DECLARE v_location_num INT(11) DEFAULT NEW.pkey;
 DECLARE v_location_char VARCHAR(2);
 DECLARE v_location_seq_start VARCHAR(9);
 DECLARE v_location_seq_end VARCHAR(9);
 DECLARE v_sequence_ddl VARCHAR(1000);
 DECLARE V_JOB INT(11);
  
 set v_location_char = SUBSTR(LPAD(CAST(NEW.pkey AS CHAR),2,'0'),1,2);
 set v_location_seq_start = CONCAT(SUBSTR(LPAD(CAST(NEW.pkey+1 AS CHAR),2,'0'),1,2) , '0000001');
 set v_location_seq_end = CAST(CAST(v_location_seq_start AS UNSIGNED) + 9999999 AS CHAR);
 set v_sequence_ddl = CONCAT('CREATE SEQUENCE entity_',v_location_char,'_seq START WITH ',v_location_seq_start,
  'MAXVALUE ',v_location_seq_end,' MINVALUE ',v_location_seq_start,' CYCLE');
  
 IF v_location_num < 98 THEN
  INSERT INTO entity_seq_source VALUES (v_sequence_ddl, CONCAT('entity_',v_location_char,'_seq'));
 END IF;
 END;
# End of the trigger loc_air_trg

# Start of the trigger loc_aif_row
 BEGIN
    INSERT INTO se_region( seregi_id, name, description ) VALUES ( NEW.pkey, NEW.name, NEW.description );
 END;
# End of the trigger loc_aif_row
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `loc_buf_row_audit` BEFORE UPDATE
    ON location FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER loc_auf_row
 AFTER UPDATE ON location FOR EACH ROW
 BEGIN
    update se_region set name = NEW.name, description = NEW.description
    where SEREGI_ID = OLD.pkey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarm_type_bif_row_audit` BEFORE INSERT
    ON me_alarm_type FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `alarm_type_buf_row_audit` BEFORE UPDATE
    ON me_alarm_type FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `msg_type_bif_row_audit` BEFORE INSERT
    ON me_message_type FOR EACH ROW
BEGIN 
    SET NEW.created_by = substring_index(user(),'@',1);
    SET NEW.date_created = SYSDATE();
    
    # TD15195 cf++
    IF NEW.isvisible = 0 then
        SET NEW.log_message = 0;
    END IF;	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `msg_type_buf_row_audit` BEFORE UPDATE
    ON me_message_type FOR EACH ROW
BEGIN 
    SET NEW.modified_by = substring_index(user(),'@',1);
    SET NEW.date_modified = SYSDATE();
    
    # TD15195
    IF NEW.isvisible = 0 then
        SET NEW.log_message = 0;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;



--
-- Temporary table structure for view `node_summary`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `node_tree_bif_row_audit` BEFORE INSERT
    ON node_tree FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `node_tree_buf_row_audit` BEFORE UPDATE
    ON node_tree FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `node_type_bif_row_audit` BEFORE INSERT
    ON node_type FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `node_type_buf_row_audit` BEFORE UPDATE
    ON node_type FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `off_peak_dr_pwrdmd_30min_view`
--



--
-- Temporary table structure for view `on_peak_dr_pwrdmd_30min_view`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `opc_bif_row_audit` BEFORE INSERT
    ON online_printcfg FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `opc_buf_row_audit` BEFORE UPDATE
    ON online_printcfg FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `opl_bif_row_audit` BEFORE INSERT
    ON online_printer FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `opl_buf_row_audit` BEFORE UPDATE
    ON online_printer FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `opc_dt_interval_trigger` BEFORE INSERT
    ON opc_dt_sample_grp FOR EACH ROW
BEGIN
	DECLARE tmpVar INT(11);
	SET tmpVar = 0;
	SELECT func_seq_get_next_number('OPC_DT_SAMPLE_GRP_ID') INTO tmpVar ;
	SET NEW.SAMPLE_GRP_ID = tmpVar;	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER sample_grp_iflag_trigger
AFTER  INSERT ON opc_dt_sample_grp FOR EACH ROW
BEGIN
   UPDATE config_vars
   SET VAR_VALUE ='Y'
   WHERE VAR_NAME = 'OPC_DT_SAMPLE_FLAG';
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER sample_grp_uflag_trigger
AFTER UPDATE ON opc_dt_sample_grp FOR EACH ROW
BEGIN
   UPDATE config_vars
   SET VAR_VALUE ='Y'
   WHERE VAR_NAME = 'OPC_DT_SAMPLE_FLAG';
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER sample_grp_dflag_trigger
AFTER DELETE ON opc_dt_sample_grp FOR EACH ROW
BEGIN
   UPDATE config_vars
   SET VAR_VALUE ='Y'
   WHERE VAR_NAME = 'OPC_DT_SAMPLE_FLAG';
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `operator_bif_row_audit` BEFORE INSERT
    ON operator FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `operator_air_trg` AFTER INSERT
    ON operator FOR EACH ROW
BEGIN
	DECLARE  v_nseregi_id  INT(9) DEFAULT 0;
	DECLARE  no_more_rows  BOOLEAN DEFAULT FALSE;
	DECLARE  c_get_region CURSOR FOR SELECT seregi_id FROM se_region;
	DECLARE  CONTINUE HANDLER FOR NOT FOUND SET no_more_rows = TRUE;
	
	OPEN c_get_region;
	the_loop: LOOP
		FETCH c_get_region INTO v_nseregi_id;
				
		IF no_more_rows THEN
			LEAVE the_loop;
		END IF;
		
		INSERT INTO se_operator_regions( seoreg_id, operatorkey, seregi_id ) values ( func_seq_get_next_number('SECURITY_SEQ'), NEW.pkey, v_nseregi_id );
	
	END LOOP the_loop ;
  CLOSE c_get_region;
	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `operator_buf_row_audit` BEFORE UPDATE
    ON operator FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER operator_aur_trg
 AFTER UPDATE ON operator FOR EACH ROW
BEGIN
	DECLARE  v_nseregi_id  INT(9) DEFAULT 0;
	DECLARE  no_more_rows  BOOLEAN DEFAULT FALSE;
	DECLARE  c_get_region CURSOR FOR SELECT seregi_id FROM se_region;
	DECLARE  CONTINUE HANDLER FOR NOT FOUND
		SET no_more_rows = TRUE;
	
	OPEN c_get_region;
	the_loop: LOOP
		FETCH c_get_region INTO v_nseregi_id;
		
		
		
		IF no_more_rows THEN
			CLOSE c_get_region;
			LEAVE the_loop;
		END IF;
		
		INSERT INTO se_operator_regions( seoreg_id, operatorkey, seregi_id ) values ( func_seq_get_next_number('SECURITY_SEQ'), NEW.pkey, v_nseregi_id );
	
	END LOOP the_loop ;
	
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER operator_bdr_trg
 BEFORE DELETE ON operator FOR EACH ROW
BEGIN
	delete from se_operator_regions where se_operator_regions.operatorkey = OLD.pkey;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `operator_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `paatbr_bif_trg` BEFORE INSERT
    ON pa_ats_triggered_broadcast FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `paatbr_buf_trg` BEFORE UPDATE
    ON pa_ats_triggered_broadcast FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmes_bif_trg` BEFORE INSERT
    ON pa_dva_message FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmes_buf_trg` BEFORE UPDATE
    ON pa_dva_message FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmprve_bif_trg` BEFORE INSERT
    ON pa_dva_message_private_version FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmprve_buf_trg` BEFORE UPDATE
    ON pa_dva_message_private_version FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmpuve_bif_trg` BEFORE INSERT
    ON pa_dva_message_public_version FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmpuve_buf_trg` BEFORE UPDATE
    ON pa_dva_message_public_version FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmve_bif_trg` BEFORE INSERT
    ON pa_dva_message_version FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `padmve_buf_trg` BEFORE UPDATE
    ON pa_dva_message_version FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pastat_bif_trg` BEFORE INSERT
    ON pa_station FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pastat_buf_trg` BEFORE UPDATE
    ON pa_station FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `patmmap_bif_trg` BEFORE INSERT
    ON pa_tis_message_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `patmmap_buf_trg` BEFORE UPDATE
    ON pa_tis_message_map FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `patdme_tif_trg` BEFORE INSERT
    ON pa_train_dva_message FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `patdme_tuf_trg` BEFORE UPDATE
    ON pa_train_dva_message FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazone_bif_trg` BEFORE INSERT
    ON pa_zone FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazone_buf_trg` BEFORE UPDATE
    ON pa_zone FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazgro_bif_trg` BEFORE INSERT
    ON pa_zone_group FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazgro_buf_trg` BEFORE UPDATE
    ON pa_zone_group FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazghe_bif_trg` BEFORE INSERT
    ON pa_zone_group_helper FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazghe_buf_trg` BEFORE UPDATE
    ON pa_zone_group_helper FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazhel_bif_trg` BEFORE INSERT
    ON pa_zone_helper FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `pazhel_buf_trg` BEFORE UPDATE
    ON pa_zone_helper FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `parameter_names`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `param_type_bif_row_audit` BEFORE INSERT
    ON parameter_type FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `param_type_buf_row_audit` BEFORE UPDATE
    ON parameter_type FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


--
-- Temporary table structure for view `plan_details`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ra_btncfg_bif_row_audit` BEFORE INSERT
    ON ra_btncfg FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ra_btncfg_buf_row_audit` BEFORE UPDATE
    ON ra_btncfg FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `racshi_bir_trg` BEFORE INSERT
    ON ra_call_stack_history FOR EACH ROW
BEGIN
	DECLARE	 v_racshi_id    INT(11) DEFAULT 0;
	SELECT func_seq_get_next_number('RACSHI_SEQ') INTO v_racshi_id ;
	SET NEW.RACSHI_ID = v_racshi_id ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `radent_bif_row_audit` BEFORE INSERT
    ON ra_directory_entry FOR EACH ROW
BEGIN
# Start of the trigger RADENT_NAME_CHECK
	DECLARE 	v_ckey  INT(11);
	select count(*) into v_ckey from ra_directory_entry radio
	where radio.OWNER = NEW.OWNER 
  and radio.CATEGORY = NEW.CATEGORY and radio.NAME = NEW.NAME;

	if v_ckey >= 1 then	    
		select 1 into @1 from Err_NameExistsInTabRA_DIRECTORY_ENTRY; 
	end if;
# End of the trigger RADENT_NAME_CHECK
  
# Start of the trigger RADENT_BF_ROW_AUDIT  
	SET NEW.created_by = substring_index(user(),'@',1);
	SET NEW.date_created = SYSDATE() ;
# End of the trigger RADENT_BF_ROW_AUDIT
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `radent_buf_row_audit` BEFORE UPDATE
    ON ra_directory_entry FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `radmem_bif_row_audit` BEFORE INSERT
    ON ra_directory_member FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `radmem_buf_row_audit` BEFORE UPDATE
    ON ra_directory_member FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ragmem_bir_trg` BEFORE INSERT
    ON ra_group_members FOR EACH ROW
BEGIN
	DECLARE  v_ragmem_id   INT(11) ;
	SELECT func_seq_get_next_number('RAGMEM_SEQ') INTO v_ragmem_id ;
	SET NEW.RAGMEM_ID = v_ragmem_id ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `raigro_audit_bir_trg` BEFORE INSERT
    ON ra_itsi_group FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `raigro_audit_bur_trg` BEFORE UPDATE
    ON ra_itsi_group FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `rapmem_bir_trg` BEFORE INSERT
    ON ra_patch_members FOR EACH ROW
BEGIN
	DECLARE  v_rapmem_id  INT(11) ;
	SELECT func_seq_get_next_number('RAPMEM_SEQ') INTO v_rapmem_id ;
	SET NEW.RAPMEM_ID = v_rapmem_id ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `raptex_bif_row_audit` BEFORE INSERT
    ON ra_predefined_textmessage FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `raptex_buf_row_audit` BEFORE UPDATE
    ON ra_predefined_textmessage FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `rasc_bir_trg` BEFORE INSERT
    ON ra_selected_calls FOR EACH ROW
BEGIN
	DECLARE  v_rasc_id   INT(11);
	SELECT func_seq_get_next_number('RASC_SEQ') INTO  v_rasc_id ;
	SET NEW.RASC_ID = v_rasc_id ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ra_subscriber_bif_row_audit` BEFORE INSERT
    ON ra_subscriber FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ra_subscriber_buf_row_audit` BEFORE UPDATE
    ON ra_subscriber FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ratinb_bif_row_audit` BEFORE INSERT
    ON ra_textmessage_inbox FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ratinb_buf_row_audit` BEFORE UPDATE
    ON ra_textmessage_inbox FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `razone_bif_trg` BEFORE INSERT
    ON ra_zone FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `razone_buf_trg` BEFORE UPDATE
    ON ra_zone FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scerep_bir_trg` BEFORE INSERT
    ON sc_equip_report FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scerep_bur_trg` BEFORE UPDATE
    ON sc_equip_report FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sceren_bir_trg` BEFORE INSERT
    ON sc_equip_report_entities FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sceren_bur_trg` BEFORE UPDATE
    ON sc_equip_report_entities FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scotal_audit_bir_trg` BEFORE INSERT
    ON sc_opc_tag_alias FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scotal_audit_bur_trg` BEFORE UPDATE
    ON sc_opc_tag_alias FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scssch_audit_bir_trg` BEFORE INSERT
    ON sc_scada_schematic FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `scssch_audit_bur_trg` BEFORE UPDATE
    ON sc_scada_schematic FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seacti_audit_bir_trg` BEFORE INSERT
    ON se_action FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seacti_audit_bur_trg` BEFORE UPDATE
    ON se_action FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `actgro_audit_bir_trg` BEFORE INSERT
    ON se_action_group FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `actgro_audit_bur_trg` BEFORE UPDATE
    ON se_action_group FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seagmap_audit_bir_trg` BEFORE INSERT
    ON se_action_group_map FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `update_on_update_se_xxx_i_trg` AFTER INSERT
    ON se_action_group_map FOR EACH ROW
BEGIN
    INSERT INTO t6 SELECT distinct (t2.seprof_id), t2.subsystemkey, t2.PHYSICAL_SUBSYSTEM_KEY, t2.SESSTA_ID, t2.SEAGRO_ID, NEW.SEACTI_ID FROM  t2  
	WHERE  t2.SEAGRO_ID = NEW.SEAGRO_ID   AND  NEW.seacti_id IN ( SELECT SEACTI_ID FROM se_action WHERE  name LIKE  '%EVENT_VIEW_%%');
    INSERT INTO t6  SELECT distinct(t1.seprof_id), t1.subsystemkey, t1.PHYSICAL_SUBSYSTEM_KEY, t1.SESSTA_ID, t1.SEAGRO_ID, NEW.SEACTI_ID FROM  t1  
	WHERE  t1.SEAGRO_ID = NEW.SEAGRO_ID  AND NEW.seacti_id IN ( SELECT SEACTI_ID FROM se_action WHERE  name LIKE  '%EVENT_VIEW_%%');  
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seagmap_audit_bur_trg` BEFORE UPDATE
    ON se_action_group_map FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `update_on_update_se_xxx_u_trg` AFTER UPDATE
    ON se_action_group_map FOR EACH ROW
BEGIN
    INSERT INTO t6 SELECT distinct (t2.seprof_id), t2.subsystemkey, t2.PHYSICAL_SUBSYSTEM_KEY, t2.SESSTA_ID, t2.SEAGRO_ID, NEW.SEACTI_ID FROM  t2  
	WHERE  t2.SEAGRO_ID = NEW.SEAGRO_ID   AND  NEW.seacti_id IN ( SELECT SEACTI_ID FROM se_action WHERE  name LIKE  '%EVENT_VIEW_%%');
    INSERT INTO t6  SELECT distinct(t1.seprof_id), t1.subsystemkey, t1.PHYSICAL_SUBSYSTEM_KEY, t1.SESSTA_ID, t1.SEAGRO_ID, NEW.SEACTI_ID FROM  t1  
	WHERE  t1.SEAGRO_ID = NEW.SEAGRO_ID  AND NEW.seacti_id IN ( SELECT SEACTI_ID FROM se_action WHERE  name LIKE  '%EVENT_VIEW_%%');  
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `update_on_update_se_xxx_d_trg` AFTER DELETE
    ON se_action_group_map FOR EACH ROW
BEGIN
    delete from t6 where  t6.seacti_id = OLD.seacti_id and t6.seagro_id = OLD.seagro_id;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `se_loc_reg_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seopro_audit_bir_trg` BEFORE INSERT
    ON se_operator_profile FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seopro_audit_bur_trg` BEFORE UPDATE
    ON se_operator_profile FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seorge_bir_trg` BEFORE INSERT
    ON se_operator_regions FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seorge_bur_trg` BEFORE UPDATE
    ON se_operator_regions FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seprof_audit_bir_trg` BEFORE INSERT
    ON se_profile FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seprof_audit_bur_trg` BEFORE UPDATE
    ON se_profile FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepacc_audit_bir_trg` BEFORE INSERT
    ON se_profile_access FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepacc_audit_bur_trg` BEFORE UPDATE
    ON se_profile_access FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepgro_audit_bir_trg` BEFORE INSERT
    ON se_profile_group FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepgro_audit_bur_trg` BEFORE UPDATE
    ON se_profile_group FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepp_audit_bir_trg` BEFORE INSERT
    ON se_profile_parameters FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sepp_audit_bur_trg` BEFORE UPDATE
    ON se_profile_parameters FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `septyp_audit_bir_trg` BEFORE INSERT
    ON se_profile_type FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `septyp_audit_bur_trg` BEFORE UPDATE
    ON se_profile_type FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `se_profile_v`
--


--
-- Temporary table structure for view `se_reg_sub_v`
--




/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seregi_bir_trg` BEFORE INSERT
    ON se_region FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `seregi_bur_trg` BEFORE UPDATE
    ON se_region FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `se_resource_v`
--



/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sessta_bir_trg` BEFORE INSERT
    ON se_subsystem_state FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sessta_bur_trg` BEFORE UPDATE
    ON se_subsystem_state FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sngmon_audit_bir_trg` BEFORE INSERT
    ON sn_group_monitor FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sngmon_audit_bur_trg` BEFORE UPDATE
    ON sn_group_monitor FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snmpro_audit_bir_trg` BEFORE INSERT
    ON sn_managed_process FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snmpro_audit_bur_trg` BEFORE UPDATE
    ON sn_managed_process FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snscon_audit_bir_trg` BEFORE INSERT
    ON sn_system_controller FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snscon_audit_bur_trg` BEFORE UPDATE
    ON sn_system_controller FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snscgr_audit_bir_trg` BEFORE INSERT
    ON sn_system_controller_group FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `snscgr_audit_bur_trg` BEFORE UPDATE
    ON sn_system_controller_group FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sosfil_bif_row_audit` BEFORE INSERT
    ON so_sound_file FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `sosfil_buf_row_audit` BEFORE UPDATE
    ON so_sound_file FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_details_bif_row_audit` BEFORE INSERT
    ON step_details FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_details_buf_row_audit` BEFORE UPDATE
    ON step_details FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_params_bif_row_audit` BEFORE INSERT
    ON step_parameters FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_params_buf_row_audit` BEFORE UPDATE
    ON step_parameters FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_type_bif_row_audit` BEFORE INSERT
    ON step_type FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `step_type_buf_row_audit` BEFORE UPDATE
    ON step_type FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `st_partype_bif_audit` BEFORE INSERT
    ON step_type_parameter_types FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `st_partype_buf_audit` BEFORE UPDATE
    ON step_type_parameter_types FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `subsystem_bif_row_audit` BEFORE INSERT
    ON subsystem FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `subsystem_aif_trg` AFTER INSERT
    ON subsystem FOR EACH ROW
BEGIN
  IF NEW.IS_PHYSICAL = 1 THEN
    INSERT INTO mm_scheduling(MMSCHE_ID, PHYSICALKEY) VALUES (func_seq_get_next_number('MMSCHE_SEQ'), NEW.PKEY);
  END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `subsystem_buf_row_audit` BEFORE UPDATE
    ON subsystem FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ta_sess_bif_row_audit` BEFORE INSERT
    ON ta_session FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `ta_sess_buf_row_audit` BEFORE UPDATE ON ta_session FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER tri_bandelsupsess
   BEFORE DELETE
   ON ta_session
   FOR EACH ROW
BEGIN
   IF old.pkey = 'TransActive Super Session ID'
   THEN
      SELECT 1 INTO @1 FROM Err_DeleteSuperSessIsProhibited;
   END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tedent_bif_trg` BEFORE INSERT
    ON te_directory_entry FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tedent_buf_trg` BEFORE UPDATE
    ON te_directory_entry FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesdbu_bif_trg` BEFORE INSERT
    ON te_speed_dial_button FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesdbu_buf_trg` BEFORE UPDATE
    ON te_speed_dial_button FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesdse_bif_trg` BEFORE INSERT
    ON te_speed_dial_set FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesdse_buf_trg` BEFORE UPDATE
    ON te_speed_dial_set FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesubd_bif_trg` BEFORE INSERT
    ON te_subdirectory FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tesubd_buf_trg` BEFORE UPDATE
    ON te_subdirectory FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `test_insert_date` BEFORE UPDATE
    ON test FOR EACH ROW
BEGIN

	SET NEW.mdate = SYSDATE();

END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `trg_test02_name` BEFORE INSERT
    ON test02 FOR EACH ROW
BEGIN
    set new.name = 'AUTO';
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER  tidreq_bif_row_audit
BEFORE INSERT ON ti_display_request FOR EACH ROW
BEGIN	
	SET NEW.create_time = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER  tidreq_buf_row_audit
BEFORE UPDATE ON ti_display_request FOR EACH ROW
BEGIN	
	SET NEW.create_time = SYSDATE();
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tirdes_bif_trg` BEFORE INSERT
    ON ti_ratis_dest FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tirdes_buf_trg` BEFORE UPDATE
    ON ti_ratis_dest FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tirtag_bif_trg` BEFORE INSERT
    ON ti_ratis_tag FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `tirtag_buf_trg` BEFORE UPDATE
    ON ti_ratis_tag FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `trtem_bif_row_audit` BEFORE INSERT
    ON trend_template FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `trtem_buf_row_audit` BEFORE UPDATE
    ON trend_template FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `version_bif_row_audit` BEFORE INSERT
    ON version FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `version_buf_row_audit` BEFORE UPDATE
    ON version FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `vistationid_bif_trg` BEFORE INSERT
    ON vi_station_id FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `vistationid_buf_trg` BEFORE UPDATE
    ON vi_station_id FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;


/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `vitrev_bif_trg` BEFORE INSERT
    ON vi_triggering_events FOR EACH ROW
BEGIN
  SET NEW.created_by = substring_index(user(),'@',1);
  SET NEW.date_created = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_bin */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=CURRENT_USER*/ /*!50003 TRIGGER `vitrev_buf_trg` BEFORE UPDATE
    ON vi_triggering_events FOR EACH ROW
BEGIN
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE() ;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

-- DB patches' modification
-- DTL-955STIS-DEV-R1
delimiter ;;
drop trigger if exists `trg_bir_tistis_time_sche` ;;
CREATE TRIGGER `trg_bir_tistis_time_sche`
 BEFORE insert ON ti_stis_time_schedule for each row
BEGIN
 select 1 into @1 from `Err_Only_Update_Is_Acceptable`;
END ;;
delimiter ;

delimiter ;;
drop trigger if exists `trg_bdr_tistis_time_sche` ;;
CREATE TRIGGER `trg_bdr_tistis_time_sche`
 BEFORE DELETE ON ti_stis_time_schedule FOR EACH ROW
BEGIN
 select 1 into @1 from `Err_Only_Update_Is_Acceptable`;
END ;;
delimiter ;

-- DTL-MMSInitRelease-02
delimiter ;;
drop trigger if exists `mms_request_alarm_pkey_trg` ;;
create trigger  `mms_request_alarm_pkey_trg`
 before insert on mms_request_alarm for each row
begin
  declare lv_pkey int(11);
  select func_seq_get_next_number('MMS_REQUEST_ALARM_SEQ') into lv_pkey;
  set new.pkey = lv_pkey;
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `mms_request_schematic_pkey_trg` ;;
create trigger  `mms_request_schematic_pkey_trg`
 before insert on mms_request_schematic for each row
begin
  declare lv_pkey int(11);
  select func_seq_get_next_number('MMS_REQUEST_SCHEMATIC_SEQ') into lv_pkey;
  set new.pkey = lv_pkey;
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `mms_request_prev_pkey_trg` ;;
create trigger  `mms_request_prev_pkey_trg`
 before insert on mms_request_scheduled for each row
begin
  declare lv_pkey int(11);
  select func_seq_get_next_number('MMS_REQUEST_SCHEDULED_SEQ') into lv_pkey;
  set new.pkey = lv_pkey;
end ;;
delimiter ;

-- DTL-PA-Development-02
delimiter ;;
drop trigger if exists `pa_hardware_parameter_bri_trg` ;;
create trigger `pa_hardware_parameter_bri_trg`
 before insert on pa_hardware_parameter for each row
begin
--
--  purpose  :- maintain audit columns in table pa_hardware_parameter
--  created by:  huangqi
--  date created:  05/09/2011
--
    set new.created_by = substring_index(user(),'@',1);
    set new.date_created := sysdate();
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `pa_hardware_parameter_bru_trg` ;;
create trigger `pa_hardware_parameter_bru_trg`
 before update on pa_hardware_parameter for each row
begin
--
--  purpose  :- maintain audit columns in table pa_hardware_parameter
--  created by:  huangqi
--  date created:  05/09/2011
--
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE();
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `pa_active_fire_alarm_bri_trg` ;;
create trigger `pa_active_fire_alarm_bri_trg`
 before insert on pa_fire_countdown for each row
begin
--
--  purpose  :- maintain audit columns in table pa_fire_countdown
--  created by:  huangqi
--  date created:  05/09/2011
--
    set new.created_by = substring_index(user(),'@',1);
    set new.date_created := sysdate();
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `pa_active_fire_alarm_bru_trg` ;;
create trigger `pa_active_fire_alarm_bru_trg`
 before update on pa_fire_countdown for each row
begin
--
--  purpose  :- maintain audit columns in table pa_fire_countdown
--  created by:  huangqi
--  date created:  05/09/2011
--
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE();
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `pa_paging_console_bri_trg` ;;
create trigger `pa_paging_console_bri_trg`
 before insert on pa_paging_console for each row
begin
--
--  purpose  :- maintain audit columns in table pa_fire_countdown
--  created by:  huangqi
--  date created:  05/09/2011
--
    set new.created_by = substring_index(user(),'@',1);
    set new.date_created := sysdate();
end ;;
delimiter ;

delimiter ;;
drop trigger if exists `pa_paging_console_bru_trg` ;;
create trigger `pa_paging_console_bru_trg`
 before update on pa_paging_console for each row
begin
 --
 --  purpose  :- maintain audit columns in table pa_paging_console
 --  created by:  huangjian
 --  date created:  05/10/2011
 --
  SET NEW.modified_by = substring_index(user(),'@',1);
  SET NEW.date_modified = SYSDATE();
end ;;
delimiter ;
