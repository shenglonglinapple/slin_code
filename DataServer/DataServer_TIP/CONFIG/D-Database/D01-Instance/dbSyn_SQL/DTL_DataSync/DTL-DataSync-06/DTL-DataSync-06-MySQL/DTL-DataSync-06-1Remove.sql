call prc_drop_queue('audit_data_queue');

DROP PROCEDURE IF EXISTS `prc_parse_queue_msg`;
DROP PROCEDURE IF EXISTS `prc_dequeue_delay`;
DROP PROCEDURE IF EXISTS `prc_dequeue`;
DROP PROCEDURE IF EXISTS `prc_dequeue_audit_data`;
DROP PROCEDURE IF EXISTS `prc_enq_table`;
DROP PROCEDURE IF EXISTS `prc_enq_others`;
DROP PROCEDURE IF EXISTS `prc_enqueue`;
DROP PROCEDURE IF EXISTS `prc_enqueue_audit_data`;

DROP PROCEDURE IF EXISTS `prc_create_queue`;
DROP PROCEDURE IF EXISTS `prc_drop_queue`;

delete from adm_sequence where name in ('AQ_LID_SEQ','AQ_HID_SEQ','AQ_ENQ_LID_SEQ','AQ_ENQ_HID_SEQ');