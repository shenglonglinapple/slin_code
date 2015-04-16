########################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/postDBCreation.sql $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
########################################################
connect SYS/change_on_install as SYSDBA
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/postDBCreation.log
@/u01/app/oracle/OraHome920/rdbms/admin/utlrp.sql;
@/u01/app/oracle/OraHome920/javavm/install/initjvm.sql;
shutdown ;
startup mount pfile="/u01/app/oracle/admin/GENERIC/scripts/init.ora";
alter database archivelog;
alter database open;
alter system archive log start;
shutdown ;
connect SYS/change_on_install as SYSDBA
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/postDBCreation.log
create spfile='/u01/app/oracle/OraHome920/dbs/spfileGENERIC.ora' FROM pfile='/u01/app/oracle/admin/GENERIC/scripts/init.ora';
connect SYS/change_on_install as SYSDBA
set echo on
startup ;
spool off;
exit;
