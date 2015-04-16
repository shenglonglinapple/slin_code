BEGIN
  sys.dbms_aqadm.stop_queue 
      (queue_name => 'AUDIT_DATA_QUEUE');
  sys.dbms_aqadm.drop_queue 
      (queue_name => 'AUDIT_DATA_QUEUE');
END;
/

BEGIN
  sys.dbms_aqadm.stop_queue 
      (queue_name => 'AQ$_AUDIT_DATA_QUEUE_T_E');
  sys.dbms_aqadm.drop_queue 
      (queue_name => 'AQ$_AUDIT_DATA_QUEUE_T_E');
END;
/

BEGIN
  sys.dbms_aqadm.drop_queue_table 
  (queue_table => 'AUDIT_DATA_QUEUE_T');
END;
/

BEGIN
  sys.dbms_aqadm.stop_queue 
      (queue_name => 'MMS_DATA_QUEUE');
  sys.dbms_aqadm.drop_queue 
      (queue_name => 'MMS_DATA_QUEUE');
END;
/

BEGIN
  sys.dbms_aqadm.stop_queue 
      (queue_name => 'AQ$_MMS_DATA_QUEUE_T_E');
  sys.dbms_aqadm.drop_queue 
      (queue_name => 'AQ$_MMS_DATA_QUEUE_T_E');
END;
/

BEGIN
  sys.dbms_aqadm.drop_queue_table 
  (queue_table => 'MMS_DATA_QUEUE_T');
END;
/


/************Re-Create Type********/

drop type  "AUDIT_DATA_QUEUE_PAYLOAD_TYPE" force;
 CREATE OR REPLACE
TYPE "AUDIT_DATA_QUEUE_PAYLOAD_TYPE" as object (
 message_qualifier  VARCHAR2(100),
 db_srv_id  NUMBER,
 central_sid  NUMBER,
 audit_data_oracle VARCHAR2(4000),
 audit_data_mysql VARCHAR2(4000)
)
/

/************Re-Create Type********/


BEGIN
  DBMS_AQADM.CREATE_QUEUE_TABLE
  (
    QUEUE_TABLE           =>        'AUDIT_DATA_QUEUE_T'
   ,QUEUE_PAYLOAD_TYPE    =>        'AUDIT_DATA_QUEUE_PAYLOAD_TYPE'
   ,COMPATIBLE            =>        '8.1'
   ,STORAGE_CLAUSE        =>        '
                                     TABLESPACE CONFIG_DATA
                                     PCTUSED    0
                                     PCTFREE    10
                                     INITRANS   1
                                     MAXTRANS   255
                                     STORAGE    (
                                                 INITIAL          200K
                                                 NEXT             200K
                                                 MINEXTENTS       1
                                                 MAXEXTENTS       2147483645
                                                 PCTINCREASE      0
                                                 BUFFER_POOL      DEFAULT
                                                )'
   ,SORT_LIST             =>        'ENQ_TIME'
   ,MULTIPLE_CONSUMERS    =>         TRUE
   ,MESSAGE_GROUPING      =>         0
   ,COMMENT               =>         'Queue table for database distribution'
   ,SECURE                =>         FALSE
   );
End;
/
BEGIN
  SYS.DBMS_AQADM.CREATE_QUEUE
  (
    QUEUE_NAME          =>   'AUDIT_DATA_QUEUE'
   ,QUEUE_TABLE         =>   'AUDIT_DATA_QUEUE_T'
   ,QUEUE_TYPE          =>   SYS.DBMS_AQADM.NORMAL_QUEUE
   ,MAX_RETRIES         =>   5
   ,RETRY_DELAY         =>   0
   ,RETENTION_TIME      =>   0
   ,COMMENT             =>   'Queue for distribution'
   );
END;
/

BEGIN
  SYS.DBMS_AQADM.START_QUEUE
  (
    QUEUE_NAME => 'AUDIT_DATA_QUEUE'
   ,ENQUEUE => TRUE 
   ,DEQUEUE => TRUE 
   );
END;
/
BEGIN
  DBMS_AQADM.CREATE_QUEUE_TABLE
  (
    QUEUE_TABLE           =>        'MMS_DATA_QUEUE_T'
   ,QUEUE_PAYLOAD_TYPE    =>        'AUDIT_DATA_QUEUE_PAYLOAD_TYPE'
   ,COMPATIBLE            =>        '8.1'
   ,STORAGE_CLAUSE        =>        '
                                     TABLESPACE USERS
                                     PCTUSED    0
                                     PCTFREE    10
                                     INITRANS   1
                                     MAXTRANS   255
                                     STORAGE    (
                                                 INITIAL          200K
                                                 MINEXTENTS       1
                                                 MAXEXTENTS       2147483645
                                                 PCTINCREASE      0
                                                 BUFFER_POOL      DEFAULT
                                                )'
   ,SORT_LIST             =>        'ENQ_TIME'
   ,MULTIPLE_CONSUMERS    =>         TRUE
   ,MESSAGE_GROUPING      =>         0
   ,COMMENT               =>         'Queue table for database distribution'
   ,SECURE                =>         FALSE
   );
End;
/
BEGIN
  SYS.DBMS_AQADM.CREATE_QUEUE
  (
    QUEUE_NAME          =>   'MMS_DATA_QUEUE'
   ,QUEUE_TABLE         =>   'MMS_DATA_QUEUE_T'
   ,QUEUE_TYPE          =>   SYS.DBMS_AQADM.NORMAL_QUEUE
   ,MAX_RETRIES         =>   5
   ,RETRY_DELAY         =>   0
   ,RETENTION_TIME      =>   0
   ,COMMENT             =>   'Queue for distribution'
   );
END;
/

BEGIN
  SYS.DBMS_AQADM.START_QUEUE
  (
    QUEUE_NAME => 'MMS_DATA_QUEUE'
   ,ENQUEUE => TRUE 
   ,DEQUEUE => TRUE 
   );
END;
/

