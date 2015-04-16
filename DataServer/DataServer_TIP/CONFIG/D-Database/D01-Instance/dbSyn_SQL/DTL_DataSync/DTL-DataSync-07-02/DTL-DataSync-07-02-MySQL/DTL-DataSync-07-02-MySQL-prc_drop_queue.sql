DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_drop_queue` $$
CREATE PROCEDURE `prc_drop_queue`(
	IN p_queue_name      VARCHAR(50) )
BEGIN
	DECLARE v_sql                VARCHAR(2000) DEFAULT NULL;
	DECLARE v_qtable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_itable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_stable             VARCHAR(50) DEFAULT NULL;
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_seqadm_table       VARCHAR(30) DEFAULT 'adm_sequence_rep';
	DECLARE v_seqname            VARCHAR(50) DEFAULT NULL;

	DECLARE EXIT HANDLER FOR SQLEXCEPTION	
		ROLLBACK;
		
	SET v_qtable = CONCAT(p_queue_name, '_t');
	SET v_itable = CONCAT('aq_', v_qtable, '_i');
	SET v_stable = CONCAT('aq_', v_qtable, '_s');
	SET v_seqname = CONCAT('aq_', p_queue_name, '_seq');
	
START TRANSACTION;	
	SET @g_sql = CONCAT('DELETE FROM ', v_seqadm_table, ' WHERE NAME = UPPER(', '''',v_seqname,'''',')');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DELETE FROM ', v_qman_table, ' WHERE q_name = UPPER(', '''',p_queue_name,'''',')');
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_qtable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_itable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	
	SET @g_sql = CONCAT('DROP TABLE IF EXISTS ', v_stable);
	PREPARE stmt FROM @g_sql;
	EXECUTE stmt;
	DEALLOCATE PREPARE stmt;
	SET @g_sql = NULL;	
COMMIT;
	
END $$

DELIMITER ;