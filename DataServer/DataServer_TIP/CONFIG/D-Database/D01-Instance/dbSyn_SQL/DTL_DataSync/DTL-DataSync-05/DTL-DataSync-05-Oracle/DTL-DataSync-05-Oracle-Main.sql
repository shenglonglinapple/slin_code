spool LOG-DTL-DataSync-05-Oracle-Main.txt


@DTL-DataSync-05-Oracle-AQ-PKG.sql
@TACOMP.SQL

DECLARE
v_job BINARY_INTEGER;
BEGIN
    BEGIN
        SELECT job
        INTO    v_job
        FROM     user_jobs
        WHERE     what = 'BEGIN audit_data_queue_pkg.dequeue_audit_data(''TRANSACT''); END;';
		DBMS_JOB.REMOVE(v_job);
	EXCEPTION
		WHEN OTHERS THEN NULL;
	END;
	DBMS_JOB.SUBMIT ( 
	   job => v_job,
	   what => 'BEGIN audit_data_queue_pkg.dequeue_audit_data(''TRANSACT''); END;',
	   interval  => 'SYSDATE + 1/60/24');
END;
/

insert into patch_log values ('DTL-DataSync-05-Oracle', sysdate);

commit;

spool off;
quit;
