insert into adm_sequence values ((select max(pkey)+1 from adm_sequence seq),'AQ_ENQ_DUP_CHECK_SEQ',1,0,2147483647,1,'N');
insert into adm_sequence values ((select max(pkey)+1 from adm_sequence seq),'AQ_DEQ_TOKEN_CHECK_SEQ',1,0,2147483647,1,'N');

truncate table aq_deq_token_check;

ALTER TABLE `aq_deq_token_check` ADD UNIQUE INDEX `AQ_DEQ_TOKEN_CHECK_U01`(`LOCATION`, `SRV_ID`, `Q_NAME`);

truncate table aq_enq_duplicate_check;

ALTER TABLE `aq_enq_duplicate_check` ADD UNIQUE INDEX `AQ_ENQ_DUPLICATE_CHECK_U01`(`LOCATION`, `SRV_ID`, `Q_NAME`);

DELIMITER ;;
DROP TRIGGER IF EXISTS aq_deq_token_check_bir_trg ;;
CREATE TRIGGER `aq_deq_token_check_bir_trg` BEFORE INSERT
    ON aq_deq_token_check FOR EACH ROW
BEGIN
	SET new.pkey = func_seq_get_next_number('AQ_DEQ_TOKEN_CHECK_SEQ');
END ;;

DROP TRIGGER IF EXISTS aq_enq_duplicate_check_bir_trg ;;
CREATE TRIGGER `aq_enq_duplicate_check_bir_trg` BEFORE INSERT
    ON aq_enq_duplicate_check FOR EACH ROW
BEGIN
	SET new.pkey = func_seq_get_next_number('AQ_ENQ_DUP_CHECK_SEQ');
END ;;
DELIMITER ;