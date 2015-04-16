########################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/CreateDBCatalog.sql $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
########################################################
connect SYS/change_on_install as SYSDBA
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/CreateDBCatalog.log
@/u01/app/oracle/OraHome920/rdbms/admin/catalog.sql;
@/u01/app/oracle/OraHome920/rdbms/admin/catexp7.sql;
@/u01/app/oracle/OraHome920/rdbms/admin/catblock.sql;
@/u01/app/oracle/OraHome920/rdbms/admin/catproc.sql;
@/u01/app/oracle/OraHome920/rdbms/admin/catoctk.sql;
@/u01/app/oracle/OraHome920/rdbms/admin/owminst.plb;
connect SYSTEM/manager
@/u01/app/oracle/OraHome920/sqlplus/admin/pupbld.sql;
spool off
connect SYSTEM/manager
set echo on
spool /u01/app/oracle/OraHome920/assistants/dbca/logs/sqlPlusHelp.log
@/u01/app/oracle/OraHome920/sqlplus/admin/help/hlpbld.sql helpus.sql;
spool off
exit;
