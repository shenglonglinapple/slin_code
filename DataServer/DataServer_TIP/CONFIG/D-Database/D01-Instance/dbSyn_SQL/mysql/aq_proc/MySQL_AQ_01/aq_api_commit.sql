delimiter $$

DROP PROCEDURE IF EXISTS `prc_deqcommit_sid` $$
CREATE PROCEDURE `prc_deqcommit_sid`(
 IN p_queue             	 VARCHAR(80),
 IN p_subid                  INT(5),
 IN p_consumer               VARCHAR(30),
 IN p_deqmode       	  	 TINYINT(1),
 IN p_sid_begin              BIGINT(20),
 IN p_sid_end                BIGINT(20)
)
BEGIN
  DECLARE v_queue_name VARCHAR(50) DEFAULT UPPER(p_queue);
  declare v_dis_table VARCHAR(80) DEFAULT NULL;
  declare v_queue_table VARCHAR(80) DEFAULT NULL;

  SET v_dis_table = CONCAT('AQ_', v_queue_name, '_T_I');
  SET v_queue_table = CONCAT(v_queue_name, '_T');
	
  	IF p_consumer <> '' and p_subid = 0 then
		IF p_deqmode = 3 THEN
		  SET @g_sql = CONCAT('UPDATE ', v_dis_table, ' SET STATE = 4 WHERE sub_name = ''', p_consumer,
					''' and msg_sid between ', p_sid_begin, ' and ',p_sid_end);
		  PREPARE stmt FROM @g_sql;
		  EXECUTE stmt;
		  DEALLOCATE PREPARE stmt;
		  set @g_sql = null;
	-- use trigger to update AQ_TABLE		
		ELSEIF p_deqmode = 1 THEN
		  SET @g_sql = CONCAT('DELETE FROM ', v_dis_table, ' WHERE sub_name = ''', p_consumer,
					''' and msg_sid between ', p_sid_begin, ' and ',p_sid_end);
		  PREPARE stmt FROM @g_sql;
		  EXECUTE stmt;
		  DEALLOCATE PREPARE stmt;
		  set @g_sql = null;
	-- use trigger to delete AQ_TABLE
		END IF;
    ELSEIF (p_consumer is null or p_consumer = '') and p_subid > 0 then
		IF p_deqmode = 3 THEN
		  SET @g_sql = CONCAT('UPDATE ', v_dis_table, ' SET STATE = 4 WHERE sub_id = ', p_subid,
					' and msg_sid between ', p_sid_begin, ' and ',p_sid_end);
		  PREPARE stmt FROM @g_sql;
		  EXECUTE stmt;
		  DEALLOCATE PREPARE stmt;
		  set @g_sql = null;				
		ELSEIF p_deqmode = 1 THEN
		  SET @g_sql = CONCAT('DELETE FROM ', v_dis_table, ' WHERE sub_id = ', p_subid,
					' and msg_sid between ', p_sid_begin, ' and ',p_sid_end);
		  PREPARE stmt FROM @g_sql;
		  EXECUTE stmt;
		  DEALLOCATE PREPARE stmt;
		  set @g_sql = null;	
		END IF;
	END IF;

END $$