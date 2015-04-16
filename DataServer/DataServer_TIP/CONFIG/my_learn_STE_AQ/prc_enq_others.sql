DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enq_others` $$
CREATE DEFINER=`IT271350_5`@`%` PROCEDURE `prc_enq_others`(
	IN p_queue              VARCHAR(80),
	IN p_msgid              VARCHAR(38),
	IN p_sid                BIGINT(20) UNSIGNED,
	IN p_recipient          VARCHAR(4000) )
BEGIN
	DECLARE v_rec_name           VARCHAR(80) DEFAULT NULL;
	DECLARE v_rec_addr           VARCHAR(128) DEFAULT NULL;	
	DECLARE v_rec_nameaddr       VARCHAR(256) DEFAULT NULL;
	DECLARE v_recipient          VARCHAR(4000) DEFAULT NULL;
	DECLARE v_nameaddr_demli     VARCHAR(3) DEFAULT ',';
	DECLARE v_pairend_demli      VARCHAR(3) DEFAULT ';';
	DECLARE v_pairend_pos        INT(9) DEFAULT 0;
	DECLARE v_nameaddr_pos       INT(5) DEFAULT 0;
	
	SET v_recipient = p_recipient;
	the_parse_loop: LOOP
		SET v_rec_name = NULL;
		SET v_rec_addr = NULL;
		SET v_pairend_pos = INSTR(v_recipient, v_pairend_demli);	
		IF v_pairend_pos = 0 THEN
			LEAVE the_parse_loop;
		END IF;
		SET v_rec_nameaddr = LEFT(v_recipient, v_pairend_pos - 1);		
		SET v_recipient = SUBSTR(v_recipient, v_pairend_pos + 1);
		SET v_nameaddr_pos = INSTR(v_rec_nameaddr, v_nameaddr_demli);
		IF v_nameaddr_pos > 1 THEN
			SET v_rec_name = TRIM(LEFT(v_rec_nameaddr, v_nameaddr_pos - 1));
			SET v_rec_addr = TRIM(SUBSTR(v_rec_nameaddr, v_nameaddr_pos + 1));			
		END IF;
		IF (v_rec_name <> '') OR (v_rec_addr <> '') THEN
			CALL prc_enq_table(p_queue, p_msgid, v_rec_name, v_rec_addr, p_sid);
		END IF;
	END LOOP the_parse_loop;

	SET v_nameaddr_pos = INSTR(v_recipient, v_nameaddr_demli);

	IF v_nameaddr_pos > 1 THEN
	  if v_nameaddr_pos > 1 then
		SET v_rec_name = LEFT(v_recipient, v_nameaddr_pos - 1);
		SET v_rec_addr = SUBSTR(v_recipient, v_nameaddr_pos + 1);
	  elseif v_nameaddr_pos = 0 then
		SET v_rec_name = v_recipient;
	  end if;
		
		CALL prc_enq_table(p_queue, p_msgid, v_rec_name, v_rec_addr, p_sid);
	END IF;

END $$

DELIMITER ;