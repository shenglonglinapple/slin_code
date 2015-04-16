CREATE OR REPLACE PROCEDURE prc_log_errors (p_sql_statement IN  VARCHAR2,p_error_message  IN  VARCHAR2) AS
  PRAGMA AUTONOMOUS_TRANSACTION;
BEGIN
  INSERT INTO error_log(pkey,sql_statement,error_message,timestamp)
         VALUES (errlog_seq.NEXTVAL,p_sql_statement,p_error_message,SYSDATE);
  COMMIT;
END;
/