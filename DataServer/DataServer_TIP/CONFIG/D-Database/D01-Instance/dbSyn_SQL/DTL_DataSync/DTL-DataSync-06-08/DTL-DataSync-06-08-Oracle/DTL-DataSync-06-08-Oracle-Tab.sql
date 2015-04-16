CREATE TABLE AQ_SYS_QUEUE_M
(
  Q_NAME        VARCHAR2(30 BYTE),
  Q_TYPE        NUMBER(1),
  SUB_COUNT     NUMBER(5),
  ENQ_STATE     NUMBER(1),
  DEQ_STATE     NUMBER(1),
  PAYLOAD_TYPE  NUMBER(1),
  RETENTION     NUMBER(11),
  ENQ_MODE      NUMBER(1),                      
  REMARK        VARCHAR2(512 BYTE)
)
TABLESPACE CONFIG_DATA;

COMMENT ON TABLE AQ_SYS_QUEUE_M IS 'AQ manage table for support datasync bwteen Oracle and MySQL';
COMMENT ON COLUMN AQ_SYS_QUEUE_M.ENQ_MODE IS '1 - use AQ API to enq;  2 - use SQL procedure to enq';

Insert into AQ_SYS_QUEUE_M
   (Q_NAME, ENQ_MODE)
 Values
   ('AUDIT_DATA_QUEUE', 2);
Insert into AQ_SYS_QUEUE_M
   (Q_NAME, ENQ_MODE)
 Values
   ('MMS_DATA_QUEUE', 2);

