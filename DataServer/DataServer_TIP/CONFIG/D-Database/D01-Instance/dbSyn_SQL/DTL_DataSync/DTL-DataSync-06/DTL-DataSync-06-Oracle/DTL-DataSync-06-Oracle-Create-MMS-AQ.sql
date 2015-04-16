

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


DECLARE
v_job BINARY_INTEGER;
BEGIN
    BEGIN
        SELECT job
        INTO    v_job
        FROM     user_jobs
        WHERE     what = 'BEGIN audit_data_queue_pkg.dequeue_mms_data(''TRANSACT''); END;';
		DBMS_JOB.REMOVE(v_job);
	EXCEPTION
		WHEN OTHERS THEN NULL;
	END;
	DBMS_JOB.SUBMIT ( 
	   job => v_job,
	   what => 'BEGIN audit_data_queue_pkg.dequeue_mms_data(''TRANSACT''); END;',
	   interval  => 'SYSDATE + 1/60/24');
END;
/
