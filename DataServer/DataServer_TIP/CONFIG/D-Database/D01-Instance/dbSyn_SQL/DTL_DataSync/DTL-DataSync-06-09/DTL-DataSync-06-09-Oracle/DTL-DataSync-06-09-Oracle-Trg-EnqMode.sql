drop trigger alarm_printevent_trg;
drop trigger evcom_printevent_trg;

UPDATE  AQ_SYS_QUEUE_M SET ENQ_MODE = 4;