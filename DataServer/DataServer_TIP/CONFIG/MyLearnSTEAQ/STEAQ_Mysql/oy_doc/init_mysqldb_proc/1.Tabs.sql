/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


--
-- Table structure for table `db_baseline_version`
--
DROP TABLE IF EXISTS `db_baseline_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
create table `db_baseline_version` 
(version varchar(30)
)ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `adm_sequence`
--

DROP TABLE IF EXISTS `adm_sequence`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `adm_sequence` (
  `PKEY` int(11) NOT NULL,
  `NAME` varchar(30) COLLATE utf8_bin NOT NULL,
  `INIT_NUMBER` bigint(20) NOT NULL,
  `LAST_NUMBER` decimal(30,0) NOT NULL,
  `MAX_NUMBER` decimal(30,0) NOT NULL,
  `INCREMENT_BY` int(11) NOT NULL,
  `CYCLE_FLAG` varchar(1) COLLATE utf8_bin NOT NULL,
  KEY `idx_adm_seq_name` (`NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Table structure for table `ae_alarm_rule_param`
--

DROP TABLE IF EXISTS `ae_alarm_rule_param`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ae_alarm_rule_param` (
  `aearpa_id` int(9) NOT NULL,
  `alarm_rule_key` int(9) DEFAULT NULL,
  `action_parameter_type` varchar(80) NOT NULL,
  `action_parameter_value` varchar(256) DEFAULT NULL,
  `related_parameter_key` int(9) DEFAULT NULL,
  PRIMARY KEY (`aearpa_id`),
  KEY `aearpa_idx` (`alarm_rule_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `alarm`
--

