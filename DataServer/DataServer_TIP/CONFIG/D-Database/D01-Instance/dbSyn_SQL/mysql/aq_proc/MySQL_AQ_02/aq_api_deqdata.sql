DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_deqdata` $$
CREATE PROCEDURE `prc_deqdata`(
	IN p_queue              VARCHAR(80),
	IN p_consumer			varchar(30),
	IN p_subid              INT(5),
	IN p_fetchcnt           INT(5)
)
BEGIN
  DECLARE v_queue_name VARCHAR(50) DEFAULT UPPER(p_queue);
  declare v_dis_table VARCHAR(80) DEFAULT NULL;
  declare v_queue_table VARCHAR(80) DEFAULT NULL;
  
	SET v_dis_table = CONCAT('AQ_', v_queue_name, '_T_I');
	SET v_queue_table = CONCAT(v_queue_name, '_T');
	
	IF p_consumer <> '' and p_subid = 0 then
      SET @g_sql = CONCAT('SELECT qtab.q_name, qtab.msg_sid, qtab.msgid, qtab.priority, qtab.user_data FROM ',
      v_queue_table,' qtab, ',v_dis_table,' qitab WHERE qtab.msgid = qitab.msgid and qitab.sub_name = UPPER(''' ,p_consumer,
       ''')  AND qitab.state=1 ORDER BY qtab.msg_sid ASC LIMIT ',p_fetchcnt);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
	  
	ELSEIF (p_consumer is null or p_consumer = '') and p_subid > 0 then
	  SET @g_sql = CONCAT('SELECT qtab.q_name, qtab.msg_sid, qtab.msgid, qtab.priority, qtab.user_data FROM ',
      v_queue_table,' qtab, ',v_dis_table,' qitab WHERE qtab.msgid = qitab.msgid and qitab.sub_id = ' , p_subid,
       '  AND qitab.state=1 ORDER BY qtab.msg_sid ASC LIMIT ',p_fetchcnt);
			PREPARE stmt FROM @g_sql;
			EXECUTE stmt;
			DEALLOCATE PREPARE stmt;
      set @g_sql = null;
	END IF;
	
END $$
