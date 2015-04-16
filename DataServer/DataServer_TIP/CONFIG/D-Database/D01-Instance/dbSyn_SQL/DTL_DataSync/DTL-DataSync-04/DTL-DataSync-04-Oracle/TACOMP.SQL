set serveroutput on;

DECLARE
   CURSOR c1
   IS
      SELECT o.object_name NAME, o.object_type TYPE, o.status
        FROM user_objects o
       WHERE o.status = 'INVALID';

   oname   VARCHAR2 (30);
   otype   VARCHAR2 (30);
BEGIN
   FOR r_c1 IN c1
   LOOP
      BEGIN
         oname := r_c1.NAME;
         otype := r_c1.TYPE;

         IF otype <> 'PACKAGE BODY'
         THEN
            
            EXECUTE IMMEDIATE 'ALTER ' || otype || ' ' || oname || ' COMPILE';
         ELSIF otype = 'PACKAGE BODY'
         THEN
            EXECUTE IMMEDIATE 'ALTER PACKAGE' || ' ' || oname
                              || ' COMPILE BODY';

            
         END IF;
      EXCEPTION
         WHEN OTHERS
         THEN
           -- DBMS_OUTPUT.put_line (   'EXCEPTION RAISED: ' ||oname||': ' ||TO_CHAR(SQLCODE) ||': '||SUBSTR(SQLERRM, 1, 80));
		  DBMS_OUTPUT.put_line (   'Comp_E:'||oname);
      END;
   END LOOP;
END;
/

COMMIT ;
