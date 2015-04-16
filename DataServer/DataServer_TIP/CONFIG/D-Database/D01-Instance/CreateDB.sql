########################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/CreateDB.sql $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
########################################################

connect SYS/change_on_install as SYSDBA
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/CreateDB.log
startup nomount pfile="/u01/app/oracle/admin/GENERIC/scripts/init.ora";
CREATE DATABASE GENERIC
MAXINSTANCES 1
MAXLOGHISTORY 1
MAXLOGFILES 5
MAXLOGMEMBERS 5
MAXDATAFILES 100
DATAFILE '/u03/oradata/GENERIC/system01.dbf' SIZE 600M REUSE AUTOEXTEND ON NEXT  10240K MAXSIZE UNLIMITED
EXTENT MANAGEMENT LOCAL
DEFAULT TEMPORARY TABLESPACE TEMP TEMPFILE '/u03/oradata/GENERIC/temp01.dbf' SIZE 150M REUSE AUTOEXTEND ON NEXT  640K MAXSIZE UNLIMITED
UNDO TABLESPACE "UNDOTBS" DATAFILE '/u03/oradata/GENERIC/undotbs01.dbf' SIZE 600M REUSE AUTOEXTEND ON NEXT  5120K MAXSIZE UNLIMITED
CHARACTER SET WE8ISO8859P1
NATIONAL CHARACTER SET AL16UTF16
LOGFILE GROUP 1 ('/u03/oradata/GENERIC/redo01.log','/u05/oradata/GENERIC/redo11.log') SIZE 50M,
GROUP 2 ('/u03/oradata/GENERIC/redo02.log','/u05/oradata/GENERIC/redo12.log') SIZE 50M,
GROUP 3 ('/u03/oradata/GENERIC/redo03.log','/u05/oradata/GENERIC/redo13.log') SIZE 50M,
GROUP 4 ('/u03/oradata/GENERIC/redo04.log','/u05/oradata/GENERIC/redo14.log') SIZE 50M;
spool off
exit;
