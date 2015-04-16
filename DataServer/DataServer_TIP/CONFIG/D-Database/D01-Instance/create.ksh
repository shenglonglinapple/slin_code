#!/bin/ksh
################################################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
# 
# Source:   $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/create.ksh $
# @author:  Matt Chalwell
# @version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
# Create a new database instance.
#
################################################################################
INSTANCE=${1}
BASE=${2}
HOME=${3}
ADMIN_DIR=${4}
ALT_DATA3=${5}
ALT_DATA4=${6}
ALT_DATA5=${7}
ALT_ARCH4=${8}
ALT_BACKUP=${9}
ALT_LOGS=${10}

################################################################################
ORACLE_BASE=${BASE}; export ORACLE_BASE
ORACLE_HOME=${HOME}; export ORACLE_HOME
ORACLE_SID=${INSTANCE}; export ORACLE_SID
PWD=`/usr/bin/pwd`
password=sys

echo "${ORACLE_SID}:${ORACLE_HOME}:Y" >> /var/opt/oracle/oratab

$ORACLE_HOME/bin/orapwd file=$ORACLE_HOME/dbs/orapw${INSTANCE} password=$password entries=10

typeset -l dbname=${ORACLE_SID}

echo "export ORACLE_BASE=${ORACLE_BASE}" > /var/opt/oracle/$dbname.env
echo "export ORACLE_HOME=${ORACLE_HOME}" >> /var/opt/oracle/$dbname.env
cat ${PWD}/CreateDBEnv.env |sed "s%/u03%${ALT_BACKUP}%g" |sed "s%/u05%${ALT_LOGS}%g" |sed "s%GENERIC%${INSTANCE}%g" >> /var/opt/oracle/$dbname.env
chmod 755 /var/opt/oracle/$dbname.env

. /var/opt/oracle/$dbname.env
mkdir -p ${ORACLE_DBA}/scripts/sh
mkdir -p ${ORACLE_DBA}/scripts/sql
mkdir -p ${ORACLE_LOGS}
mkdir -p ${ARCHIVE_DIR}
mkdir -p ${BACKUP_DEST_DIR}
mkdir -p ${BACKUP_DEST_DIR_BACKUP}

cat ${PWD}/CreateDB.sql |sed "s%/u03/oradata/GENERIC%${ALT_DATA3}%g" |sed "s%/u04/oradata/GENERIC%${ALT_DATA4}%g" |sed "s%/u05/oradata/GENERIC%${ALT_DATA5}%g" |sed "s%GENERIC%${INSTANCE}%g" |sed "s%/u01/app/oracle/OraHome920%${ORACLE_HOME}%g" |sed "s%/u01/app/oracle%${ORACLE_BASE}%g" > ${ADMIN_DIR}/scripts/CreateDB.sql
cat ${PWD}/CreateDBFiles.sql |sed "s%/u03/oradata/GENERIC%${ALT_DATA3}%g" |sed "s%/u04/oradata/GENERIC%${ALT_DATA4}%g" |sed "s%/u05/oradata/GENERIC%${ALT_DATA5}%g" |sed "s%GENERIC%${INSTANCE}%g" |sed "s%/u01/app/oracle/OraHome920%${ORACLE_HOME}%g" |sed "s%/u01/app/oracle%${ORACLE_BASE}%g" > ${ADMIN_DIR}/scripts/CreateDBFiles.sql
cat ${PWD}/CreateDBCatalog.sql |sed "s%/u03/oradata/GENERIC%${ALT_DATA3}%g" |sed "s%/u04/oradata/GENERIC%${ALT_DATA4}%g" |sed "s%/u05/oradata/GENERIC%${ALT_DATA5}%g" |sed "s%GENERIC%${INSTANCE}%g" |sed "s%/u01/app/oracle/OraHome920%${ORACLE_HOME}%g" |sed "s%/u01/app/oracle%${ORACLE_BASE}%g" > ${ADMIN_DIR}/scripts/CreateDBCatalog.sql
cat ${PWD}/postDBCreation.sql |sed "s%/u03/oradata/GENERIC%${ALT_DATA3}%g" |sed "s%/u04/oradata/GENERIC%${ALT_DATA4}%g" |sed "s%/u05/oradata/GENERIC%${ALT_DATA5}%g" |sed "s%GENERIC%${INSTANCE}%g" |sed "s%/u01/app/oracle/OraHome920%${ORACLE_HOME}%g" |sed "s%/u01/app/oracle%${ORACLE_BASE}%g" > ${ADMIN_DIR}/scripts/postDBCreation.sql
cat ${PWD}/init.ora |sed "s%/u04/arch/GENERIC%${ALT_ARCH4}%g" |sed "s%/u03/oradata/GENERIC%${ALT_DATA3}%g" |sed "s%/u04/oradata/GENERIC%${ALT_DATA4}%g" |sed "s%/u05/oradata/GENERIC%${ALT_DATA5}%g" |sed "s%GENERIC%${INSTANCE}%g" |sed "s%/u01/app/oracle/OraHome920%${ORACLE_HOME}%g" |sed "s%/u01/app/oracle%${ORACLE_BASE}%g" > ${ADMIN_DIR}/scripts/init.ora

${ORACLE_HOME}/bin/sqlplus /nolog @${ADMIN_DIR}/scripts/CreateDB.sql
${ORACLE_HOME}/bin/sqlplus /nolog @${ADMIN_DIR}/scripts/CreateDBFiles.sql
${ORACLE_HOME}/bin/sqlplus /nolog @${ADMIN_DIR}/scripts/CreateDBCatalog.sql
${ORACLE_HOME}/bin/sqlplus /nolog @${ADMIN_DIR}/scripts/postDBCreation.sql

