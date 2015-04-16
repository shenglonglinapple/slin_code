########################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/CreateDBFiles.sql $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
########################################################
connect SYS/change_on_install as SYSDBA
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/CreateDBFiles.log
CREATE TABLESPACE "DRSYS" LOGGING DATAFILE '/u03/oradata/GENERIC/drsys01.dbf' SIZE 20M REUSE AUTOEXTEND ON NEXT  640K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL SEGMENT SPACE MANAGEMENT  AUTO ;
CREATE TABLESPACE "CWMLITE" LOGGING DATAFILE '/u03/oradata/GENERIC/cwmlite01.dbf' SIZE 20480K REUSE AUTOEXTEND ON NEXT  640K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL;
CREATE TABLESPACE "INDX" LOGGING DATAFILE '/u03/oradata/GENERIC/indx01.dbf' SIZE 25M REUSE AUTOEXTEND ON NEXT  1280K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL;
CREATE TABLESPACE "TOOLS" LOGGING DATAFILE '/u03/oradata/GENERIC/tools01.dbf' SIZE 10M REUSE AUTOEXTEND ON NEXT  320K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL;
CREATE TABLESPACE "USERS" LOGGING DATAFILE '/u03/oradata/GENERIC/users01.dbf' SIZE 25M REUSE AUTOEXTEND ON NEXT  1280K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL;
CREATE TABLESPACE "XDB" LOGGING DATAFILE '/u03/oradata/GENERIC/xdb01.dbf' SIZE 20M REUSE AUTOEXTEND ON NEXT  640K MAXSIZE UNLIMITED EXTENT MANAGEMENT LOCAL SEGMENT SPACE MANAGEMENT  AUTO ;
spool off
exit;