DROP TABLE IF EXISTS `alarm`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alarm` (
  `alarm_id` varchar(38) NOT NULL,
  `sourcetime` varchar(23) NOT NULL,
  `transactivetime` varchar(23) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  `param_list` varchar(1024) DEFAULT NULL,
  `severity` int(9) NOT NULL,
  `type` varchar(50) NOT NULL,
  `context` varchar(50) NOT NULL,
  `state` int(1) NOT NULL,
  `planstatus` varchar(30) DEFAULT NULL,
  `mms_state_type` int(3) DEFAULT NULL,
  `avl_status` int(3) DEFAULT '0',
  `avl_head_id` varchar(38) DEFAULT NULL,
  `acknowledged_by` varchar(38) DEFAULT NULL,
  `ack_time` datetime DEFAULT NULL,
  `close_time` datetime DEFAULT NULL,
  `entitykey` int(9) NOT NULL,
  `comments` varchar(1024) DEFAULT NULL,
  `asset_name` varchar(256) DEFAULT NULL,
  `expired` datetime DEFAULT NULL,
  `is_unique` int(1) NOT NULL DEFAULT '1',
  `operator_name` varchar(85) DEFAULT NULL,
  PRIMARY KEY (`alarm_id`),
 # UNIQUE KEY `PK_ALARM` (`alarm_id`),
  KEY `alarm_severity_idx` (`severity`),
  KEY `alarm_type_idx` (`type`),
  KEY `idx_alarm_acknowledged` (`acknowledged_by`),
  KEY `idx_alarm_entity` (`entitykey`),
  KEY `idx_alarm_expired` (`expired`),
  KEY `idx_alarm_state` (`state`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `alarmplanmaps`
--

DROP TABLE IF EXISTS `alarmplanmaps`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alarmplanmaps` (
  `pkey` int(9) NOT NULL,
  `entitytypekey` int(9) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `alarmtypekey` int(9) NOT NULL,
  `planpath` varchar(300) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  KEY `alarmplanmaps_01_idx` (`entitytypekey`,`entitykey`,`alarmtypekey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `alarmrule`
--

DROP TABLE IF EXISTS `alarmrule`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alarmrule` (
  `pkey` int(9) NOT NULL,
  `entitytypekey` int(9) DEFAULT NULL,
  `entitykey` int(9) DEFAULT NULL,
  `alarmtype` int(9) DEFAULT NULL,
  `rule_trigger` varchar(50) NOT NULL,
  `ruletype` varchar(50) NOT NULL,
  `alarmdescription` varchar(1024) DEFAULT NULL,
  `created_by_session_key` varchar(38) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `created_by_profile_key` int(9) DEFAULT NULL,
  `created_by_operator_name` varchar(85) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_ALARMRULE` (`pkey`),
  KEY `alarmrule_entitykey_idx` (`entitykey`),
  KEY `alarmrule_entitytype_idx` (`entitytypekey`),
  KEY `alarmrule_idx` (`ruletype`),
  KEY `alarmrule_ruletrigger_idx` (`rule_trigger`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `alarmseverity`
--

DROP TABLE IF EXISTS `alarmseverity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `alarmseverity` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `open_acked_fg_colour1` int(9) NOT NULL,
  `open_acked_fg_colour2` int(9) NOT NULL,
  `open_acked_bg_colour1` int(9) NOT NULL,
  `open_acked_bg_colour2` int(9) NOT NULL,
  `open_unacked_fg_colour1` int(9) NOT NULL,
  `open_unacked_fg_colour2` int(9) NOT NULL,
  `open_unacked_bg_colour1` int(9) NOT NULL,
  `open_unacked_bg_colour2` int(9) NOT NULL,
  `closed_unacked_fg_colour1` int(9) NOT NULL,
  `closed_unacked_fg_colour2` int(9) NOT NULL,
  `closed_unacked_bg_colour1` int(9) NOT NULL,
  `closed_unacked_bg_colour2` int(9) NOT NULL,
  `sel_open_acked_fg_colour1` int(9) NOT NULL,
  `sel_open_acked_fg_colour2` int(9) NOT NULL,
  `sel_open_acked_bg_colour1` int(9) NOT NULL,
  `sel_open_acked_bg_colour2` int(9) NOT NULL,
  `sel_open_unacked_fg_colour1` int(9) NOT NULL,
  `sel_open_unacked_fg_colour2` int(9) NOT NULL,
  `sel_open_unacked_bg_colour1` int(9) NOT NULL,
  `sel_open_unacked_bg_colour2` int(9) NOT NULL,
  `sel_closed_unacked_fg_colour1` int(9) NOT NULL,
  `sel_closed_unacked_fg_colour2` int(9) NOT NULL,
  `sel_closed_unacked_bg_colour1` int(9) NOT NULL,
  `sel_closed_unacked_bg_colour2` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_ALARMSEVERITY` (`pkey`),
  KEY `alarmseverity_name_idx` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `alarmstate`
--
DROP TABLE IF EXISTS `alarmstate`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE  `alarmstate` (
  `pkey` int(9) DEFAULT NULL,
  `name` varchar(256) DEFAULT NULL,
  `displayname` varchar(500) DEFAULT NULL,
  `typekey` int(9) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `approval_state`
--

DROP TABLE IF EXISTS `approval_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `approval_state` (
  `p_key` int(6) NOT NULL,
  `state_value` int(6) NOT NULL,
  `state_name` varchar(50) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  UNIQUE KEY `plasta_01_uk` (`state_value`),
  UNIQUE KEY `plasta_02_uk` (`state_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `aq_timeout`
--

DROP TABLE IF EXISTS `aq_timeout`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `aq_timeout` (
  `pkey` decimal(22,0) NOT NULL,
  `timeout` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`pkey`)
  # , UNIQUE KEY `SYS_C008344` (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `aqtest`
--

DROP TABLE IF EXISTS `aqtest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `aqtest` (
  `sender` varchar(10) DEFAULT NULL,
  `d` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ar_inventory`
--

DROP TABLE IF EXISTS `ar_inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ar_inventory` (
  `arinve_id` int(9) NOT NULL,
  `data_date` datetime NOT NULL,
  `volume_label` varchar(30) DEFAULT NULL,
  `deleting` int(1) DEFAULT '0',
  `restored_date` datetime DEFAULT NULL,
  `restored_by` varchar(40) DEFAULT NULL,
  `deletion_due_date` datetime NOT NULL,
  `created_by` varchar(30) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`arinve_id`),
  KEY `arinventory_datadate_idx` (`data_date`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ar_online`
--

DROP TABLE IF EXISTS `ar_online`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ar_online` (
  `aronli_id` int(9) NOT NULL,
  `online_period` int(3) DEFAULT NULL,
  `data_expiry` int(3) DEFAULT NULL,
  PRIMARY KEY (`aronli_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ar_tables`
--

DROP TABLE IF EXISTS `ar_tables`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ar_tables` (
  `artabl_id` int(9) NOT NULL,
  `table_name` varchar(32) NOT NULL,
  `query_col` varchar(400) DEFAULT NULL,
  `file_postfix` varchar(15) NOT NULL,
  `created_by` varchar(30) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `purge_only` varchar(1) DEFAULT 'N',
  PRIMARY KEY (`artabl_id`),
  UNIQUE KEY `artabl_name_uk` (`table_name`),
  UNIQUE KEY `artabl_postfix_uk` (`file_postfix`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_branch_track`
--

DROP TABLE IF EXISTS `at_branch_track`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_branch_track` (
  `atbtra_id` int(9) NOT NULL,
  `track` varchar(3) NOT NULL,
  PRIMARY KEY (`atbtra_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_dss_plan_map`
--

DROP TABLE IF EXISTS `at_dss_plan_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_dss_plan_map` (
  `atdpma_id` int(9) NOT NULL,
  `dss_event` int(9) NOT NULL,
  `plan_path` varchar(300) NOT NULL,
  PRIMARY KEY (`atdpma_id`),
  UNIQUE KEY `atdpma_01_uk` (`dss_event`),
  KEY `atdpma_planpath_idx` (`plan_path`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_fixed_block_map`
--

DROP TABLE IF EXISTS `at_fixed_block_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_fixed_block_map` (
  `atfblo_id` int(9) NOT NULL,
  `branch_id` int(9) NOT NULL,
  `min_abscissa` int(9) NOT NULL,
  `max_abscissa` int(9) NOT NULL,
  `generic_id` decimal(9,1) NOT NULL,
  `zone_type` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`atfblo_id`),
  KEY `atbtra_branch_idx` (`branch_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_msszone`
--

DROP TABLE IF EXISTS `at_msszone`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_msszone` (
  `atmssz_id` int(9) NOT NULL,
  `station_id` int(9) NOT NULL,
  `mss_zone` varchar(30) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`atmssz_id`),
  KEY `atmssz_msszone_idx` (`mss_zone`),
  KEY `atmssz_stnid_idx` (`station_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_platform`
--

DROP TABLE IF EXISTS `at_platform`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_platform` (
  `atplat_id` int(9) NOT NULL,
  `platform_id` int(9) NOT NULL,
  `platform_name` varchar(30) NOT NULL,
  `station_id` int(9) NOT NULL,
  `tis_platform_id` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`atplat_id`),
  KEY `ATPLAM_PLATID_IDX` (`platform_id`),
  KEY `ATPLAM_PLATNAME_IDX` (`platform_name`),
  KEY `ATPLAM_STNID_IDX` (`station_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_power_entity_map`
--

DROP TABLE IF EXISTS `at_power_entity_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_power_entity_map` (
  `atpoem_id` int(9) NOT NULL,
  `subsection_id` int(9) NOT NULL,
  `location_key` int(9) NOT NULL,
  `data_point_entity_key` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `bit_position` varchar(1) DEFAULT '0',
  PRIMARY KEY (`atpoem_id`),
  KEY `ATPOEM_DPENTITYKEY_IDX` (`data_point_entity_key`),
  KEY `ATPOEM_LOCATION_IDX` (`location_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_psd_entity_map`
--

DROP TABLE IF EXISTS `at_psd_entity_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_psd_entity_map` (
  `atpema_id` int(9) NOT NULL,
  `platform_key` int(9) NOT NULL,
  `psd_number` int(2) NOT NULL,
  `data_point_entity_key` int(9) NOT NULL,
  `data_point_type` varchar(30) NOT NULL,
  `data_point_nameof_type` varchar(30) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`atpema_id`),
  KEY `ATPEMA_DPNAMETYPE_IDX` (`data_point_nameof_type`),
  KEY `ATPEMA_DPTYPE_IDX` (`data_point_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `at_twp_entity_map`
--

DROP TABLE IF EXISTS `at_twp_entity_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `at_twp_entity_map` (
  `attema_id` int(9) NOT NULL,
  `command` varchar(60) NOT NULL,
  `data_point_entity_key` int(9) NOT NULL,
  `data_point_entity_type` varchar(10) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`attema_id`),
  KEY `ATTEMA_DPENTITYTYPE_IDX` (`data_point_entity_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `bak_sn_managed_process`
--

DROP TABLE IF EXISTS `bak_sn_managed_process`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bak_sn_managed_process` (
  `snscon_id` int(9) NOT NULL,
  `managed_process_pkey` int(9) NOT NULL,
  `default_operating_mode` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `co_component`
--

DROP TABLE IF EXISTS `co_component`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `co_component` (
  `cocomp_id` int(9) NOT NULL,
  `category` varchar(30) NOT NULL,
  `component` varchar(30) NOT NULL,
  `library` varchar(256) NOT NULL,
  `entitytypekey` int(9) DEFAULT NULL,
  `help` varchar(1000) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`cocomp_id`),
  KEY `COCOMP_CATEGORY_IDX` (`category`),
  KEY `COCOMP_COMPONENT_IDX` (`component`),
  KEY `COCOMP_ENTITYTYPE_IDX` (`entitytypekey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `co_counter`
--

DROP TABLE IF EXISTS `co_counter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `co_counter` (
  `cocoun_id` int(9) NOT NULL,
  `location_id` int(9) NOT NULL,
  `next` int(9) NOT NULL DEFAULT '1',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`cocoun_id`,`location_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `co_line`
--

DROP TABLE IF EXISTS `co_line`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `co_line` (
  `coline_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`coline_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `config_editor_timestamp`
--

DROP TABLE IF EXISTS `config_editor_timestamp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `config_editor_timestamp` (
  `last_timestamp` varchar(26) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `config_vars`
--

DROP TABLE IF EXISTS `config_vars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `config_vars` (
  `var_name` varchar(50) DEFAULT NULL,
  `var_desc` varchar(50) DEFAULT NULL,
  `var_table` varchar(50) DEFAULT NULL,
  `var_column` varchar(50) DEFAULT NULL,
  `var_value` varchar(50) DEFAULT NULL,
  KEY `CONFIG_VARS_NDX` (`var_name`,`var_table`,`var_column`,`var_value`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_datanode_state`
--

DROP TABLE IF EXISTS `dr_datanode_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_datanode_state` (
  `entitykey` int(9) DEFAULT NULL,
  `sourcetime` datetime DEFAULT NULL,
  `updatetime` datetime DEFAULT NULL,
  `quality` decimal(22,0) DEFAULT NULL,
  `tagstatus` text DEFAULT NULL,
  `tagoutputinhibitstatus` text DEFAULT NULL,
  `taginputinhibitstatus` text DEFAULT NULL,
  `tagptw` text DEFAULT NULL,
  `ptwcomments` text DEFAULT NULL,
  `lastoperatorsessionid` text DEFAULT NULL,
  `lastoperatortimestamp` decimal(22,0) DEFAULT NULL,
  `notes` text DEFAULT NULL,
  `inhibitmms` int(1) DEFAULT NULL,
  UNIQUE KEY `DRDNS_01_UK` (`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_datapoint_data`
--

DROP TABLE IF EXISTS `dr_datapoint_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_datapoint_data` (
  `sourcedate` datetime DEFAULT NULL,
  `timeofday` decimal(22,0) DEFAULT NULL,
  `entitykey` int(9) DEFAULT NULL,
  `sourcetime` datetime DEFAULT NULL,
  `logtime` datetime DEFAULT NULL,
  `value` decimal(22,0) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_datapoint_date`
--

DROP TABLE IF EXISTS `dr_datapoint_date`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_datapoint_date` (
  `sourcedate` datetime NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_datapoint_state`
--

DROP TABLE IF EXISTS `dr_datapoint_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_datapoint_state` (
  `entitykey` int(9) DEFAULT NULL,
  `sourcetime` datetime DEFAULT NULL,
  `updatetime` datetime DEFAULT NULL,
  `quality` decimal(22,0) DEFAULT NULL,
  `manuallydressed` int(1) DEFAULT NULL,
  `manuallydressedvalue` text DEFAULT NULL,
  `overscalehialarmenabled` int(1) DEFAULT NULL,
  `hihialarmenabled` int(1) DEFAULT NULL,
  `hialarmenabled` int(1) DEFAULT NULL,
  `loalarmenabled` int(1) DEFAULT NULL,
  `loloalarmenabled` int(1) DEFAULT NULL,
  `overscaleloalarmenabled` int(1) DEFAULT NULL,
  `truealarmenable` int(1) DEFAULT NULL,
  `falsealarmenable` int(1) DEFAULT NULL,
  `controlstatus` text DEFAULT NULL,
  `controlinhibited` int(1) DEFAULT NULL,
  `alarminhibited` int(1) DEFAULT NULL,
  `mmsalarminhibited` int(1) DEFAULT NULL,
  `mmsalarmpreviouslyinhibited` int(1) DEFAULT NULL,
  `servicestate` varchar(3) DEFAULT NULL,
  `launchresultstring` text DEFAULT NULL,
  `currentcontrolrequest` text DEFAULT NULL,
  `lastoperatorsessionid` text DEFAULT NULL,
  `lastoperatortimestamp` decimal(22,0) DEFAULT NULL,
  `lastinputvalue` decimal(20,8) DEFAULT NULL,
  `accumulatedinputvalue` decimal(25,8) DEFAULT NULL,
  `correctionvalue` decimal(20,8) DEFAULT NULL,
  `derived_alarm_enable` varchar(256) DEFAULT NULL,
  `loalarmvalue` decimal(20,8) DEFAULT NULL,
  `hialarmvalue` decimal(20,8) DEFAULT NULL,
  `loloalarmvalue` decimal(20,8) DEFAULT NULL,
  `hihialarmvalue` decimal(20,8) DEFAULT NULL,
  `overscaleloalarmvalue` decimal(20,8) DEFAULT NULL,
  `overscalehialarmvalue` decimal(25,8) DEFAULT NULL,
  `value` varchar(100) DEFAULT NULL,
  UNIQUE KEY `DRPS_01_UK` (`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_event`
--

DROP TABLE IF EXISTS `dr_event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_event` (
  `sessionid` decimal(22,0) DEFAULT NULL,
  `jobseq_no` decimal(22,0) DEFAULT NULL,
  `job_step` decimal(22,0) DEFAULT NULL,
  `job_seconds` decimal(22,0) DEFAULT NULL,
  `action` varchar(10) DEFAULT NULL,
  `logtime` datetime DEFAULT NULL,
  `tablename` varchar(30) DEFAULT NULL,
  `iteration` decimal(22,0) DEFAULT NULL,
  `rowsadded` decimal(22,0) DEFAULT NULL,
  `description` varchar(2000) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_live_property`
--

DROP TABLE IF EXISTS `dr_live_property`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_live_property` (
  `drlp_typekey` int(9) NOT NULL,
  `drlp_category` varchar(30) NOT NULL,
  `drlp_name` varchar(30) NOT NULL,
  `drlp_identifier` varchar(10) DEFAULT NULL,
  `drlp_table` varchar(30) DEFAULT NULL,
  `drlp_column` varchar(30) DEFAULT NULL,
  `drlp_column_type` varchar(30) DEFAULT 'FLOAT',
  `drlp_eng_max` decimal(12,2) DEFAULT NULL,
  `drlp_eng_min` decimal(12,2) DEFAULT NULL,
  `drlp_status` varchar(10) DEFAULT 'PENDING',
  `interval_between_writes` decimal(22,0) DEFAULT '0',
  `min_summary_interval` decimal(22,0) DEFAULT '0',
  PRIMARY KEY (`drlp_typekey`,`drlp_category`,`drlp_name`),
  UNIQUE KEY `DRLP_UK` (`drlp_identifier`),
  KEY `DRLP_STATUS_IDX` (`drlp_status`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_pwrdmd_30min_table`
--

DROP TABLE IF EXISTS `dr_pwrdmd_30min_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_pwrdmd_30min_table` (
  `entitykey` decimal(22,0) NOT NULL,
  `entityname` varchar(85) DEFAULT NULL,
  `sourcedate` datetime NOT NULL,
  `int` decimal(22,0) NOT NULL,
  `tariff` decimal(22,0) NOT NULL,
  `demand` decimal(38,30) NOT NULL,
  `setpoint` decimal(22,0) DEFAULT NULL,
  `setpoint_name` varchar(85) DEFAULT NULL,
  `edited_demand` decimal(22,0) DEFAULT NULL,
  `week` datetime DEFAULT NULL,
  `weeknum` decimal(22,0) DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`entitykey`,`sourcedate`,`int`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_pwrdmd_config`
--

DROP TABLE IF EXISTS `dr_pwrdmd_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_pwrdmd_config` (
  `locationkey` decimal(22,0) NOT NULL,
  `location` varchar(20) DEFAULT NULL,
  `tariff` varchar(20) DEFAULT NULL,
  `setpoint` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`locationkey`)
  # , UNIQUE KEY `SYS_C008458` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_pwrdmd_data`
--

DROP TABLE IF EXISTS `dr_pwrdmd_data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_pwrdmd_data` (
  `entitykey` int(9) NOT NULL,
  `sourcedate` datetime NOT NULL,
  `consumption` decimal(22,0) NOT NULL,
  PRIMARY KEY (`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_trend_config`
--

DROP TABLE IF EXISTS `dr_trend_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_trend_config` (
  `dr_id` decimal(22,0) DEFAULT NULL,
  `dr_status` varchar(10) DEFAULT 'PENDING',
  `dr_type1` varchar(10) DEFAULT NULL,
  `dr_type2` varchar(5) DEFAULT NULL,
  `property_category` varchar(30) DEFAULT NULL,
  `property_name` varchar(30) DEFAULT NULL,
  `property_identifier` varchar(10) DEFAULT NULL,
  `interval` varchar(5) DEFAULT NULL,
  `interval_seconds` decimal(22,0) DEFAULT NULL,
  `source_name` varchar(30) DEFAULT NULL,
  `source_column` varchar(30) DEFAULT NULL,
  `interval_column` varchar(30) DEFAULT NULL,
  `icount_column` varchar(100) DEFAULT NULL,
  `iavg_column` varchar(100) DEFAULT NULL,
  `imin_column` varchar(100) DEFAULT NULL,
  `imax_column` varchar(100) DEFAULT NULL,
  `isum_column` varchar(100) DEFAULT NULL,
  `object_name` varchar(30) NOT NULL,
  `object_description` varchar(100) DEFAULT NULL,
  `object_select1` text DEFAULT NULL,
  `object_select2` text DEFAULT NULL,
  `object_job` text DEFAULT NULL,
  PRIMARY KEY (`object_name`),
  KEY `DRTC_PROPERTYID_IDX` (`property_identifier`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `dr_trend_interval`
--

DROP TABLE IF EXISTS `dr_trend_interval`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `dr_trend_interval` (
  `starttime` decimal(22,0) DEFAULT NULL,
  `endtime` decimal(22,0) DEFAULT NULL,
  `startminute` decimal(22,0) DEFAULT NULL,
  `startsecond` decimal(22,0) DEFAULT NULL,
  `endsecond` decimal(22,0) DEFAULT NULL,
  `int1min` decimal(22,0) DEFAULT NULL,
  `int2min` decimal(22,0) DEFAULT NULL,
  `int3min` decimal(22,0) DEFAULT NULL,
  `int4min` decimal(22,0) DEFAULT NULL,
  `int5min` decimal(22,0) DEFAULT NULL,
  `int6min` decimal(22,0) DEFAULT NULL,
  `int10min` decimal(22,0) DEFAULT NULL,
  `int12min` decimal(22,0) DEFAULT NULL,
  `int15min` decimal(22,0) DEFAULT NULL,
  `int20min` decimal(22,0) DEFAULT NULL,
  `int30min` decimal(22,0) DEFAULT NULL,
  `int40min` decimal(22,0) DEFAULT NULL,
  `int45min` decimal(22,0) DEFAULT NULL,
  `int1hrs` decimal(22,0) DEFAULT NULL,
  `int2hrs` decimal(22,0) DEFAULT NULL,
  `int3hrs` decimal(22,0) DEFAULT NULL,
  `int4hrs` decimal(22,0) DEFAULT NULL,
  `int6hrs` decimal(22,0) DEFAULT NULL,
  `int8hrs` decimal(22,0) DEFAULT NULL,
  `int12hrs` decimal(22,0) DEFAULT NULL,
  `int1day` decimal(22,0) DEFAULT NULL,
  UNIQUE KEY `DR_TREND_INT1MIN_UN` (`int1min`),
  KEY `DR_TREND_INT10MIN_NU` (`int10min`),
  KEY `DR_TREND_INT1MIN_NU` (`int1min`),
  KEY `DR_TREND_INT15MIN_NU` (`int15min`),
  KEY `DR_TREND_INT1HR_NU` (`int1hrs`),
  KEY `DR_TREND_INT30MIN_NU` (`int30min`),
  KEY `DR_TREND_INT3MIN_NU` (`int3min`),
  KEY `DR_TREND_INT40MIN_NU` (`int40min`),
  KEY `DR_TREND_INT45MIN_NU` (`int45min`),
  KEY `DR_TREND_INT4MIN_NU` (`int4min`),
  KEY `DR_TREND_INT5MIN_NU` (`int5min`),
  KEY `DR_TREND_INT6MIN_NU` (`int6min`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ec_master_mode`
--

DROP TABLE IF EXISTS `ec_master_mode`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ec_master_mode` (
  `ecmmod_id` int(9) NOT NULL,
  `master_mode` int(4) NOT NULL,
  `condition` varchar(40) NOT NULL,
  `eczone_id` int(9) DEFAULT NULL,
  `evacuation_direction` varchar(20) NOT NULL,
  `airflow_direction` varchar(20) NOT NULL,
  `display_direction` varchar(20) NOT NULL DEFAULT ' ',
  `verification_msg` varchar(40) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`ecmmod_id`),
  UNIQUE KEY `ECMMOD_UK` (`master_mode`),
  KEY `ECMMODE_AFDIRECT_IDX` (`airflow_direction`),
  KEY `ECMMODE_CONDITION_IDX` (`condition`),
  KEY `ECMMODE_DISPDIRECT_IDX` (`display_direction`),
  KEY `ECMMODE_ECZONEID_IDX` (`eczone_id`),
  KEY `ECMMODE_EVDIRECT_IDX` (`evacuation_direction`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ec_master_mode_helper`
--

DROP TABLE IF EXISTS `ec_master_mode_helper`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ec_master_mode_helper` (
  `ecmmhe_id` int(9) NOT NULL,
  `ecmmod_id` int(9) NOT NULL,
  `ecsmod_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`ecmmhe_id`),
  KEY `ECMMHE_ECMMOD_IDX` (`ecmmod_id`),
  KEY `ECMMHE_ECSMOD_IDX` (`ecsmod_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ec_station_colour`
--

DROP TABLE IF EXISTS `ec_station_colour`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ec_station_colour` (
  `ecscol_id` int(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `current_ecs_station_colour` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`ecscol_id`),
  UNIQUE KEY `ECSTATIONCOLOUR_NAME_IDX` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ec_station_mode`
--

DROP TABLE IF EXISTS `ec_station_mode`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ec_station_mode` (
  `ecsmod_id` int(9) NOT NULL,
  `station_mode` int(4) NOT NULL,
  `locationkey` int(9) NOT NULL DEFAULT '0',
  `operation` varchar(40) NOT NULL,
  `track` varchar(40) DEFAULT NULL,
  `condition` varchar(20) NOT NULL,
  `congestion_logic` varchar(1000) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`ecsmod_id`),
  KEY `ECSMODE_CONDITION_IDX` (`condition`),
  KEY `ECSMODE_CONGESTLOG_IDX` (`congestion_logic`(500)),
  KEY `ECSMODE_LOCATIONKEY_IDX` (`locationkey`),
  KEY `ECSMODE_OPERATION_IDX` (`operation`),
  KEY `ECSMODE_STNMODE_IDX` (`station_mode`),
  KEY `ECSMODE_TRACK_IDX` (`track`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ec_zone`
--

DROP TABLE IF EXISTS `ec_zone`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ec_zone` (
  `eczone_id` int(9) NOT NULL,
  `ecs_location` varchar(20) NOT NULL,
  `track` varchar(40) NOT NULL,
  `occ_equipment_entitykey` int(9) NOT NULL,
  `stn_equipment_entitykey` int(9) NOT NULL,
  `is_ignoring_congestion` varchar(1) NOT NULL DEFAULT 'N',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`eczone_id`),
  UNIQUE KEY `ECZONE_01_UK` (`occ_equipment_entitykey`),
  UNIQUE KEY `ECZONE_0_UK` (`stn_equipment_entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entity`
--

DROP TABLE IF EXISTS `entity`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entity` (
  `pkey` int(9) NOT NULL,
  `name` varchar(85) NOT NULL,
  `address` varchar(100) NOT NULL,
  `description` varchar(2000) NOT NULL,
  `subsystemkey` int(9) DEFAULT NULL,
  `locationkey` int(9) NOT NULL,
  `seregi_id` int(9) NOT NULL DEFAULT '0',
  `typekey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `scsdat_id` int(9) DEFAULT NULL,
  `parentkey` int(9) NOT NULL DEFAULT '0',
  `agentkey` int(9) NOT NULL DEFAULT '0',
  `deleted` int(9) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `ENTITY_NAME_UK` (`name`),
  KEY `ENTITY_AGENTKEY_IDX` (`agentkey`),
  KEY `ENTITY_DELETED_IDX` (`deleted`),
  KEY `ENTITY_LOCATIONKEY_IDX` (`locationkey`),
  KEY `ENTITY_PARENTKEY_IDX` (`parentkey`),
  KEY `ENTITY_PHYSICAL_IDX` (`physical_subsystem_key`),
  KEY `ENTITY_REGION_IDX` (`seregi_id`),
  KEY `ENTITY_SUBSYSTEMKEY_IDX` (`subsystemkey`),
  KEY `ENTITY_TYPEKEY_IDX` (`typekey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entity_seq_source`
--

DROP TABLE IF EXISTS `entity_seq_source`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entity_seq_source` (
  `stmnt` varchar(2000) DEFAULT NULL,
  `seq_name` varchar(30) NOT NULL,
  PRIMARY KEY (`seq_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entityparameter`
--

DROP TABLE IF EXISTS `entityparameter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entityparameter` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` text DEFAULT NULL,
  `typekey` int(9) NOT NULL,
  `order_seq` decimal(22,0) DEFAULT '10',
  `drivertypekey` int(9) NOT NULL,
  `ep_mandatory` varchar(1) NOT NULL,
  `ep_default` varchar(1024) DEFAULT NULL,
  `ep_default_datatype` int(3) NOT NULL,
  `ep_validation` varchar(1000) DEFAULT NULL,
  `visible` varchar(1) DEFAULT 'Y',
  `onlineupdate` varchar(1) DEFAULT 'N',
  `ec_field` varchar(30) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_ENTITYPARAMETER` (`pkey`),
  UNIQUE KEY `UK_ENTITYPARAMETER` (`name`,`typekey`),
  KEY `EP_DEFDATATYPE_IDX` (`ep_default_datatype`),
  KEY `EP_TYPEKEY_IDX` (`typekey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entityparameterdatatype`
--

DROP TABLE IF EXISTS `entityparameterdatatype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entityparameterdatatype` (
  `pkey` int(9) NOT NULL,
  `datatype` varchar(30) NOT NULL,
  PRIMARY KEY (`pkey`)
  # , UNIQUE KEY `PK_ENTITYPARAMETERDATATYPE` (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entityparametervalue`
--

DROP TABLE IF EXISTS `entityparametervalue`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entityparametervalue` (
  `pkey` int(9) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `parameterkey` int(9) NOT NULL,
  `value` varchar(2000) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_EPV` (`pkey`),
  UNIQUE KEY `U_EPV_EK_PK` (`entitykey`,`parameterkey`),
  KEY `EPV_ENTITYPARAMETER_IDX` (`parameterkey`),
  KEY `EPV_VALUE_IDX` (`value`(1024))
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entitystatusdata`
--

DROP TABLE IF EXISTS `entitystatusdata`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entitystatusdata` (
  `entitystatustype` int(9) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `statusdatatype` int(9) NOT NULL,
  `entitystatusvalue` varchar(1024) NOT NULL,
  `last_modified_session` varchar(38) NOT NULL,
  `last_modified_date` datetime NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`entitystatustype`,`entitykey`),
  KEY `STATUSDATA_ENTITYKEY_INDX` (`entitykey`),
  KEY `STATUSDATA_STATUSTYPE_INDX` (`entitystatustype`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entitytype`
--

DROP TABLE IF EXISTS `entitytype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entitytype` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `sys_site` int(1) NOT NULL DEFAULT '0',
  `description` varchar(2000) DEFAULT NULL,
  `default_parenttype` int(9) DEFAULT '0',
  `guiapplicationkey` int(9) NOT NULL,
  `ta_subsystemkey` int(9) NOT NULL DEFAULT '0',
  `name_tip` text DEFAULT NULL,
  `address_tip` text DEFAULT NULL,
  `description_tip` text DEFAULT NULL,
  `subsystem_tip` text DEFAULT NULL,
  `location_tip` text DEFAULT NULL,
  `parent_tip` text DEFAULT NULL,
  `executable_tip` text DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `ETYPE_01_UK` (`name`),
  KEY `ETYPE_TASUBSYS_IDX` (`ta_subsystemkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `entitytypeparent`
--

DROP TABLE IF EXISTS `entitytypeparent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `entitytypeparent` (
  `pkey` int(9) NOT NULL,
  `et_key` int(9) NOT NULL,
  `et_parentkey` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `ENTITYTYPEPARENT_KEYS_UK` (`et_key`,`et_parentkey`)
  # , UNIQUE KEY `PK_ENTITYTYPEPAR` (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `error_log`
--

DROP TABLE IF EXISTS `error_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `error_log` (
  `pkey` int(9) NOT NULL,
  `sql_statement` varchar(2000) NOT NULL,
  `error_message` varchar(2000) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`pkey`),
  KEY `ERRORLOG_TIMESTAMP_IDX` (`timestamp`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;



--
-- Table structure for table `ev_combined`
--

DROP TABLE IF EXISTS `ev_combined`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ev_combined` (
  `source_table` varchar(3) DEFAULT NULL,
  `pkey` decimal(22,0) DEFAULT NULL,
  `createdatetime` datetime DEFAULT NULL,
  `createtime` varchar(23) DEFAULT NULL,
  `subsystem_key` int(9) DEFAULT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `location_key` int(9) DEFAULT NULL,
  `severity_key` int(9) DEFAULT NULL,
  `severity_name` varchar(20) DEFAULT NULL,
  `asset_name` varchar(256) DEFAULT NULL,
  `description` varchar(1024) DEFAULT NULL,
  `event_type_key` int(9) DEFAULT NULL,
  `event_type_name` varchar(256) DEFAULT NULL,
  `alarm_id` varchar(38) DEFAULT NULL,
  `alarm_type_key` int(9) DEFAULT NULL,
  `value` varchar(512) DEFAULT NULL,
  `mms_state` varchar(100) DEFAULT NULL,
  `dss_state` varchar(30) DEFAULT NULL,
  `avl_state` varchar(100) DEFAULT NULL,
  `operator_key` int(9) DEFAULT NULL,
  `operator_name` varchar(85) DEFAULT NULL,
  `alarm_comment` text DEFAULT NULL,
  `event_level` int(1) DEFAULT NULL,
  `alarm_ack` varchar(38) DEFAULT NULL,
  `alarm_status` varchar(2) DEFAULT NULL,
  `session_key` varchar(38) DEFAULT NULL,
  `session_location` int(9) DEFAULT NULL,
  `profile_id` int(9) DEFAULT NULL,
  `action_id` int(9) DEFAULT NULL,
  `operation_mode` varchar(2) DEFAULT NULL,
  `entity_key` int(9) DEFAULT NULL,
  `avlalarmheadid` varchar(38) DEFAULT NULL,
  `system_key` int(9) DEFAULT NULL,
  # UNIQUE KEY `EVCOM_PKEY_INDX` (`pkey`),
  PRIMARY KEY (`pkey`),
  KEY `EVCOM_SUB_TIME_INDX` (`createtime`,`subsystem_key`,`physical_subsystem_key`,`action_id`),
  KEY `IND_EV_COMBINED_TIME` (`createdatetime`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `event`
--

DROP TABLE IF EXISTS `event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `event` (
  `pkey` decimal(22,0) NOT NULL,
  `message_id` varchar(38) NOT NULL,
  `createtime` varchar(23) NOT NULL,
  `logtime` varchar(23) NOT NULL,
  `description` varchar(1024) NOT NULL,
  `param_list` varchar(512) DEFAULT NULL,
  `details` varchar(1024) DEFAULT NULL,
  `eventtype` varchar(32) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `sessionkey` varchar(38) DEFAULT NULL,
  `alarm_id` varchar(38) DEFAULT NULL,
  `locationkey` int(9) DEFAULT NULL,
  `incident_id` varchar(38) DEFAULT NULL,
  `asset_name` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `EVENT_MESSAGE_IDX` (`message_id`),
  KEY `EVENT_ALARM_IDX` (`alarm_id`),
  KEY `EVENT_CREATETIME_IDX` (`createtime`),
  KEY `EVENT_INCIDENT_IDX` (`incident_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `eventcolour`
--

DROP TABLE IF EXISTS `eventcolour`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `eventcolour` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `open_acked_fg_colour1` int(9) NOT NULL,
  `open_acked_bg_colour1` int(9) NOT NULL,
  `open_unacked_fg_colour1` int(9) NOT NULL,
  `open_unacked_bg_colour1` int(9) NOT NULL,
  `closed_unacked_fg_colour1` int(9) NOT NULL,
  `closed_unacked_bg_colour1` int(9) NOT NULL,
  `closed_acked_fg_colour1` int(9) NOT NULL,
  `closed_acked_bg_colour1` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `EVENTCOLOUR_NAME_IDX` (`name`)
  # , UNIQUE KEY `PK_EVENTCOLOUR` (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `eventplanmaps`
--

DROP TABLE IF EXISTS `eventplanmaps`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `eventplanmaps` (
  `pkey` int(9) NOT NULL,
  `enabled` int(1) NOT NULL,
  `entitytypekey` int(9) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `eventtypekey` int(9) NOT NULL,
  `planpath` varchar(300) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  KEY `EVENTPLANMAPS_01_IDX` (`entitytypekey`,`entitykey`,`eventtypekey`),
  KEY `EVENTPLANMAPS_ENABLED_IDX` (`enabled`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `global_parameter`
--

DROP TABLE IF EXISTS `global_parameter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `global_parameter` (
  `gparam_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `name` varchar(85) NOT NULL,
  `value` varchar(512) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`gparam_id`),
  UNIQUE KEY `GPARAM_01_UK` (`subsystemkey`,`name`),
  KEY `GPARAM_NAME_IDX` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `guiapplication`
--

DROP TABLE IF EXISTS `guiapplication`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `guiapplication` (
  `pkey` int(9) NOT NULL,
  `name` varchar(50) NOT NULL,
  `fullname` varchar(50) NOT NULL,
  `executable` varchar(1024) NOT NULL,
  `maxinstances` int(1) NOT NULL,
  `reposition` int(1) NOT NULL,
  `passregisterparams` int(1) NOT NULL,
  `show_launch_icon` int(1) NOT NULL DEFAULT '1',
  `app_security_level` int(2) NOT NULL DEFAULT '0',
  `app_group` varchar(32) NOT NULL DEFAULT 'OTHER',
  `terminate_on_logout` int(1) NOT NULL DEFAULT '1',
  `help` varchar(1024) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `GLOBALAPP_NAME_IDX` (`name`),
  # UNIQUE KEY `PK_GUIAPPLICATION` (`pkey`),
  KEY `GLOBALAPP_FULLNAME_IDX` (`fullname`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `hist_config_full`
--

DROP TABLE IF EXISTS `hist_config_full`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hist_config_full` (
  `entitykey` int(9) DEFAULT NULL,
  `entityname` varchar(85) DEFAULT NULL,
  `tablename` text DEFAULT NULL,
  `datatype` text DEFAULT NULL,
  `timeperiod` text DEFAULT NULL,
  `basedata` text DEFAULT NULL,
  `procedurename` text DEFAULT NULL,
  `startofday` text DEFAULT NULL,
  `archiveflag` text DEFAULT NULL,
  `storagetime` text DEFAULT NULL,
  `basetable` text DEFAULT NULL,
  `basetimeperiod` text DEFAULT NULL,
  `basebasedata` text DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_base`
--

DROP TABLE IF EXISTS `history_base`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_base` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `status` varchar(6) DEFAULT NULL,
  `comms_error` int(9) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_data1`
--

DROP TABLE IF EXISTS `history_data1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_data1` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `pct_used` int(3) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_data2`
--

DROP TABLE IF EXISTS `history_data2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_data2` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `pct_used` int(3) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_data3`
--

DROP TABLE IF EXISTS `history_data3`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_data3` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `pct_used` int(3) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_data4`
--

DROP TABLE IF EXISTS `history_data4`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_data4` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `pct_used` int(3) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `history_data5`
--

DROP TABLE IF EXISTS `history_data5`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history_data5` (
  `timestamp` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` decimal(22,0) DEFAULT NULL,
  `pct_used` int(3) DEFAULT NULL,
  PRIMARY KEY (`timestamp`,`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `in_incident_report`
--

DROP TABLE IF EXISTS `in_incident_report`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `in_incident_report` (
  `ininci_id` varchar(38) NOT NULL,
  `title` varchar(100) DEFAULT NULL,
  `create_operat_id` int(9) NOT NULL,
  `create_seprof_id` int(9) NOT NULL,
  `create_date` datetime NOT NULL,
  `modify_operat_id` int(9) DEFAULT NULL,
  `modify_seprof_id` int(9) DEFAULT NULL,
  `modify_date` datetime DEFAULT NULL,
  `false_incident` int(1) NOT NULL DEFAULT '1',
  `entity_id` int(9) DEFAULT NULL,
  `locati_id_1` int(9) DEFAULT NULL,
  `locati_id_2` int(9) DEFAULT NULL,
  `train_id` varchar(10) DEFAULT NULL,
  `start_date` datetime DEFAULT NULL,
  `end_date` datetime DEFAULT NULL,
  `inner_track` int(1) NOT NULL DEFAULT '0',
  `outer_track` int(1) NOT NULL DEFAULT '0',
  `km_loss` int(9) DEFAULT NULL,
  `initial_delay` int(9) DEFAULT NULL,
  `total_delay` int(9) DEFAULT NULL,
  `alarm_id` varchar(38) DEFAULT NULL,
  `alarm_desc` varchar(500) DEFAULT NULL,
  `operators` varchar(500) DEFAULT NULL,
  `comments` varchar(1200) DEFAULT NULL,
  `recommendation` varchar(1200) DEFAULT NULL,
  `instat_id` varchar(38) DEFAULT NULL,
  `close_date` datetime DEFAULT NULL,
  `create_locati_id` int(9) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `alarm_value` varchar(100) DEFAULT NULL,
  `edit_operator_count` int(9) DEFAULT '0',
  PRIMARY KEY (`ininci_id`),
  KEY `ININCI_CRTOPRID_IDX` (`create_operat_id`),
  KEY `ININCI_CRTSEPROFID_IDX` (`create_seprof_id`),
  KEY `ININCI_ENTITYID_IDX` (`entity_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `in_plan`
--

DROP TABLE IF EXISTS `in_plan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `in_plan` (
  `inplan_id` varchar(38) NOT NULL,
  `ininci_id` varchar(38) NOT NULL,
  `plan_id` varchar(1024) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`inplan_id`),
  KEY `INPLAN_INCIDENT_IDX` (`ininci_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `in_report_access`
--

DROP TABLE IF EXISTS `in_report_access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `in_report_access` (
  `inracc_id` int(9) NOT NULL,
  `create_sepgro_id` int(9) NOT NULL,
  `access_sepgro_id` int(9) NOT NULL,
  `is_incident` int(1) NOT NULL,
  `access_level` int(1) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`inracc_id`),
  KEY `INREPO_ACCSEPGRO_IDX` (`access_sepgro_id`),
  KEY `INREPO_CRTSEPGRO_IDX` (`create_sepgro_id`),
  KEY `INREPO_ISINCIDENT_IDX` (`is_incident`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `in_station_report`
--

DROP TABLE IF EXISTS `in_station_report`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `in_station_report` (
  `instat_id` varchar(38) NOT NULL,
  `submitted_by` varchar(100) DEFAULT NULL,
  `ep` varchar(100) DEFAULT NULL,
  `incident_date` datetime DEFAULT NULL,
  `incident_closed_date` datetime DEFAULT NULL,
  `incident_type` varchar(11) DEFAULT NULL,
  `other_type` varchar(100) DEFAULT NULL,
  `location` varchar(4) DEFAULT NULL,
  `other_location` varchar(100) DEFAULT NULL,
  `cause` varchar(7) DEFAULT NULL,
  `other_cause` varchar(100) DEFAULT NULL,
  `condition` varchar(6) DEFAULT NULL,
  `other_condition` varchar(100) DEFAULT NULL,
  `action` varchar(500) DEFAULT NULL,
  `staff` varchar(500) DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL,
  `create_locati_id` int(9) DEFAULT NULL,
  `create_seprof_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`instat_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `index_tmp_sql`
--

DROP TABLE IF EXISTS `index_tmp_sql`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `index_tmp_sql` (
  `index_name` varchar(30) DEFAULT NULL,
  `index_sql` varchar(3000) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `key_map`
--

DROP TABLE IF EXISTS `key_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `key_map` (
  `org_key` decimal(22,0) DEFAULT NULL,
  `new_key` decimal(22,0) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lk_alias`
--

DROP TABLE IF EXISTS `lk_alias`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lk_alias` (
  `lkirul_id` int(9) NOT NULL,
  `alias` varchar(100) NOT NULL,
  `variable_name` varchar(100) NOT NULL,
  `variable_type` varchar(100) NOT NULL,
  UNIQUE KEY `LKINAL_01_UK` (`lkirul_id`,`variable_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lk_entity_types`
--

DROP TABLE IF EXISTS `lk_entity_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lk_entity_types` (
  `entity_type` varchar(30) NOT NULL,
  `dll_name` varchar(50) NOT NULL,
  UNIQUE KEY `LKENTY_UC_ENTY` (`entity_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lk_interlocking_rules`
--

DROP TABLE IF EXISTS `lk_interlocking_rules`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lk_interlocking_rules` (
  `lkirul_id` int(9) NOT NULL,
  `name` varchar(100) NOT NULL,
  `entity_key` int(9) NOT NULL,
  `entity_type` varchar(30) NOT NULL,
  `desired_state` varchar(85) NOT NULL,
  `parameters` varchar(1000) DEFAULT NULL,
  `precondition` varchar(1) NOT NULL,
  `condition` varchar(1000) NOT NULL,
  `description` varchar(500) DEFAULT NULL,
  `enabled` varchar(1) NOT NULL,
  PRIMARY KEY (`lkirul_id`),
  KEY `LKINTLOCKRULES_ENTITYKEY_IDX` (`entity_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lk_variable_types`
--

DROP TABLE IF EXISTS `lk_variable_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lk_variable_types` (
  `entity_type` varchar(30) NOT NULL,
  `dll_name` varchar(50) NOT NULL,
  `button_text` varchar(20) DEFAULT NULL,
  UNIQUE KEY `LKVRTY_UC_ENTY` (`entity_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `lo_datapt_state_change`
--

DROP TABLE IF EXISTS `lo_datapt_state_change`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `lo_datapt_state_change` (
  `ukey` decimal(22,0) NOT NULL,
  `lodsch_id` varchar(38) NOT NULL,
  `timestamp` datetime NOT NULL,
  `logtime` datetime NOT NULL,
  `entitykey` int(9) NOT NULL,
  `value` varchar(100) NOT NULL,
  `status` varchar(100) NOT NULL,
  `sessionkey` varchar(38) DEFAULT NULL,
  `alarmmessagekey` int(9) DEFAULT NULL,
  `generalmessagekey` int(9) DEFAULT NULL,
  `eventtypekey` int(9) DEFAULT NULL,
  PRIMARY KEY (`lodsch_id`),
  UNIQUE KEY `LODSCH_01_UK` (`ukey`),
  KEY `LODSCH_TIMESTAMP_IDX` (`timestamp`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `location`
--

DROP TABLE IF EXISTS `location`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `location` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` varchar(1024) NOT NULL,
  `order_id` int(9) DEFAULT NULL,
  `coline_id` int(9) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `LOC_NAME_UNIQUE` (`name`),
  # UNIQUE KEY `PK_LOCATION` (`pkey`),
  UNIQUE KEY `LOC_ORDER_UNIQUE` (`order_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `me_alarm_type`
--

DROP TABLE IF EXISTS `me_alarm_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `me_alarm_type` (
  `meatyp_id` int(9) NOT NULL,
  `type_name` varchar(255) NOT NULL,
  `type_description` varchar(256) DEFAULT NULL,
  `measev_id` int(9) NOT NULL,
  `print_alarm` int(1) NOT NULL DEFAULT '0',
  `system_alarm` int(1) NOT NULL DEFAULT '1',
  `persist_alarm` int(1) NOT NULL,
  `memcon_id` int(9) NOT NULL,
  `alarm_value` varchar(256) DEFAULT NULL,
  `normal_value` varchar(256) DEFAULT NULL,
  `mms_state` int(1) DEFAULT '0',
  `isvisible` int(1) NOT NULL DEFAULT '1',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `physical_alarm` decimal(22,0) DEFAULT '1',
  PRIMARY KEY (`meatyp_id`),
  UNIQUE KEY `MEATYP_UK` (`type_name`),
  KEY `MEATYP_MEMCONID_IDX` (`memcon_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `me_event_channel`
--

DROP TABLE IF EXISTS `me_event_channel`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `me_event_channel` (
  `meecha_id` int(9) NOT NULL,
  `channel_name` varchar(255) NOT NULL,
  PRIMARY KEY (`meecha_id`),
  UNIQUE KEY `UC_ME_EVENT_CHANNEL` (`channel_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `me_message_context`
--

DROP TABLE IF EXISTS `me_message_context`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `me_message_context` (
  `memcon_id` int(9) NOT NULL,
  `context_name` varchar(255) NOT NULL,
  `meecha_id` int(9) NOT NULL,
  PRIMARY KEY (`memcon_id`),
  UNIQUE KEY `UC_ME_MESSAGE_CONTEXT` (`context_name`),
  KEY `MEMCON_MEECHA_ID_IDX` (`meecha_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `me_message_type`
--

DROP TABLE IF EXISTS `me_message_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `me_message_type` (
  `memtyp_id` int(9) NOT NULL,
  `type_name` varchar(255) NOT NULL,
  `type_description` varchar(500) DEFAULT NULL,
  `priority` int(4) NOT NULL DEFAULT '0',
  `print_message` int(1) NOT NULL,
  `log_message` int(1) NOT NULL,
  `persist_message` int(1) NOT NULL DEFAULT '0',
  `view_level` int(1) NOT NULL DEFAULT '0',
  `memcon_id` int(9) NOT NULL,
  `isvisible` int(1) NOT NULL DEFAULT '1',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`memtyp_id`),
  UNIQUE KEY `MEMTYP_UK` (`type_name`),
  KEY `MEMTYP_ISVISIBLE_IDX` (`isvisible`),
  KEY `MEMTYP_MEMCON_ID_IDX` (`memcon_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `mm_scheduling`
--

DROP TABLE IF EXISTS `mm_scheduling`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `mm_scheduling` (
  `mmsche_id` int(9) NOT NULL,
  `physicalkey` int(9) NOT NULL,
  `time_of_day` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_sent` datetime NOT NULL,
  PRIMARY KEY (`mmsche_id`),
  UNIQUE KEY `MMSCHE_UK` (`physicalkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `msg`
--

DROP TABLE IF EXISTS `msg`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `msg` (
  `value` varchar(400) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `named_filter`
--

DROP TABLE IF EXISTS `named_filter`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `named_filter` (
  `operatorkey` int(9) NOT NULL,
  `applicationkey` int(9) NOT NULL,
  `filter_name` varchar(32) NOT NULL,
  `list_name` varchar(32) NOT NULL,
  `list_type` int(1) NOT NULL,
  `list_item` varchar(64) NOT NULL,
  KEY `NAMEFILTER_APPLICATIONKEY_IDX` (`applicationkey`),
  KEY `NAMEFILTER_FILTERNAME_IDX` (`filter_name`),
  KEY `NF_OP_APP_IDX` (`operatorkey`,`applicationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `naming_ports`
--

DROP TABLE IF EXISTS `naming_ports`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `naming_ports` (
  `entity_key` int(9) NOT NULL,
  `primary_port` int(9) DEFAULT NULL,
  `secondary_port` int(9) DEFAULT NULL,
  PRIMARY KEY (`entity_key`)
  # , UNIQUE KEY `SYS_C008766` (`entity_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `new_entityparametervalue`
--

DROP TABLE IF EXISTS `new_entityparametervalue`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `new_entityparametervalue` (
  `pkey` int(9) DEFAULT NULL,
  `entitykey` int(9) DEFAULT NULL,
  `parameterkey` int(9) DEFAULT NULL,
  `value` varchar(2000) DEFAULT NULL,
  `created_by` varchar(30) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `node_tree`
--

DROP TABLE IF EXISTS `node_tree`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `node_tree` (
  `p_key` int(6) NOT NULL,
  `fk_node_type` int(6) DEFAULT NULL,
  `parent_node` int(6) DEFAULT NULL,
  `name` varchar(150) NOT NULL,
  `description` varchar(2000) DEFAULT NULL,
  `fk_approval_state` int(6) DEFAULT NULL,
  `node_created_by` varchar(85) DEFAULT NULL,
  `node_modified_by` varchar(85) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `approval_modified_by` varchar(85) DEFAULT NULL,
  `approval_date_modified` datetime DEFAULT NULL,
  `edit_time_stamp` datetime DEFAULT NULL,
  `edit_lock_owner` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  UNIQUE KEY `PLNTRE_CHILD_NAME_UK` (`name`,`parent_node`),
  KEY `NODETREE_FKNODETYPE_IDX` (`fk_node_type`),
  KEY `NODETREE_PARENTNODE_IDX` (`parent_node`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `node_type`
--

DROP TABLE IF EXISTS `node_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `node_type` (
  `p_key` int(6) NOT NULL,
  `type_value` int(6) NOT NULL,
  `type_name` varchar(50) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  UNIQUE KEY `PLNTYP_01_UK` (`type_value`),
  UNIQUE KEY `PLNTYP_0_UK` (`type_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `online_printcfg`
--

DROP TABLE IF EXISTS `online_printcfg`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `online_printcfg` (
  `locationkey` int(9) NOT NULL,
  `def_printer` varchar(50) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`locationkey`)
  # , UNIQUE KEY `PK_ONLINE_PRINTCFG` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `online_printer`
--

DROP TABLE IF EXISTS `online_printer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `online_printer` (
  `pkey` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `printer` varchar(50) NOT NULL,
  `is_alarm` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `OPL_SUBSYS_UNIQUE` (`locationkey`,`subsystemkey`,`is_alarm`),
  # UNIQUE KEY `PK_ONLINE_PRINTER` (`pkey`),
  KEY `ONLINEPRINT_ISALARM_IDX` (`is_alarm`),
  KEY `ONLINEPRINT_SUBSYSKEY_IDX` (`subsystemkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `opc_dt_node`
--

DROP TABLE IF EXISTS `opc_dt_node`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `opc_dt_node` (
  `keyid` decimal(22,0) DEFAULT NULL,
  `pkeyid` decimal(22,0) DEFAULT NULL,
  `dt_node_name` varchar(100) DEFAULT NULL,
  `dt_node_desc` varchar(100) DEFAULT NULL,
  `data_pt_host` varchar(100) DEFAULT NULL,
  `disable` varchar(1) DEFAULT 'N',
  `data_pt_server` varchar(100) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `opc_dt_pt`
--

DROP TABLE IF EXISTS `opc_dt_pt`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `opc_dt_pt` (
  `keyid` decimal(22,0) NOT NULL,
  `data_pt_host` varchar(100) DEFAULT NULL,
  `data_pt_server` varchar(100) DEFAULT NULL,
  `data_pt_name` varchar(200) DEFAULT NULL,
  `data_pt_desc` varchar(100) DEFAULT NULL,
  `disable` varchar(1) DEFAULT 'Y',
  `pkeyid` decimal(22,0) NOT NULL,
  `sample_grp_id` decimal(22,0) DEFAULT NULL,
  UNIQUE KEY `OPC_DT_PT_U01` (`data_pt_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `opc_dt_sample_grp`
--

DROP TABLE IF EXISTS `opc_dt_sample_grp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `opc_dt_sample_grp` (
  `sample_grp_id` decimal(22,0) DEFAULT NULL,
  `sample_grp_name` varchar(50) DEFAULT NULL,
  `sample_grp_desc` varchar(100) DEFAULT NULL,
  `sample_interval` decimal(22,0) DEFAULT NULL,
  `interval_type` varchar(5) DEFAULT NULL,
  `start_time` varchar(10) DEFAULT NULL,
  `has_dt_pt` varchar(1) DEFAULT 'N',
  `disable` varchar(1) DEFAULT 'N',
  `delta_value` decimal(22,0) DEFAULT '0'
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `operator`
--

DROP TABLE IF EXISTS `operator`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `operator` (
  `pkey` int(9) NOT NULL,
  `name` varchar(85) NOT NULL,
  `passwd` varchar(50) NOT NULL,
  `accesslevel` int(9) NOT NULL DEFAULT '0',
  `description` varchar(80) NOT NULL,
  `is_system` int(1) NOT NULL DEFAULT '0',
  `deleted` int(9) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_OPERATOR` (`pkey`),
  UNIQUE KEY `UNIQUE_OPERATOR_DESC` (`description`),
  KEY `OPERATOR_DELETED_IDX` (`deleted`),
  KEY `OPERATOR_ISSYS_IDX` (`is_system`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_ats_triggered_broadcast`
--

DROP TABLE IF EXISTS `pa_ats_triggered_broadcast`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_ats_triggered_broadcast` (
  `paatbr_id` int(9) NOT NULL,
  `ats_event_type` int(2) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `dest_locationkey` int(9) NOT NULL,
  `platform_id` int(9) NOT NULL,
  `is_last_train` int(1) NOT NULL,
  `pazgro_id` int(9) NOT NULL,
  `padmes_id` int(9) NOT NULL,
  `dva_message_version` varchar(20) DEFAULT NULL,
  `is_enabled` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`paatbr_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_dva_message`
--

DROP TABLE IF EXISTS `pa_dva_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_dva_message` (
  `padmes_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `id` int(5) NOT NULL,
  `label` varchar(120) DEFAULT NULL,
  `type` char(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`padmes_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_dva_message_private_version`
--

DROP TABLE IF EXISTS `pa_dva_message_private_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_dva_message_private_version` (
  `padmprve_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `private_adhoc1` varchar(40) DEFAULT NULL,
  `private_adhoc2` varchar(40) DEFAULT NULL,
  `private_adhoc3` varchar(40) DEFAULT NULL,
  `private_adhoc4` varchar(40) DEFAULT NULL,
  `private_adhoc5` varchar(40) DEFAULT NULL,
  `private_adhoc6` varchar(40) DEFAULT NULL,
  `private_prerecorded` varchar(40) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`padmprve_id`),
  UNIQUE KEY `PADMPRVE_01_UK` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_dva_message_public_version`
--

DROP TABLE IF EXISTS `pa_dva_message_public_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_dva_message_public_version` (
  `padmpuve_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `public_adhoc1` varchar(40) DEFAULT NULL,
  `public_adhoc2` varchar(40) DEFAULT NULL,
  `public_adhoc3` varchar(40) DEFAULT NULL,
  `public_adhoc4` varchar(40) DEFAULT NULL,
  `public_adhoc5` varchar(40) DEFAULT NULL,
  `public_adhoc6` varchar(40) DEFAULT NULL,
  `public_prerecorded` varchar(40) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`padmpuve_id`),
  UNIQUE KEY `PADMPUVE_01_UK` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_dva_message_version`
--

DROP TABLE IF EXISTS `pa_dva_message_version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_dva_message_version` (
  `padmve_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `public_adhoc1` varchar(40) DEFAULT NULL,
  `public_adhoc2` varchar(40) DEFAULT NULL,
  `public_adhoc3` varchar(40) DEFAULT NULL,
  `public_adhoc4` varchar(40) DEFAULT NULL,
  `public_adhoc5` varchar(40) DEFAULT NULL,
  `public_adhoc6` varchar(40) DEFAULT NULL,
  `public_prerecorded` varchar(40) DEFAULT NULL,
  `private_adhoc1` varchar(40) DEFAULT NULL,
  `private_adhoc2` varchar(40) DEFAULT NULL,
  `private_adhoc3` varchar(40) DEFAULT NULL,
  `private_adhoc4` varchar(40) DEFAULT NULL,
  `private_adhoc5` varchar(40) DEFAULT NULL,
  `private_adhoc6` varchar(40) DEFAULT NULL,
  `private_prerecorded` varchar(40) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`padmve_id`),
  UNIQUE KEY `PADMVE_01_UK` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_station`
--

DROP TABLE IF EXISTS `pa_station`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_station` (
  `pastat_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pastat_id`),
  UNIQUE KEY `PASTAT_01_UK` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_tis_message_map`
--

DROP TABLE IF EXISTS `pa_tis_message_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_tis_message_map` (
  `pkey` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `id` int(5) NOT NULL,
  `tis_message_tag` decimal(22,0) DEFAULT NULL,
  `tis_library_section` decimal(22,0) DEFAULT NULL,
  `tis_library_version` decimal(22,0) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `PATMMAP_01_UK` (`locationkey`,`id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_train_dva_message`
--

DROP TABLE IF EXISTS `pa_train_dva_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_train_dva_message` (
  `patdme_id` int(9) NOT NULL,
  `label` varchar(40) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`patdme_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_zone`
--

DROP TABLE IF EXISTS `pa_zone`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_zone` (
  `pazone_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `id` int(5) NOT NULL,
  `label` varchar(256) NOT NULL,
  `stn_equipment` varchar(85) DEFAULT NULL,
  `occ_equipment` varchar(85) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pazone_id`),
  UNIQUE KEY `PAZONE_03_UK` (`locationkey`,`id`),
  UNIQUE KEY `PAZONE_01_UK` (`stn_equipment`),
  UNIQUE KEY `PAZONE_0_UK` (`occ_equipment`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_zone_group`
--

DROP TABLE IF EXISTS `pa_zone_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_zone_group` (
  `pazgro_id` bigint(12) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `label` varchar(40) NOT NULL,
  `is_event_group` int(1) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pazgro_id`),
  UNIQUE KEY `PAZGRO_01_UK` (`locationkey`,`label`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_zone_group_helper`
--

DROP TABLE IF EXISTS `pa_zone_group_helper`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_zone_group_helper` (
  `pazghe_id` bigint(12) NOT NULL,
  `pazone_id` int(9) NOT NULL,
  `pazgro_id` bigint(12) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pazghe_id`),
  UNIQUE KEY `PAZGHE_01_UK` (`pazone_id`,`pazgro_id`),
  KEY `PAZGHE_PAZGROID_IDX` (`pazgro_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pa_zone_helper`
--

DROP TABLE IF EXISTS `pa_zone_helper`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pa_zone_helper` (
  `pazhel_id` int(9) NOT NULL,
  `pid_zone_equipment` varchar(100) NOT NULL,
  `pazone_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pazhel_id`),
  UNIQUE KEY `PAZHEL_01_UK` (`pazone_id`,`pid_zone_equipment`),
  KEY `PAZHEL_PIDZONEEQP_IDX` (`pid_zone_equipment`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `parameter_type`
--

DROP TABLE IF EXISTS `parameter_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `parameter_type` (
  `p_key` int(6) NOT NULL,
  `type_value` int(6) NOT NULL,
  `type_name` varchar(50) NOT NULL,
  `constraint_table` varchar(50) DEFAULT NULL,
  `constraint_column` varchar(50) DEFAULT NULL,
  `constraint_query` varchar(50) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `patch_log`
--
DROP TABLE IF EXISTS `patch_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE  `patch_log` (
  `PATCH_NAME` varchar(100) DEFAULT NULL,
  `TIME_PATCHED` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pctable`
--

DROP TABLE IF EXISTS `pctable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pctable` (
  `pkey` decimal(22,0) DEFAULT NULL,
  `p_id` decimal(22,0) DEFAULT NULL,
  `p_name` varchar(30) NOT NULL,
  `p_col_name` varchar(1000) DEFAULT NULL,
  `c_id` decimal(22,0) DEFAULT NULL,
  `c_name` varchar(30) NOT NULL,
  `c_col_name` varchar(1000) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `printable_event`
--

DROP TABLE IF EXISTS `printable_event`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `printable_event` (
  `pkey` decimal(22,0) NOT NULL,
  `alarm_id` varchar(38) DEFAULT NULL,
  `event_id` decimal(22,0) DEFAULT NULL,
  `printer` varchar(64) NOT NULL,
  `alarmflag` varchar(20) DEFAULT NULL,
  `createtime` varchar(32) NOT NULL,
  `severity` varchar(20) DEFAULT NULL,
  `asset` varchar(256) DEFAULT NULL,
  `description` text DEFAULT NULL,
  `value` varchar(2000) DEFAULT NULL,
  `mms` varchar(100) DEFAULT NULL,
  `dss` varchar(30) DEFAULT NULL,
  `avalanche` varchar(100) DEFAULT NULL,
  `operatorname` varchar(85) DEFAULT NULL,
  `alarm_comment` text DEFAULT NULL,
  `alm` varchar(10) DEFAULT NULL,
  `location_key` int(9) NOT NULL,
  UNIQUE KEY `PRTEV_01_IDX` (`pkey`),
  KEY `PRTEV_0_IDX` (`location_key`),
  KEY `PRTEV_03_IDX` (`alarm_id`),
  KEY `PRTEV_04_IDX` (`event_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `pwr_dmd_log`
--

DROP TABLE IF EXISTS `pwr_dmd_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pwr_dmd_log` (
  `v_oldtime` datetime DEFAULT NULL,
  `v_newtime` datetime DEFAULT NULL,
  `v_entityname` varchar(85) DEFAULT NULL,
  `v_value` decimal(22,0) DEFAULT NULL,
  `v_quality` decimal(22,0) DEFAULT NULL,
  `v_demand` decimal(22,0) DEFAULT NULL,
  `v_tariff` decimal(22,0) DEFAULT NULL,
  `v_setpoint` decimal(22,0) DEFAULT NULL,
  `v_setpointname` varchar(85) DEFAULT NULL,
  `v_int` decimal(22,0) DEFAULT NULL,
  `v_old` decimal(22,0) DEFAULT NULL,
  `v_new` decimal(22,0) DEFAULT NULL,
  `v_counter` decimal(22,0) DEFAULT NULL,
  `v_loop` decimal(22,0) DEFAULT NULL,
  `v_diff` decimal(22,0) DEFAULT NULL,
  `v_head` decimal(22,0) DEFAULT NULL,
  `v_end` decimal(22,0) DEFAULT NULL,
  `v_demandpersecond` decimal(22,0) DEFAULT NULL,
  `v_head_demand` decimal(22,0) DEFAULT NULL,
  `v_end_demand` decimal(22,0) DEFAULT NULL,
  `my_demand` decimal(22,0) DEFAULT NULL,
  `v_time` datetime DEFAULT NULL,
  `v_newint` decimal(22,0) DEFAULT NULL,
  `old_value` decimal(22,0) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_btncfg`
--

DROP TABLE IF EXISTS `ra_btncfg`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_btncfg` (
  `PKEY` int(9) NOT NULL,
  `OPERATOR_PROFILE` int(9) DEFAULT NULL,
  `BUTTONREF` int(3) DEFAULT NULL,
  `RESOURCE_TYPE` varchar(1)  DEFAULT NULL,
  `RESOURCE_ID` int(9) DEFAULT NULL,
  `IS_PROFILE` int(1) DEFAULT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_call_stack_history`
--

DROP TABLE IF EXISTS `ra_call_stack_history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_call_stack_history` (
  `racshi_id` int(9) NOT NULL,
  `profile_name` varchar(85) NOT NULL,
  `location_key` int(9) NOT NULL,
  `timestamp` datetime NOT NULL,
  `origin` char(1) NOT NULL,
  `call_type` char(1) NOT NULL,
  `identifier` varchar(32) DEFAULT NULL,
  `location` varchar(80) DEFAULT NULL,
  `isemergency` int(1) DEFAULT NULL,
  PRIMARY KEY (`racshi_id`),
  KEY `RACSHI_IE` (`profile_name`,`location_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_directory_entry`
--

DROP TABLE IF EXISTS `ra_directory_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_directory_entry` (
  `PKEY` int(9) NOT NULL,
  `OWNER` int(9) DEFAULT NULL,
  `CATEGORY` int(9) DEFAULT NULL,
  `NAME` varchar(20)  DEFAULT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_directory_member`
--

DROP TABLE IF EXISTS `ra_directory_member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_directory_member` (
  `PARENT` int(9) NOT NULL,
  `RESOURCE_TYPE` varchar(1) NOT NULL,
  `RESOURCE_ID` int(9) NOT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_group_members`
--

DROP TABLE IF EXISTS `ra_group_members`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_group_members` (
  `ragmem_id` int(8) NOT NULL,
  `group_rasubs_id` varchar(32) NOT NULL,
  `member_rasubs_id` varchar(32) NOT NULL,
  PRIMARY KEY (`ragmem_id`),
  UNIQUE KEY `RAGMEM_UK` (`group_rasubs_id`,`member_rasubs_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_itsi_group`
--

DROP TABLE IF EXISTS `ra_itsi_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_itsi_group` (
  `raigro_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`raigro_id`),
  UNIQUE KEY `RAIGRO_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_patch_members`
--

DROP TABLE IF EXISTS `ra_patch_members`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_patch_members` (
  `rapmem_id` int(8) NOT NULL,
  `patch_rasubs_id` varchar(32) NOT NULL,
  `group_rasubs_id` varchar(32) NOT NULL,
  PRIMARY KEY (`rapmem_id`),
  UNIQUE KEY `RAPMEM_UK` (`patch_rasubs_id`,`group_rasubs_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_predefined_sds_messages`
--

DROP TABLE IF EXISTS `ra_predefined_sds_messages`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_predefined_sds_messages` (
  `short_name` varchar(50) NOT NULL,
  `message` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`short_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_predefined_textmessage`
--

DROP TABLE IF EXISTS `ra_predefined_textmessage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_predefined_textmessage` (
  `PKEY` int(9) NOT NULL,
  `OPERATOR` int(9) DEFAULT NULL,
  `TYPE` int(1) NOT NULL,
  `SHORT_NAME` varchar(20)  DEFAULT NULL,
  `MESSAGETEXT` varchar(140)  DEFAULT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_selected_calls`
--

DROP TABLE IF EXISTS `ra_selected_calls`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_selected_calls` (
  `rasc_id` int(9) DEFAULT NULL,
  `mft_name` varchar(85) DEFAULT NULL,
  `tetra_id` varchar(85) DEFAULT NULL,
  `call_id` varchar(85) DEFAULT NULL,
  `location` varchar(85) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_speed_dial_button`
--

DROP TABLE IF EXISTS `ra_speed_dial_button`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_speed_dial_button` (
  `rasdbu_id` int(8) NOT NULL,
  `rasdse_id` int(8) DEFAULT NULL,
  `button_position` int(3) NOT NULL,
  `button_label` varchar(30) DEFAULT NULL,
  `button_tsi` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`rasdbu_id`),
  UNIQUE KEY `RASDBU_01_IDX` (`rasdse_id`,`button_position`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_speed_dial_set`
--

DROP TABLE IF EXISTS `ra_speed_dial_set`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_speed_dial_set` (
  `rasdse_id` int(8) NOT NULL,
  `is_system` int(1) NOT NULL,
  `operator_key` int(9) DEFAULT NULL,
  `seprof_id` int(9) DEFAULT NULL,
  `set_name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`rasdse_id`),
  UNIQUE KEY `RASDSE_IDX` (`set_name`),
  KEY `RASPEEDDIALSET_SEPROFID_IDX` (`seprof_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_subscriber`
--

DROP TABLE IF EXISTS `ra_subscriber`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_subscriber` (
  `PKEY` int(9) NOT NULL,
  `OWNER_FLAG` varchar(1)  DEFAULT '0',
  `OWNER` int(9) DEFAULT '0',
  `RESOURCE_TYPE` varchar(1) NOT NULL,
  `RESOURCE_ID` int(9) NOT NULL,
  `SSI` int(9) NOT NULL,
  `ALIAS` varchar(14) NOT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_subscribers`
--

DROP TABLE IF EXISTS `ra_subscribers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_subscribers` (
  `rasubs_id` varchar(32) NOT NULL,
  `subscriber_name` varchar(32) DEFAULT NULL,
  `location` varchar(32) DEFAULT NULL,
  `subscriber_type` varchar(1) NOT NULL,
  `location_key` int(9) DEFAULT NULL,
  `owner` varchar(32) DEFAULT NULL,
  PRIMARY KEY (`rasubs_id`),
  KEY `RASUBS_IE` (`subscriber_name`),
  KEY `RASUBS_SUBTYPE_IDX` (`subscriber_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_textmessage_inbox`
--

DROP TABLE IF EXISTS `ra_textmessage_inbox`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_textmessage_inbox` (
  `PKEY` int(9) NOT NULL,
  `TIMESTAMP` date DEFAULT NULL,
  `OPERATOR` int(9) DEFAULT NULL,
  `IS_READ` varchar(1)  DEFAULT NULL,
  `MESSAGETEXT` varchar(140)  DEFAULT NULL,
  `ALIAS` varchar(30)  DEFAULT NULL,
  `CREATED_BY` varchar(30) NOT NULL,
  `DATE_CREATED` date NOT NULL,
  `MODIFIED_BY` varchar(30)  DEFAULT NULL,
  `DATE_MODIFIED` date DEFAULT NULL,
  `RECIPIENTCONSOLE` varchar(30)  DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ra_zone`
--

DROP TABLE IF EXISTS `ra_zone`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ra_zone` (
  `razone_id` int(9) NOT NULL,
  `radio_location` varchar(20) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`razone_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `recipient`
--

DROP TABLE IF EXISTS `recipient`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `recipient` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `address` varchar(1024) DEFAULT NULL,
  `db_link_name` varchar(40) DEFAULT NULL,
  `status` decimal(22,0) DEFAULT '0',
  `timeout` decimal(22,0) DEFAULT '0',
  PRIMARY KEY (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `recipient_all`
--

DROP TABLE IF EXISTS `recipient_all`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `recipient_all` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `member` varchar(30) NOT NULL,
  `db_link_name` varchar(40) NOT NULL,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT NULL,
  UNIQUE KEY `RECIPIENT_UNIQUE` (`name`,`member`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `recipient_group`
--

DROP TABLE IF EXISTS `recipient_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `recipient_group` (
  `pkey` int(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `member` varchar(30) NOT NULL,
  `db_link_name` varchar(40) NOT NULL,
  `status` int(1) NOT NULL,
  `timeout` decimal(22,0) DEFAULT '0',
  PRIMARY KEY (`pkey`,`name`,`member`,`db_link_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `s_p`
--

DROP TABLE IF EXISTS `s_p`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `s_p` (
  `subsystemkey` int(9) DEFAULT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_calculated_input_rule`
--

DROP TABLE IF EXISTS `sc_calculated_input_rule`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_calculated_input_rule` (
  `scciru_id` int(9) NOT NULL,
  `label` varchar(50) NOT NULL,
  `rule` varchar(512) NOT NULL,
  PRIMARY KEY (`scciru_id`),
  UNIQUE KEY `SCCIRU_0_UK` (`rule`(255)),
  UNIQUE KEY `SCCIRU_03_UK` (`label`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_derived_output_asso_2lv`
--

DROP TABLE IF EXISTS `sc_derived_output_asso_2lv`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_derived_output_asso_2lv` (
  `scdoas_id` int(9) DEFAULT NULL,
  `scdsta_id` int(9) NOT NULL,
  `output_dp_pkey` int(9) NOT NULL,
  `output_value` int(8) NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_derived_output_association`
--

DROP TABLE IF EXISTS `sc_derived_output_association`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_derived_output_association` (
  `scdoas_id` int(9) NOT NULL,
  `scdsta_id` int(9) NOT NULL,
  `output_dp_pkey` int(9) NOT NULL,
  `output_value` int(8) NOT NULL,
  PRIMARY KEY (`scdoas_id`),
  UNIQUE KEY `SCDOAS_01_UK` (`scdsta_id`,`output_dp_pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_derived_state`
--

DROP TABLE IF EXISTS `sc_derived_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_derived_state` (
  `scdsta_id` int(9) NOT NULL,
  `derived_dp_pkey` int(9) NOT NULL,
  `state_value` int(8) NOT NULL,
  `state_description` varchar(250) NOT NULL,
  `state_return_condition` varchar(250) NOT NULL DEFAULT ' ',
  `alarm_enabled` int(1) DEFAULT NULL,
  `alarm_delay` int(8) DEFAULT NULL,
  `alarm_message` varchar(250) DEFAULT NULL,
  `alarm_mms` varchar(250) DEFAULT NULL,
  `alarm_severity` int(8) DEFAULT NULL,
  PRIMARY KEY (`scdsta_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_derived_state_2lv`
--

DROP TABLE IF EXISTS `sc_derived_state_2lv`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_derived_state_2lv` (
  `scdsta_id` int(9) DEFAULT NULL,
  `derived_dp_pkey` int(9) NOT NULL,
  `state_value` int(8) NOT NULL,
  `state_description` varchar(250) NOT NULL,
  `state_return_condition` varchar(250) NOT NULL,
  `alarm_enabled` int(1) DEFAULT NULL,
  `alarm_delay` int(8) DEFAULT NULL,
  `alarm_message` varchar(250) DEFAULT NULL,
  `alarm_mms` varchar(250) DEFAULT NULL,
  `alarm_severity` int(8) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_equip_report`
--

DROP TABLE IF EXISTS `sc_equip_report`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_equip_report` (
  `scerep_id` varchar(38) NOT NULL,
  `report_name` varchar(80) NOT NULL,
  `location_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `report_type_filter_flag` int(1) DEFAULT '0',
  `report_type_filter` varchar(80) DEFAULT NULL,
  `asset_filter_flag` int(1) DEFAULT '0',
  `asset_filter` varchar(80) DEFAULT NULL,
  `desc_filter_flag` int(1) DEFAULT '0',
  `desc_filter` varchar(80) DEFAULT NULL,
  `dpname_filter_flag` int(1) DEFAULT '0',
  `dpname_filter` varchar(80) DEFAULT NULL,
  `dptype_filter_flag` int(1) DEFAULT '0',
  `dptype_filter` varchar(80) DEFAULT NULL,
  `dpvalue_filter_flag` int(1) DEFAULT '0',
  `dpvalue_filter` varchar(80) DEFAULT NULL,
  `status_filter_flag` int(1) DEFAULT '0',
  `scan_inhibit_flag` int(1) DEFAULT '0',
  `alarm_inhibit_flag` int(1) DEFAULT '0',
  `control_inhibit_flag` int(1) DEFAULT '0',
  `mms_inhibit_flag` int(1) DEFAULT '0',
  `tagged_flag` int(1) DEFAULT '0',
  `tagged_ptw_flag` int(1) DEFAULT '0',
  `overridden_flag` int(1) DEFAULT '0',
  `status_change_by_filter_flag` int(1) DEFAULT '0',
  `status_change_by_filter` varchar(80) DEFAULT NULL,
  `timestamp_filter_flag` int(1) DEFAULT '0',
  `timestamp_filter` varchar(80) DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `profile` int(9) DEFAULT NULL,
  PRIMARY KEY (`scerep_id`),
  UNIQUE KEY `SCEQUIPREPORT_REPNAME_IDX` (`report_name`,`location_id`),
  KEY `SCEQUIPREPORT_LOCATION_IDX` (`location_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_equip_report_entities`
--

DROP TABLE IF EXISTS `sc_equip_report_entities`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_equip_report_entities` (
  `sceren_id` varchar(38) NOT NULL,
  `scerep_id` varchar(38) NOT NULL,
  `datanode_id` int(9) DEFAULT '0',
  `datapoint_id` int(9) DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`sceren_id`),
  KEY `SCEQREPENTI_DATANODEID_IDX` (`datanode_id`),
  KEY `SCEQREPENTI_DATAPOINTID_IDX` (`datapoint_id`),
  KEY `SCEQREPENTI_SCEREPID_IDX` (`scerep_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_input_association`
--

DROP TABLE IF EXISTS `sc_input_association`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_input_association` (
  `sciass_id` int(9) NOT NULL,
  `main_entity_pkey` int(9) NOT NULL,
  `input_entity_pkey` int(9) NOT NULL,
  `input_calc_order` int(2) NOT NULL DEFAULT '0',
  `predefined_input_value` decimal(8,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`sciass_id`),
  UNIQUE KEY `SCIASS_01_UK` (`main_entity_pkey`,`input_entity_pkey`,`input_calc_order`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_input_association_2lv`
--

DROP TABLE IF EXISTS `sc_input_association_2lv`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_input_association_2lv` (
  `sciass_id` int(9) DEFAULT NULL,
  `main_entity_pkey` int(9) NOT NULL,
  `input_entity_pkey` int(9) NOT NULL,
  `input_calc_order` int(2) NOT NULL,
  `predefined_input_value` decimal(8,2) NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_opc_tag_alias`
--

DROP TABLE IF EXISTS `sc_opc_tag_alias`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_opc_tag_alias` (
  `scotal_id` int(9) NOT NULL,
  `alias` varchar(85) NOT NULL,
  `entity_id_dp` int(9) NOT NULL,
  `attribute_dp` varchar(85) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`scotal_id`),
  UNIQUE KEY `SCOTAL_0_UK` (`alias`),
  KEY `SCOTAL_ENTITYID_IDX` (`entity_id_dp`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_scada_datatypes`
--

DROP TABLE IF EXISTS `sc_scada_datatypes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_scada_datatypes` (
  `scsdat_id` int(9) NOT NULL,
  `name` varchar(20) NOT NULL,
  `prefix` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`scsdat_id`),
  UNIQUE KEY `SCSDAT_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sc_scada_schematic`
--

DROP TABLE IF EXISTS `sc_scada_schematic`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sc_scada_schematic` (
  `scssch_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `path` varchar(1024) NOT NULL,
  `coloca_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`scssch_id`),
  UNIQUE KEY `SCSSCH_01_UK` (`name`),
  KEY `SCSCADASCHE_COLOCAID_IDX` (`coloca_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_action`
--

DROP TABLE IF EXISTS `se_action`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_action` (
  `seacti_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` varchar(500) DEFAULT NULL,
  `entitytypekey` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `memtyp_id` int(9) DEFAULT NULL,
  PRIMARY KEY (`seacti_id`),
  UNIQUE KEY `SEACTI_UK` (`name`),
  KEY `SE_ACTION_MEMTYP_ID_INDX` (`memtyp_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_action_group`
--

DROP TABLE IF EXISTS `se_action_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_action_group` (
  `seagro_id` int(9) NOT NULL,
  `name` varchar(255) NOT NULL,
  `is_controltype` int(1) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seagro_id`),
  UNIQUE KEY `ACTGRO_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_action_group_map`
--

DROP TABLE IF EXISTS `se_action_group_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_action_group_map` (
  `seacti_id` int(9) NOT NULL,
  `seagro_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seacti_id`,`seagro_id`),
  KEY `SE_ACTGROUP_MAP_SEACTI_ID_INDX` (`seacti_id`),
  KEY `SE_ACTGROUP_MAP_SEAGRO_ID_INDX` (`seagro_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_operator_profile`
--

DROP TABLE IF EXISTS `se_operator_profile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_operator_profile` (
  `seopro_id` int(9) NOT NULL,
  `operatorkey` int(9) NOT NULL,
  `seprof_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seopro_id`),
  KEY `SEOPRO_IDX` (`operatorkey`),
  KEY `SEOPRO_SEPROF_IDX` (`seprof_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_operator_profile_bak`
--

DROP TABLE IF EXISTS `se_operator_profile_bak`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_operator_profile_bak` (
  `seopro_id` int(9) DEFAULT NULL,
  `operatorkey` int(9) DEFAULT NULL,
  `seprof_id` int(9) DEFAULT NULL,
  `created_by` varchar(30) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_operator_regions`
--

DROP TABLE IF EXISTS `se_operator_regions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_operator_regions` (
  `seoreg_id` int(9) NOT NULL,
  `operatorkey` int(9) NOT NULL,
  `seregi_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seoreg_id`),
  KEY `SEOREG_IDX` (`operatorkey`),
  KEY `SEOREG_SEREGI_IDX` (`seregi_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile`
--

DROP TABLE IF EXISTS `se_profile`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile` (
  `seprof_id` int(9) NOT NULL,
  `name` varchar(85) NOT NULL,
  `septyp_id` int(9) NOT NULL DEFAULT '0',
  `sepgro_id` int(9) NOT NULL DEFAULT '0',
  `raigro_id` int(9) DEFAULT NULL,
  `is_system` int(1) NOT NULL DEFAULT '0',
  `deleted` int(9) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `consolemode` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`seprof_id`),
  UNIQUE KEY `SEPROF_UK` (`name`),
  KEY `SEPROFILE_DELETED_IDX` (`deleted`),
  KEY `SEPROFILE_ISSYS_IDX` (`is_system`),
  KEY `SEPROFILE_RAIGROID_IDX` (`raigro_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_access`
--

DROP TABLE IF EXISTS `se_profile_access`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_access` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `sessta_id` int(9) NOT NULL DEFAULT '0',
  `seagro_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seprof_id`,`subsystemkey`,`sessta_id`),
  KEY `SEPACC_SEAGRO_ID_INDX` (`seagro_id`),
  KEY `SEPACC_SESSTAID_IDX` (`sessta_id`),
  KEY `SEPACC_SUBSYS_KEY_INDX` (`subsystemkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_bak`
--

DROP TABLE IF EXISTS `se_profile_bak`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_bak` (
  `seprof_id` int(9) DEFAULT NULL,
  `name` varchar(85) DEFAULT NULL,
  `septyp_id` int(9) DEFAULT NULL,
  `sepgro_id` int(9) DEFAULT NULL,
  `raigro_id` int(9) DEFAULT NULL,
  `is_system` int(1) DEFAULT NULL,
  `deleted` int(9) DEFAULT NULL,
  `created_by` varchar(30) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `consolemode` varchar(20) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_group`
--

DROP TABLE IF EXISTS `se_profile_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_group` (
  `sepgro_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`sepgro_id`),
  UNIQUE KEY `SEPGRO_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_location`
--

DROP TABLE IF EXISTS `se_profile_location`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_location` (
  `seprof_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  PRIMARY KEY (`seprof_id`,`locationkey`),
  KEY `SEPLOC_IDX` (`locationkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_parameters`
--

DROP TABLE IF EXISTS `se_profile_parameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_parameters` (
  `seprof_id` int(9) NOT NULL,
  `locationkey` int(9) NOT NULL,
  `display_1` int(9) NOT NULL,
  `display_2` int(9) DEFAULT NULL,
  `display_3` int(9) DEFAULT NULL,
  `left_banner` varchar(50) NOT NULL,
  `centre_banner` varchar(50) DEFAULT NULL,
  `right_banner` varchar(50) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seprof_id`,`locationkey`),
  KEY `SEPP_DISP1_IDX` (`display_1`),
  KEY `SEPP_DISP3_IDX` (`display_3`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_profile_type`
--

DROP TABLE IF EXISTS `se_profile_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_profile_type` (
  `septyp_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `is_exclusive` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`septyp_id`),
  UNIQUE KEY `SEPTYP_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_region`
--

DROP TABLE IF EXISTS `se_region`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_region` (
  `seregi_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` varchar(1024) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`seregi_id`),
  UNIQUE KEY `SEREGI_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `se_subsystem_state`
--

DROP TABLE IF EXISTS `se_subsystem_state`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `se_subsystem_state` (
  `sessta_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` varchar(1024) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`sessta_id`),
  UNIQUE KEY `SESSTA_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sh_job`
--

DROP TABLE IF EXISTS `sh_job`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sh_job` (
  `shjob_id` varchar(38) NOT NULL,
  `job_type` varchar(50) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  `is_inhibited` char(1) NOT NULL,
  `location_id` bigint(16) DEFAULT NULL,
  `order_id` decimal(20,0) DEFAULT NULL,
  `seprof_id` bigint(16) DEFAULT NULL,
  `parameters` varchar(1024) DEFAULT NULL,
  `schedule_type` int(1) DEFAULT NULL,
  `minute` int(2) DEFAULT NULL,
  `hour` int(2) DEFAULT NULL,
  `day_of_month` int(2) DEFAULT NULL,
  `month_of_year` int(2) DEFAULT NULL,
  `year` int(4) DEFAULT NULL,
  `days_of_week` varchar(32) DEFAULT NULL,
  `end_day` int(2) DEFAULT NULL,
  `end_month` int(2) DEFAULT NULL,
  `end_year` int(4) DEFAULT NULL,
  PRIMARY KEY (`shjob_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_group_monitor`
--

DROP TABLE IF EXISTS `sn_group_monitor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_group_monitor` (
  `snscon_id` int(9) NOT NULL,
  `snscgr_id` int(9) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`snscon_id`,`snscgr_id`),
  KEY `SNGROUPMONITOR_SNSCGRID_IDX` (`snscgr_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_managed_process`
--

DROP TABLE IF EXISTS `sn_managed_process`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_managed_process` (
  `snscon_id` int(9) NOT NULL,
  `managed_process_pkey` int(9) NOT NULL,
  `default_operating_mode` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`snscon_id`,`managed_process_pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_system_controller`
--

DROP TABLE IF EXISTS `sn_system_controller`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_system_controller` (
  `snscon_id` int(9) NOT NULL,
  `name` varchar(100) NOT NULL,
  `agent_poll_period` int(8) NOT NULL,
  `heartbeat_send_period` int(8) NOT NULL,
  `agent_response_timeout` int(8) NOT NULL,
  `server_entity_pkey` int(9) NOT NULL,
  `snscgr_id` int(9) DEFAULT NULL,
  `debug_log_dir` varchar(1024) NOT NULL,
  `bin_dir` varchar(1024) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `heartbeat_send_number` decimal(22,0) DEFAULT '3',
  PRIMARY KEY (`snscon_id`),
  UNIQUE KEY `SNSCON_01_UK` (`name`),
  KEY `SNSYSCTRL_SNSCGRID_IDX` (`snscgr_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_system_controller_coretest`
--

DROP TABLE IF EXISTS `sn_system_controller_coretest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_system_controller_coretest` (
  `snscon_id` int(9) DEFAULT NULL,
  `name` varchar(100) NOT NULL,
  `agent_poll_period` int(8) NOT NULL,
  `heartbeat_send_period` int(8) NOT NULL,
  `agent_response_timeout` int(8) NOT NULL,
  `server_entity_pkey` int(9) NOT NULL,
  `snscgr_id` int(9) DEFAULT NULL,
  `debug_log_dir` varchar(1024) NOT NULL,
  `bin_dir` varchar(1024) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `heartbeat_send_number` decimal(22,0) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_system_controller_group`
--

DROP TABLE IF EXISTS `sn_system_controller_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_system_controller_group` (
  `snscgr_id` int(9) NOT NULL,
  `name` varchar(100) NOT NULL,
  `description` varchar(256) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`snscgr_id`),
  UNIQUE KEY `SNSCGR_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `sn_system_controller_original`
--

DROP TABLE IF EXISTS `sn_system_controller_original`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sn_system_controller_original` (
  `snscon_id` int(9) DEFAULT NULL,
  `name` varchar(100) NOT NULL,
  `agent_poll_period` int(8) NOT NULL,
  `heartbeat_send_period` int(8) NOT NULL,
  `agent_response_timeout` int(8) NOT NULL,
  `server_entity_pkey` int(9) NOT NULL,
  `snscgr_id` int(9) DEFAULT NULL,
  `debug_log_dir` varchar(1024) NOT NULL,
  `bin_dir` varchar(1024) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `so_sound_category`
--

DROP TABLE IF EXISTS `so_sound_category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `so_sound_category` (
  `soscat_id` int(9) NOT NULL,
  `name` varchar(100) NOT NULL,
  `position` int(9) NOT NULL,
  PRIMARY KEY (`soscat_id`),
  UNIQUE KEY `SOSCAT_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `so_sound_file`
--

DROP TABLE IF EXISTS `so_sound_file`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `so_sound_file` (
  `soscat_id` int(9) NOT NULL,
  `priority` int(9) NOT NULL,
  `description` varchar(1024) DEFAULT NULL,
  `sound_file` varchar(1024) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`soscat_id`,`priority`),
  KEY `SOSOUNDFILE_SOSCATID_IDX` (`soscat_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ss`
--

DROP TABLE IF EXISTS `ss`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ss` (
  `subsystemkey` int(9) DEFAULT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `st_type`
--

DROP TABLE IF EXISTS `st_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `st_type` (
  `sttype_id` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `description` varchar(250) NOT NULL,
  `unit_of_measure` varchar(20) NOT NULL,
  `subsystemkey` decimal(22,0) NOT NULL,
  `enabled` int(1) NOT NULL,
  `format` int(1) NOT NULL,
  `frequency` int(9) NOT NULL,
  PRIMARY KEY (`sttype_id`),
  KEY `IDX_STTYPE_SUBSYSTEMKEY` (`subsystemkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `st_values`
--

DROP TABLE IF EXISTS `st_values`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `st_values` (
  `stvalu_id` int(9) NOT NULL,
  `sttype_id` int(9) NOT NULL,
  `createtime` datetime NOT NULL,
  `valuestr` varchar(20) DEFAULT NULL,
  `valuelong` int(9) DEFAULT NULL,
  `valuereal` decimal(22,0) DEFAULT NULL,
  `entitykey` int(9) DEFAULT NULL,
  PRIMARY KEY (`stvalu_id`),
  KEY `IDX_STVALU_ENTITYKEY` (`entitykey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `step_details`
--

DROP TABLE IF EXISTS `step_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `step_details` (
  `p_key` int(6) NOT NULL,
  `fk_step_type` int(6) NOT NULL,
  `fk_node_tree` int(6) NOT NULL,
  `position` int(6) NOT NULL,
  `description` varchar(500) DEFAULT NULL,
  `skip` int(1) NOT NULL,
  `skippable` int(1) NOT NULL,
  `delay` int(6) NOT NULL,
  `ignore_failure` int(1) DEFAULT NULL,
  `name` varchar(150) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `no_wait` int(1) DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  KEY `IDX_STEP_DETAILS_NTREE` (`fk_node_tree`),
  KEY `STDETAIL_POSITION_IDX` (`position`),
  KEY `STDETAIL_STEPTYPE_IDX` (`fk_step_type`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `step_parameters`
--

DROP TABLE IF EXISTS `step_parameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `step_parameters` (
  `p_key` int(6) NOT NULL,
  `fk_step_details` int(6) NOT NULL,
  `position` int(6) NOT NULL,
  `value` varchar(1000) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  KEY `IDX_STEP_PARS_SDETAILS` (`fk_step_details`),
  KEY `STPARAM_POSITION_IDX` (`position`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `step_type`
--

DROP TABLE IF EXISTS `step_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `step_type` (
  `p_key` int(6) NOT NULL,
  `type_value` int(6) NOT NULL,
  `type_name` varchar(50) NOT NULL,
  `step_use` int(6) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  UNIQUE KEY `PLSTYP_01_UK` (`type_value`),
  UNIQUE KEY `PLSTYP_0_UK` (`type_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `step_type_parameter_types`
--

DROP TABLE IF EXISTS `step_type_parameter_types`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `step_type_parameter_types` (
  `p_key` int(6) NOT NULL,
  `fk_step_type` int(6) NOT NULL,
  `fk_parameter_type` int(6) NOT NULL,
  `position` int(6) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`p_key`),
  KEY `PLSTPT_FKPARAMTYPE_IDX` (`fk_parameter_type`),
  KEY `PLSTPT_FKSTEPTYPE_IDX` (`fk_step_type`),
  KEY `PLSTPT_POSITION_IDX` (`position`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `subsystem`
--

DROP TABLE IF EXISTS `subsystem`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `subsystem` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `is_physical` int(1) NOT NULL,
  `exclusive_control` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  `system_key` int(9) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_SUBSYSTEM` (`pkey`),
  UNIQUE KEY `SUBSYSTEM_NAME_UK` (`name`),
  KEY `SUBSYSTEM_ISPHYSICAL_IDX` (`is_physical`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `system`
--
DROP TABLE IF EXISTS `system`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE  `system` (
  `pkey` int(9) NOT NULL,
  `name` varchar(80) NOT NULL,
  `is_physical` int(1) NOT NULL,
  `exclusive_control` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t1`
--

DROP TABLE IF EXISTS `t1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t1` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `sessta_id` int(9) DEFAULT NULL,
  `seagro_id` int(9) NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t2`
--

DROP TABLE IF EXISTS `t2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t2` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `sessta_id` int(9) DEFAULT NULL,
  `seagro_id` int(9) NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t5`
--

DROP TABLE IF EXISTS `t5`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t5` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `sessta_id` int(9) DEFAULT NULL,
  `seagro_id` int(9) NOT NULL,
  `seacti_id` int(9) DEFAULT NULL,
  KEY `T5_INDX` (`seprof_id`,`subsystemkey`,`physical_subsystem_key`,`seacti_id`,`sessta_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t6`
--

DROP TABLE IF EXISTS `t6`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t6` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `sessta_id` int(9) DEFAULT NULL,
  `seagro_id` int(9) NOT NULL,
  `seacti_id` int(9) DEFAULT NULL,
  KEY `T6_INDX` (`seprof_id`,`subsystemkey`,`physical_subsystem_key`,`seacti_id`,`sessta_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `t8`
--

DROP TABLE IF EXISTS `t8`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `t8` (
  `seprof_id` int(9) NOT NULL,
  `subsystemkey` int(9) NOT NULL,
  `physical_subsystem_key` int(9) DEFAULT NULL,
  `sessta_id` int(9) DEFAULT NULL,
  `seagro_id` int(9) NOT NULL,
  `seacti_id` int(9) DEFAULT NULL,
  KEY `T8_INDX` (`seprof_id`,`subsystemkey`,`physical_subsystem_key`,`seacti_id`,`sessta_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ta_error_log`
--

DROP TABLE IF EXISTS `ta_error_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ta_error_log` (
  `pkey` int(9) NOT NULL,
  `sql_statement` varchar(2000) DEFAULT NULL,
  `error_message` varchar(2000) DEFAULT NULL,
  `timestamp` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ta_session`
--

DROP TABLE IF EXISTS `ta_session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ta_session` (
  `pkey` varchar(38) NOT NULL,
  `operatorkey` int(9) NOT NULL,
  `consolekey` int(9) NOT NULL,
  `seprof_id` int(9) NOT NULL,
  `locati_id` int(9) NOT NULL,
  `entity_id` int(9) NOT NULL,
  `has_ended` int(1) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  # UNIQUE KEY `PK_TA_SESSION` (`pkey`),
  KEY `TASESSION_OPRKEY_IDX` (`operatorkey`),
  KEY `TA_SESSION_LOCATI_ID_INDX` (`locati_id`),
  KEY `TA_SESSION_SEPROF_ID_INDX` (`seprof_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ta_session_log`
--

DROP TABLE IF EXISTS `ta_session_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ta_session_log` (
  `pkey` int(9) NOT NULL,
  `fromwhere` varchar(30) NOT NULL,
  `start_location` varchar(30) DEFAULT NULL,
  `en_de_q` decimal(22,0) NOT NULL,
  `qualifier` varchar(30) NOT NULL,
  `sql_statement` varchar(2000) NOT NULL,
  `timestamp` datetime NOT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `te_directory_entry`
--

DROP TABLE IF EXISTS `te_directory_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `te_directory_entry` (
  `tedent_id` int(9) NOT NULL,
  `tesubd_id` int(9) NOT NULL,
  `tel_number` varchar(32) DEFAULT NULL,
  `fullname` varchar(32) DEFAULT NULL,
  `location` varchar(32) DEFAULT NULL,
  `status` int(4) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tedent_id`),
  UNIQUE KEY `UNIQUE_TE_DIR_ENTRY_TEL_NUMBER` (`tel_number`,`status`),
  KEY `TEDENT_STATUS_IDX` (`status`),
  KEY `TEDENT_TESUBDID_IDX` (`tesubd_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `te_speed_dial_button`
--

DROP TABLE IF EXISTS `te_speed_dial_button`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `te_speed_dial_button` (
  `tesdbu_id` int(9) NOT NULL,
  `tesdse_id` int(9) NOT NULL,
  `button_position` int(3) DEFAULT NULL,
  `button_label` varchar(32) DEFAULT NULL,
  `button_tsi` varchar(32) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tesdbu_id`),
  KEY `TESDBU_BTNPOS_IDX` (`button_position`),
  KEY `TESDBU_TESDSEID_IDX` (`tesdse_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `te_speed_dial_set`
--

DROP TABLE IF EXISTS `te_speed_dial_set`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `te_speed_dial_set` (
  `tesdse_id` int(9) NOT NULL,
  `operator_key` int(9) NOT NULL DEFAULT '-1',
  `seprof_id` int(9) NOT NULL DEFAULT '-1',
  `set_name` varchar(20) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tesdse_id`),
  UNIQUE KEY `U_TSDS_OK_SI_SN` (`operator_key`,`seprof_id`,`set_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `te_subdirectory`
--

DROP TABLE IF EXISTS `te_subdirectory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `te_subdirectory` (
  `tesubd_id` int(9) NOT NULL,
  `name` varchar(255) NOT NULL,
  `status` int(4) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tesubd_id`),
  UNIQUE KEY `TESUBD_NAME_IDX` (`name`),
  KEY `TESUBD_STATUS_IDX` (`status`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `test`
--

DROP TABLE IF EXISTS `test`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test` (
  `agent` varchar(300) DEFAULT NULL,
  `date_created` datetime DEFAULT NULL,
  `mdate` datetime DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `test02`
--

DROP TABLE IF EXISTS `test02`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test02` (
  `id` decimal(10,1) DEFAULT NULL,
  `name` varchar(20) DEFAULT NULL,
  `timestamp` datetime DEFAULT NULL,
  `number` decimal(38,30) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `test_xx`
--

DROP TABLE IF EXISTS `test_xx`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test_xx` (
  `agent` varchar(200) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_adhoc_default_attributes`
--

DROP TABLE IF EXISTS `ti_adhoc_default_attributes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_adhoc_default_attributes` (
  `tiadat_id` decimal(22,0) NOT NULL,
  `tipmli_id` decimal(22,0) NOT NULL,
  `stis_led_display_mode` decimal(22,0) DEFAULT NULL,
  `stis_led_scroll_speed` decimal(22,0) DEFAULT NULL,
  `stis_led_validity_period` decimal(22,0) DEFAULT NULL,
  `stis_led_repeat_interval` decimal(22,0) DEFAULT NULL,
  `stis_led_display_time` decimal(22,0) DEFAULT NULL,
  `stis_led_justification` decimal(22,0) DEFAULT NULL,
  `stis_led_font_size` decimal(22,0) DEFAULT NULL,
  `stis_led_intensity` decimal(22,0) DEFAULT NULL,
  `stis_led_font_colour` decimal(22,0) DEFAULT NULL,
  `stis_led_background_colour` decimal(22,0) DEFAULT NULL,
  `ttis_led_display_mode` decimal(22,0) DEFAULT NULL,
  `ttis_led_scroll_speed` decimal(22,0) DEFAULT NULL,
  `ttis_led_validity_period` decimal(22,0) DEFAULT NULL,
  `ttis_led_repeat_interval` decimal(22,0) DEFAULT NULL,
  `ttis_led_display_time` decimal(22,0) DEFAULT NULL,
  `ttis_led_latin_font_size` decimal(22,0) DEFAULT NULL,
  `ttis_led_justification` decimal(22,0) DEFAULT NULL,
  `ttis_led_intensity` decimal(22,0) DEFAULT NULL,
  `stis_plasma_display_mode` decimal(22,0) DEFAULT NULL,
  `stis_plasma_scroll_speed` decimal(22,0) DEFAULT NULL,
  `stis_plasma_validity_period` decimal(22,0) DEFAULT NULL,
  `stis_plasma_repeat_interval` decimal(22,0) DEFAULT NULL,
  `stis_plasma_display_time` decimal(22,0) DEFAULT NULL,
  `stis_plasma_justification` decimal(22,0) DEFAULT NULL,
  `stis_plasma_font_size` decimal(22,0) DEFAULT NULL,
  `stis_plasma_font_type` decimal(22,0) DEFAULT NULL,
  `stis_plasma_foreground_colour` decimal(22,0) DEFAULT NULL,
  `stis_plasma_background_colour` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`tiadat_id`),
  KEY `TIADAT_TIPMLIID_IDX` (`tipmli_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_display_request`
--

DROP TABLE IF EXISTS `ti_display_request`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_display_request` (
  `tidreq_id` varchar(38) NOT NULL,
  `timestamp` varchar(30) DEFAULT NULL,
  `destination_system` varchar(5) DEFAULT NULL,
  `is_send_success` varchar(4) DEFAULT NULL,
  `submitted_by` varchar(50) DEFAULT NULL,
  `message_type` decimal(22,0) DEFAULT NULL,
  `message_tag` decimal(22,0) DEFAULT NULL,
  `library_section` decimal(22,0) DEFAULT NULL,
  `library_version` decimal(22,0) DEFAULT NULL,
  `ad_hoc_message_content` varchar(256) DEFAULT NULL,
  `start_time` varchar(15) DEFAULT NULL,
  `end_time` varchar(15) DEFAULT NULL,
  `continuous` decimal(22,0) DEFAULT NULL,
  `priority` decimal(22,0) DEFAULT NULL,
  `ratis_tag` varchar(25) DEFAULT NULL,
  `ratis_destination` varchar(30) DEFAULT NULL,
  `ratis_overridable` decimal(22,0) DEFAULT NULL,
  `stis_destination_station` varchar(3) DEFAULT NULL,
  `stis_destination_levels` varchar(50) DEFAULT NULL,
  `stis_destination_pids` varchar(250) DEFAULT NULL,
  `ttis_destination_train_id` varchar(5) DEFAULT NULL,
  `ttis_destination_pids` varchar(50) DEFAULT NULL,
  `display_mode` decimal(22,0) DEFAULT NULL,
  `scroll_speed` decimal(22,0) DEFAULT NULL,
  `repeat_interval` decimal(22,0) DEFAULT NULL,
  `display_time` decimal(22,0) DEFAULT NULL,
  `justification` decimal(22,0) DEFAULT NULL,
  `led_font_size` decimal(22,0) DEFAULT NULL,
  `led_intensity` decimal(22,0) DEFAULT NULL,
  `led_font_colour` decimal(22,0) DEFAULT NULL,
  `led_background_colour` decimal(22,0) DEFAULT NULL,
  `plasma_font_size` decimal(22,0) DEFAULT NULL,
  `plasma_font_type` decimal(22,0) DEFAULT NULL,
  `plasma_foreground_colour` decimal(22,0) DEFAULT NULL,
  `plasma_background_colour` decimal(22,0) DEFAULT NULL,
  `create_time` datetime DEFAULT NULL,
  PRIMARY KEY (`tidreq_id`),
  KEY `TIDREQ_TIMESTAMP_IDX` (`timestamp`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_pid_group_map`
--

DROP TABLE IF EXISTS `ti_pid_group_map`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_pid_group_map` (
  `pid_key` int(9) NOT NULL,
  `tipgro_id` varchar(38) NOT NULL,
  PRIMARY KEY (`tipgro_id`,`pid_key`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_pid_groups`
--

DROP TABLE IF EXISTS `ti_pid_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_pid_groups` (
  `tipgro_id` varchar(38) NOT NULL,
  `name` varchar(40) NOT NULL,
  `location_key` int(9) NOT NULL,
  PRIMARY KEY (`tipgro_id`),
  UNIQUE KEY `LOC_NAME_UK` (`location_key`,`name`),
  KEY `TIPGRO_NAME_IDX` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_predefined_message`
--

DROP TABLE IF EXISTS `ti_predefined_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_predefined_message` (
  `tipmes_id` decimal(22,0) NOT NULL,
  `tipmli_id` decimal(22,0) NOT NULL,
  `message_tag` decimal(22,0) DEFAULT NULL,
  `library_section` decimal(22,0) DEFAULT NULL,
  `description` varchar(125) DEFAULT NULL,
  `priority` decimal(22,0) DEFAULT NULL,
  `repeat_interval` decimal(22,0) DEFAULT NULL,
  `message_content` varchar(256) DEFAULT NULL,
  `english_only` decimal(22,0) DEFAULT NULL,
  PRIMARY KEY (`tipmes_id`),
  KEY `TIPMES_MESTAG_IDX` (`message_tag`),
  KEY `TIPMES_TIPMLIID_IDX` (`tipmli_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_predefined_message_library`
--

DROP TABLE IF EXISTS `ti_predefined_message_library`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_predefined_message_library` (
  `tipmli_id` int(9) NOT NULL,
  `version` decimal(22,0) NOT NULL,
  `library_type` varchar(4) DEFAULT NULL,
  `library_file_content` longblob,
  PRIMARY KEY (`tipmli_id`),
  UNIQUE KEY `TIPMLI_01_UK` (`version`,`library_type`),
  KEY `TIPMLI_LIBTYPE_IDX` (`library_type`),
  KEY `TIPMLI_VER_IDX` (`version`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_ratis_dest`
--

DROP TABLE IF EXISTS `ti_ratis_dest`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_ratis_dest` (
  `tirdes_id` int(9) NOT NULL,
  `destination` varchar(30) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tirdes_id`),
  UNIQUE KEY `UNIQUE_TI_RATIS_DEST_DEST` (`destination`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_ratis_message`
--

DROP TABLE IF EXISTS `ti_ratis_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_ratis_message` (
  `tirmes_id` decimal(22,0) NOT NULL,
  `session_ref` decimal(22,0) DEFAULT NULL,
  `start_time` varchar(14) DEFAULT NULL,
  `end_time` varchar(14) DEFAULT NULL,
  `requires_vetting` int(1) DEFAULT NULL,
  `overridable` int(1) DEFAULT NULL,
  `type` decimal(22,0) DEFAULT NULL,
  `status` decimal(22,0) DEFAULT NULL,
  `creation_date` decimal(22,0) DEFAULT NULL,
  `message_text` varchar(256) DEFAULT NULL,
  `priority` decimal(22,0) DEFAULT NULL,
  `tag` varchar(12) DEFAULT NULL,
  `destination` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`tirmes_id`),
  KEY `TIRMES_CRTDATE_IDX` (`creation_date`),
  KEY `TIRMES_RQEVETT_IDX` (`requires_vetting`),
  KEY `TIRMES_TAG_IDX` (`tag`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_ratis_tag`
--

DROP TABLE IF EXISTS `ti_ratis_tag`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_ratis_tag` (
  `tirtag_id` int(9) NOT NULL,
  `tag_group` varchar(3) NOT NULL,
  `detail` varchar(5) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`tirtag_id`),
  UNIQUE KEY `UNIQUE_TI_RATIS_TAG_GD` (`tag_group`,`detail`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_train_time_schedule`
--

DROP TABLE IF EXISTS `ti_train_time_schedule`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_train_time_schedule` (
  `tittsc_id` int(9) NOT NULL,
  `name` varchar(85) NOT NULL,
  `adhoc1_title` varchar(40) DEFAULT NULL,
  `adhoc1` varchar(125) DEFAULT NULL,
  `adhoc2_title` varchar(40) DEFAULT NULL,
  `adhoc2` varchar(125) DEFAULT NULL,
  `adhoc3_title` varchar(40) DEFAULT NULL,
  `adhoc3` varchar(125) DEFAULT NULL,
  `adhoc4_title` varchar(40) DEFAULT NULL,
  `adhoc4` varchar(125) DEFAULT NULL,
  `adhoc5_title` varchar(40) DEFAULT NULL,
  `adhoc5` varchar(125) DEFAULT NULL,
  `adhoc6_title` varchar(40) DEFAULT NULL,
  `adhoc6` varchar(125) DEFAULT NULL,
  PRIMARY KEY (`tittsc_id`),
  UNIQUE KEY `TITTSC_01_UK` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `ti_train_time_schedule_entry`
--

DROP TABLE IF EXISTS `ti_train_time_schedule_entry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ti_train_time_schedule_entry` (
  `tittse_id` int(9) NOT NULL,
  `tittsc_id` int(9) NOT NULL,
  `start_time` datetime DEFAULT NULL,
  `end_time` datetime DEFAULT NULL,
  `repeat_interval` int(3) DEFAULT NULL,
  `message_table` int(3) DEFAULT NULL,
  `message_id` int(3) DEFAULT NULL,
  `priority` int(3) DEFAULT NULL,
  PRIMARY KEY (`tittse_id`),
  KEY `TITTSE_TITTSCID_IDX` (`tittsc_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `toad_plan_table`
--

DROP TABLE IF EXISTS `toad_plan_table`;

--
-- Table structure for table `tr_group_coverage`
--

DROP TABLE IF EXISTS `tr_group_coverage`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tr_group_coverage` (
  `trradg_id` int(9) NOT NULL,
  `location` int(9) NOT NULL,
  PRIMARY KEY (`trradg_id`,`location`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tr_radio_group`
--

DROP TABLE IF EXISTS `tr_radio_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tr_radio_group` (
  `trradg_id` int(9) NOT NULL,
  `group_tsi` varchar(32) NOT NULL,
  PRIMARY KEY (`trradg_id`),
  UNIQUE KEY `TRRADG_01_UK` (`group_tsi`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tr_train`
--

DROP TABLE IF EXISTS `tr_train`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tr_train` (
  `train_id` int(2) NOT NULL,
  `primary_tsi` varchar(32) DEFAULT NULL,
  `secondary_tsi` varchar(32) DEFAULT NULL,
  `pa_library_version` int(11) NOT NULL,
  `ttis_library_version` int(5) NOT NULL,
  `ttis_schedule_version` int(5) NOT NULL,
  `timestamp` datetime NOT NULL,
  PRIMARY KEY (`train_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tra_system_stats`
--

DROP TABLE IF EXISTS `tra_system_stats`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tra_system_stats` (
  `statid` varchar(30) DEFAULT NULL,
  `type` char(1) DEFAULT NULL,
  `version` decimal(22,0) DEFAULT NULL,
  `flags` decimal(22,0) DEFAULT NULL,
  `c1` varchar(30) DEFAULT NULL,
  `c2` varchar(30) DEFAULT NULL,
  `c3` varchar(30) DEFAULT NULL,
  `c4` varchar(30) DEFAULT NULL,
  `c5` varchar(30) DEFAULT NULL,
  `n1` decimal(22,0) DEFAULT NULL,
  `n2` decimal(22,0) DEFAULT NULL,
  `n3` decimal(22,0) DEFAULT NULL,
  `n4` decimal(22,0) DEFAULT NULL,
  `n5` decimal(22,0) DEFAULT NULL,
  `n6` decimal(22,0) DEFAULT NULL,
  `n7` decimal(22,0) DEFAULT NULL,
  `n8` decimal(22,0) DEFAULT NULL,
  `n9` decimal(22,0) DEFAULT NULL,
  `n10` decimal(22,0) DEFAULT NULL,
  `n11` decimal(22,0) DEFAULT NULL,
  `n12` decimal(22,0) DEFAULT NULL,
  `d1` datetime DEFAULT NULL,
  `r1` mediumblob,
  `r2` mediumblob,
  `ch1` varchar(1000) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trend_template`
--

DROP TABLE IF EXISTS `trend_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trend_template` (
  `name` varchar(30) DEFAULT NULL,
  `description` varchar(100) DEFAULT NULL,
  `graph_type` decimal(22,0) DEFAULT NULL,
  `time_range` decimal(22,0) DEFAULT NULL,
  `start_time` datetime DEFAULT NULL,
  `sample_period` decimal(22,0) DEFAULT NULL,
  `live` decimal(22,0) DEFAULT NULL,
  `items` varchar(1800) DEFAULT NULL,
  `extra_info` varchar(200) DEFAULT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  UNIQUE KEY `TRENDTEMPLATE_NAME_IDX` (`name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trendviewer_config`
--

DROP TABLE IF EXISTS `trendviewer_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trendviewer_config` (
  `config_name` varchar(50) DEFAULT NULL,
  `data_pt_name` varchar(500) DEFAULT NULL,
  `data_pt_type` varchar(100) DEFAULT NULL,
  `data_pt_color` varchar(50) DEFAULT NULL,
  `data_pt_server` varchar(100) DEFAULT NULL,
  `data_pt_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_name` varchar(50) DEFAULT NULL,
  `data_pt_visible` varchar(1) DEFAULT NULL,
  `data_pt_host` varchar(50) DEFAULT NULL,
  KEY `TRENDVIEWER_CONFIG_NDX` (`config_name`,`data_pt_name`,`data_pt_type`,`data_pt_color`,`data_pt_server`,`data_pt_enabled`,`data_pt_lbl_enabled`,`data_pt_lbl_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trendviewer_formula_config`
--

DROP TABLE IF EXISTS `trendviewer_formula_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trendviewer_formula_config` (
  `config_name` varchar(50) DEFAULT NULL,
  `data_pt_equation` varchar(2000) DEFAULT NULL,
  `data_pt_type` varchar(100) DEFAULT NULL,
  `data_pt_color` varchar(50) DEFAULT NULL,
  `data_pt_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_name` varchar(50) DEFAULT NULL,
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_01` (`config_name`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_02` (`data_pt_equation`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_03` (`data_pt_type`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_04` (`data_pt_color`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_05` (`data_pt_enabled`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_06` (`data_pt_lbl_enabled`),
  KEY `TRENDVIEWER_FORMULA_CONFIG_NDX_07` (`data_pt_lbl_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trendviewer_hist_config`
--

DROP TABLE IF EXISTS `trendviewer_hist_config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trendviewer_hist_config` (
  `config_name` varchar(50) DEFAULT NULL,
  `data_pt_name` varchar(500) DEFAULT NULL,
  `data_pt_type` varchar(100) DEFAULT NULL,
  `data_pt_color` varchar(50) DEFAULT NULL,
  `data_pt_server` varchar(100) DEFAULT NULL,
  `data_pt_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_enabled` varchar(1) DEFAULT NULL,
  `data_pt_lbl_name` varchar(50) DEFAULT NULL,
  `data_pt_dt` datetime DEFAULT NULL,
  `data_pt_dt_end` datetime DEFAULT NULL,
  `data_pt_host` varchar(50) DEFAULT NULL,
  KEY `TRENDVIEWER_HIST_CONFIG_NDX` (`config_name`,`data_pt_name`,`data_pt_type`,`data_pt_color`,`data_pt_server`,`data_pt_enabled`,`data_pt_lbl_enabled`,`data_pt_lbl_name`,`data_pt_dt`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trendviewer_log`
--

DROP TABLE IF EXISTS `trendviewer_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trendviewer_log` (
  `data_pt_name` varchar(500) DEFAULT NULL,
  `data_pt_server` varchar(100) DEFAULT NULL,
  `data_pt_value` decimal(22,0) DEFAULT NULL,
  `data_pt_date` datetime DEFAULT NULL,
  `data_pt_host` varchar(50) DEFAULT NULL,
  KEY `TRENDVIEWER_LOG_NDX` (`data_pt_name`,`data_pt_server`,`data_pt_value`,`data_pt_date`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `trendviewer_marker`
--

DROP TABLE IF EXISTS `trendviewer_marker`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trendviewer_marker` (
  `config_name` varchar(50) DEFAULT NULL,
  `marker_name` varchar(50) DEFAULT NULL,
  `marker_width` decimal(22,0) DEFAULT NULL,
  `marker_value` decimal(22,0) DEFAULT NULL,
  `marker_enabled` varchar(1) DEFAULT NULL,
  `marker_bcolor` varchar(50) DEFAULT NULL,
  `marker_fcolor` varchar(50) DEFAULT NULL,
  KEY `TRENDVIEWER_MARKER_NDX` (`config_name`,`marker_name`,`marker_width`,`marker_value`,`marker_enabled`,`marker_bcolor`,`marker_fcolor`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;


--
-- Table structure for table `typestat`
--

DROP TABLE IF EXISTS `typestat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `typestat` (
  `typename` varchar(80) DEFAULT NULL,
  `locationname` varchar(80) DEFAULT NULL,
  `cnt` decimal(22,0) DEFAULT NULL,
  `lockey` decimal(22,0) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `user_settings`
--

DROP TABLE IF EXISTS `user_settings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user_settings` (
  `op_key` int(9) NOT NULL,
  `ap_type_key` int(9) NOT NULL,
  `setting_name` varchar(80) NOT NULL,
  `setting_value` varchar(1024) NOT NULL,
  PRIMARY KEY (`op_key`,`ap_type_key`,`setting_name`)
  # , UNIQUE KEY `PK_USER_SETTINGS` (`op_key`,`ap_type_key`,`setting_name`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `verify_err`
--

DROP TABLE IF EXISTS `verify_err`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `verify_err` (
  `msg` varchar(50) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `verify_tmp`
--

DROP TABLE IF EXISTS `verify_tmp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `verify_tmp` (
  `tname` varchar(30) DEFAULT NULL,
  `rcount_central` int(9) DEFAULT NULL,
  `rcount_stn` int(9) DEFAULT NULL
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `version`
--

DROP TABLE IF EXISTS `version`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `version` (
  `pkey` decimal(22,0) NOT NULL,
  `version` varchar(30) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `vi_station_id`
--

DROP TABLE IF EXISTS `vi_station_id`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vi_station_id` (
  `vistid_id` decimal(22,0) NOT NULL,
  `station_id` decimal(22,0) NOT NULL,
  `ta_location` decimal(22,0) NOT NULL,
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`vistid_id`),
  UNIQUE KEY `VISTID_LOC_UK` (`ta_location`),
  UNIQUE KEY `VISTID_SID_UK` (`station_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `vi_triggering_events`
--

DROP TABLE IF EXISTS `vi_triggering_events`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vi_triggering_events` (
  `vitrev_id` decimal(22,0) NOT NULL,
  `vistid_id` decimal(22,0) NOT NULL,
  `event_id` decimal(22,0) NOT NULL,
  `location` varchar(30) DEFAULT NULL,
  `cctv_triggering` varchar(256) NOT NULL,
  `manual_closing` decimal(22,0) NOT NULL DEFAULT '0',
  `entitykey` decimal(22,0) NOT NULL DEFAULT '0',
  `created_by` varchar(30) NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`vitrev_id`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `vi_video_output_group`
--

DROP TABLE IF EXISTS `vi_video_output_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vi_video_output_group` (
  `coenti_id_01` int(9) NOT NULL,
  `position` int(4) NOT NULL,
  `coenti_id_02` int(9) DEFAULT NULL,
  PRIMARY KEY (`coenti_id_01`,`position`)
  # , UNIQUE KEY `SYS_C009365` (`coenti_id_01`,`position`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `zonetype`
--

DROP TABLE IF EXISTS `zonetype`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `zonetype` (
  `pkey` int(9) NOT NULL,
  `name` varchar(40) NOT NULL,
  PRIMARY KEY (`pkey`)
  # , UNIQUE KEY `PK_ZONETYPE` (`pkey`)
) ENGINE=innodb DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-09-26 15:46:24

-- DB patches' modification
-- DTL-955STIS-DEV-R1
alter table `ti_predefined_message` modify column `message_content` text character set utf8 collate utf8_bin default null;
alter table ti_adhoc_default_attributes drop column stis_led_display_mode;
alter table ti_adhoc_default_attributes drop column stis_led_scroll_speed;
alter table ti_adhoc_default_attributes drop column stis_led_validity_period;
alter table ti_adhoc_default_attributes drop column stis_led_repeat_interval;
alter table ti_adhoc_default_attributes drop column stis_led_display_time;
alter table ti_adhoc_default_attributes drop column stis_led_justification;
alter table ti_adhoc_default_attributes drop column stis_led_intensity;
alter table ti_adhoc_default_attributes drop column stis_led_background_colour;
alter table ti_adhoc_default_attributes drop column ttis_led_display_mode;
alter table ti_adhoc_default_attributes drop column ttis_led_scroll_speed;
alter table ti_adhoc_default_attributes drop column ttis_led_validity_period;
alter table ti_adhoc_default_attributes drop column ttis_led_repeat_interval;
alter table ti_adhoc_default_attributes drop column ttis_led_display_time;
alter table ti_adhoc_default_attributes drop column ttis_led_latin_font_size;
alter table ti_adhoc_default_attributes drop column ttis_led_justification;
alter table ti_adhoc_default_attributes drop column ttis_led_intensity;
alter table ti_adhoc_default_attributes drop column stis_plasma_display_mode;
alter table ti_adhoc_default_attributes drop column stis_plasma_scroll_speed;
alter table ti_adhoc_default_attributes drop column stis_plasma_validity_period;
alter table ti_adhoc_default_attributes drop column stis_plasma_repeat_interval;
alter table ti_adhoc_default_attributes drop column stis_plasma_display_time;
alter table ti_adhoc_default_attributes drop column stis_plasma_justification;
alter table ti_adhoc_default_attributes drop column stis_plasma_font_size;
alter table ti_adhoc_default_attributes drop column stis_plasma_font_type;
alter table ti_adhoc_default_attributes drop column stis_plasma_foreground_colour;
alter table ti_adhoc_default_attributes drop column stis_plasma_background_colour;
alter table ti_adhoc_default_attributes add (stis_lcd_font_size  int);
alter table ti_adhoc_default_attributes add (stis_lcd_font_colour  int);
alter table ti_adhoc_default_attributes add (stis_display_mode  int);
alter table ti_adhoc_default_attributes add (stis_scroll_speed  int);
alter table ti_adhoc_default_attributes add (stis_repeat_interval  int);
alter table ti_adhoc_default_attributes add (stis_display_time  int);
alter table ti_adhoc_default_attributes add (stis_justification  int);

DROP TABLE IF EXISTS `ti_stis_time_schedule`;
CREATE TABLE  `ti_stis_time_schedule` (
  `stis_ts_id` int(11) NOT NULL,
  `start_time` varchar(15) COLLATE utf8_bin DEFAULT NULL,
  `end_time` varchar(15) COLLATE utf8_bin DEFAULT NULL,
  `priority` int(11),
  `display_mode` int(11),
  `scroll_speed` int(11),
  `repeat_interval` int(11) DEFAULT NULL,
  `lcd_font_size` int(11) DEFAULT NULL,
  `lcd_font_colour` int(11) DEFAULT NULL,
  `led_font_size` int(11) DEFAULT NULL,
  `led_font_colour` int(11) DEFAULT NULL,
  `display_time` int(11) DEFAULT NULL,
  `justification` int(11) DEFAULT NULL,
  `text_content` varchar(256) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`stis_ts_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- DTL-MMSInitRelease-02
DROP TABLE IF EXISTS `mms_request_alarm`;
CREATE TABLE  `mms_request_alarm` (
  `pkey` int(9) NOT NULL,
  `alarmid` varchar(38) COLLATE utf8_bin NOT NULL,
  `alarmdate` datetime DEFAULT NULL,
  `alarmseverity` int(11) DEFAULT NULL,
  `equipmentid` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `alarmfaultcode` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `alarmdescription` varchar(400) COLLATE utf8_bin DEFAULT NULL,
  `problemreport` varchar(256) COLLATE utf8_bin DEFAULT NULL,
  `requestor` varchar(85) COLLATE utf8_bin DEFAULT NULL,
  `targetdate` datetime DEFAULT NULL,
  `isautotrigger` int(1) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `MMS_REQUEST_ALARM_ALARMID` (`alarmid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `mms_request_schematic`;
CREATE TABLE  `mms_request_schematic` (
  `PKEY` int(9) NOT NULL,
  `ENTITYKEY` int(9) NOT NULL,
  `REQUESTOR` varchar(50) COLLATE utf8_bin NOT NULL,
  `EQUIPMENTID` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `PROBLEMREPORT` varchar(256) COLLATE utf8_bin DEFAULT NULL,
  `TARGETDATE` datetime DEFAULT NULL,
  PRIMARY KEY (`PKEY`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

DROP TABLE IF EXISTS `mms_request_scheduled`;
CREATE TABLE `mms_request_scheduled` (
  `pkey` int(9) NOT NULL,
  `entitykey` int(9) NOT NULL,
  `equipmentid` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `metercode` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `equipmentdescription` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `dpvalue` decimal(14,4) DEFAULT NULL,
  `plandate` datetime DEFAULT NULL,
  `createdate` datetime DEFAULT NULL,
  `scheduledtype` int(3) DEFAULT NULL,
  PRIMARY KEY (`pkey`),
  UNIQUE KEY `MMS_REQ_SCHED_PLAN_ETY` (`entitykey`,`plandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- DTL-PA-Development-02
ALTER TABLE `pa_dva_message` MODIFY COLUMN `type` INT(9) NOT NULL;

DROP TABLE IF EXISTS `pa_hardware_parameter`;
CREATE TABLE  `pa_hardware_parameter` (
  `location_key` int(11) NOT NULL,
  `parameter_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `parameter_value` varchar(100) COLLATE utf8_bin DEFAULT NULL,
  `created_by` varchar(30) COLLATE utf8_bin NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`location_key`,`parameter_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

ALTER TABLE `pa_dva_message_version` DROP COLUMN `public_adhoc1`,
 DROP COLUMN `public_adhoc2`,
 DROP COLUMN `public_adhoc3`,
 DROP COLUMN `public_adhoc4`,
 DROP COLUMN `public_adhoc5`,
 DROP COLUMN `public_adhoc6`,
 CHANGE COLUMN `public_prerecorded` `version_number` VARCHAR(40) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
 DROP COLUMN `private_adhoc1`,
 DROP COLUMN `private_adhoc2`,
 DROP COLUMN `private_adhoc3`,
 DROP COLUMN `private_adhoc4`,
 DROP COLUMN `private_adhoc5`,
 DROP COLUMN `private_adhoc6`,
 DROP COLUMN `private_prerecorded`;

DROP TABLE IF EXISTS `pa_fire_countdown`;
CREATE TABLE  `pa_fire_countdown` (
  `location_key` int(9) NOT NULL,
  `stn_timer_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `occ_timer_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `stn_abort_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `occ_abort_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `created_by` varchar(30) COLLATE utf8_bin NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`location_key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
 
DROP TABLE IF EXISTS `pa_paging_console`;
CREATE TABLE  `pa_paging_console` (
  `location_key` int(11) NOT NULL,
  `paging_console_name` varchar(50) COLLATE utf8_bin NOT NULL,
  `paging_console_id` int(11) DEFAULT NULL,
  `created_by` varchar(30) COLLATE utf8_bin NOT NULL,
  `date_created` datetime NOT NULL,
  `modified_by` varchar(30) COLLATE utf8_bin DEFAULT NULL,
  `date_modified` datetime DEFAULT NULL,
  PRIMARY KEY (`location_key`,`paging_console_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
 
-- DTL-RAS-DEV-R1
ALTER TABLE `ra_subscriber` ADD PRIMARY KEY (`PKEY`),
 ADD UNIQUE INDEX `NN_RA_SUBSCRIBER_4`(`RESOURCE_ID`),
 ADD INDEX `NN_RA_SUBSCRIBER_5`(`SSI`); 

-- DTL-235
DROP TABLE IF EXISTS `se_security_setting`;
CREATE TABLE  `se_security_setting` (
  `setting_name` varchar(60) COLLATE utf8_bin NOT NULL DEFAULT '',
  `setting_value` int(11) DEFAULT NULL,
  `description` varchar(200) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`setting_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

ALTER TABLE `location` ADD COLUMN `is_display_only` INT(2) DEFAULT 0;

ALTER TABLE `ta_session` ADD COLUMN `isdisplayonly` INT(2),
                         ADD COLUMN `operator_override_key` INT(9),
                         ADD COLUMN `seprof_override_id` INT(9);
						 
DROP TABLE IF EXISTS `operator_password`;
CREATE TABLE `operator_password` (
  `pkey` int(9) NOT NULL DEFAULT '0',
  `latest_login_date` datetime DEFAULT NULL,
  `passwd_modified_date` datetime DEFAULT NULL,
  `latest_locked_time` datetime DEFAULT NULL,
  `is_password_lockout` int(9) DEFAULT NULL,
  `current_passwd_indicator` int(9) DEFAULT NULL,
  `password_0` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `password_1` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  `password_2` varchar(50) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`pkey`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;			
			 