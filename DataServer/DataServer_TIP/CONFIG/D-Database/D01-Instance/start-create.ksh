#!/bin/ksh
########################################################
# The source code in this file is the property of
# Ripple Systems and is not for redistribution
# in any form.
#
# Source:  $File: //depot/3001_Review_Branch_DBSync/CONFIG/D-Database/D01-Instance/start-create.ksh $ 
# Author:  Ripple
# Version: $Revision: #1 $
#
# Last modification: $DateTime: 2013/01/24 17:57:59 $
# Last modified by:  $Author: CM $
#
#########################################################
# Check Usage
if [ ${#} -lt 6 ] || [ "$1" = "-h" -o "$1" = "-?" ]; then
  echo "Usage: $0 <INSTANCE> <ALT_MOUNT2> <ALT_MOUNT3> <ALT_MOUNT4> <ALT_MOUNT5> <DIRECTORY_PATH> <Oracle Home - if not set> <Oracle Base - if not set>"
  exit 1
fi

INSTANCE=${1}
################################################################################

# following best defined by oracle user .profile
# ORACLE_BASE=/u01/app/oracle; export ORACLE_BASE
# ORACLE_HOME=$ORACLE_BASE/OraHome920; export ORACLE_HOME
if [ "$ORACLE_HOME" = "" ]; then
  if  [ "$7" = "" ]; then
    echo "ORACLE_HOME not set.  Must include as an installation parameter."
    exit 0
  fi
  ORACLE_HOME=$7
  export ORACLE_HOME
else
  echo "ORACLE_HOME set to $ORACLE_HOME"
fi

if [ "$ORACLE_BASE" = "" ]; then
  if  [ "$8" = "" ]; then
    echo "ORACLE_BASE not set.  Must include as an installation parameter."
    exit 0
  fi
  ORACLE_BASE=$8
  export ORACLE_BASE
else
  echo "ORACLE_BASE set to $ORACLE_BASE"
fi

ORACLE_SID=${INSTANCE}; export ORACLE_SID
ALT_MOUNT2=${2}
ALT_MOUNT3=${3}
ALT_MOUNT4=${4}
ALT_MOUNT5=${5}
DIRECTORY_PATH=${6}

ADMINDIR=${ORACLE_BASE}/admin/${INSTANCE}
ALT_DATA2=${ALT_MOUNT2}/oradata/${INSTANCE}
ALT_DATA3=${ALT_MOUNT3}/oradata/${INSTANCE}
ALT_DATA4=${ALT_MOUNT4}/oradata/${INSTANCE}
ALT_ARCH4=${ALT_MOUNT4}/arch/${INSTANCE}
ALT_BACKUP=${ALT_MOUNT4}
ALT_LOGS=${ALT_MOUNT5}
ALT_DATA5=${ALT_MOUNT5}/oradata/${INSTANCE}
MKDIR=/usr/bin/mkdir

echo 'Oracle Instances must be shut down.....Hit return to continue, or CTRLC to halt and correct'
read continue

        ${MKDIR} -p ${ADMINDIR} 2>/dev/null
        ${MKDIR} -p ${ADMINDIR}/bdump 2>/dev/null
        ${MKDIR} -p ${ADMINDIR}/udump 2>/dev/null
        ${MKDIR} -p ${ADMINDIR}/cdump 2>/dev/null
	${MKDIR} -p ${ADMINDIR}/create 2>/dev/null
	${MKDIR} -p ${ADMINDIR}/pfile 2>/dev/null
	${MKDIR} -p ${ADMINDIR}/scripts 2>/dev/null
	${MKDIR} -p ${ALT_DATA2} 2>/dev/null
	${MKDIR} -p ${ALT_DATA2}/tmp 2>/dev/null
	${MKDIR} -p ${ALT_DATA3} 2>/dev/null
	${MKDIR} -p ${ALT_DATA4} 2>/dev/null
	${MKDIR} -p ${ALT_DATA4}/archive 2>/dev/null
	${MKDIR} -p ${ALT_ARCH4} 2>/dev/null
	${MKDIR} -p ${ALT_DATA5} 2>/dev/null
	${MKDIR} -p ${DIRECTORY_PATH} 2>/dev/null

if [ ! -d ${ADMINDIR} -o ! -d ${ALT_DATA2} -o ! -d ${ALT_DATA3} -o ! -d ${ALT_DATA4} -o ! -d ${ALT_DATA5} ]; then
  echo "Directories do not exist. Exiting"
  exit
fi

# cd create
/usr/bin/ksh ./create.ksh ${INSTANCE} ${ORACLE_BASE} ${ORACLE_HOME} ${ADMINDIR} ${ALT_DATA3} ${ALT_DATA4} ${ALT_DATA5} ${ALT_ARCH4} ${ALT_BACKUP} ${ALT_LOGS}
