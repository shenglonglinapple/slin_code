DELIMITER $$

DROP PROCEDURE IF EXISTS `tra_occ`.`prc_drop_object`$$
CREATE DEFINER=`IT271350_5`@`%` PROCEDURE  `tra_occ`.`prc_drop_object`(
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