#include "WorkTime.h"

CAWorkTime::CAWorkTime()
{

}
CAWorkTime::~CAWorkTime()
{

}



qint64 CAWorkTime::getDiffTime( const QDateTime& timeBegin, const QDateTime& timeEnd )
{
	qint64 nDiffTimeMsecs = 0;

	//format to str		
	//char szCurTime[256] = {0};
	//sprintf(szCurTime, "%10.3f ms", diffAll); 
	//strDiffTime =	szCurTime;
	//TA_DB_Sync::trim(strDiffTime);


	//int cha = dataTimeCurrentPCTime.toMSecsSinceEpoch() - time.toMSecsSinceEpoch(); 这里是毫秒级别的
	//int chaMiao = cha/1000;
	//QDateTime time = QDateTime::fromString("2013-07-11 20:11:05", "yyyy-MM-dd hh:mm:ss");
	//qint64 sec = QDateTime::currentDateTime().secsTo(time);
	//qint64 msecs = QDateTime::currentDateTime().msecsTo(time);

	nDiffTimeMsecs = timeBegin.msecsTo(timeEnd);

		
	return nDiffTimeMsecs;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CWorkTimeLock::CWorkTimeLock(qint32 nWorkTimeCode )
{
	m_nWorkTimeCode = nWorkTimeCode;

	m_fTimeWorkBegin = QDateTime::currentDateTime();
	m_fTimeWorkEnd = QDateTime::currentDateTime();
	m_nWorkTime = 0;	
	m_bSetWorkBegin = false;
	m_bSetWorkEnd = false;
	m_nNotWorkTime = 0;

}
CWorkTimeLock::~CWorkTimeLock(void)
{
}

void CWorkTimeLock::workBegin()
{
	QMutexLocker lock(&m_lockWorkTime);	
	m_fTimeWorkBegin = QDateTime::currentDateTime();
	m_fTimeWorkEnd = QDateTime::currentDateTime();
	m_bSetWorkBegin = true;
	m_bSetWorkEnd = false;

}

qint64 CWorkTimeLock::workEnd()
{
	QMutexLocker lock(&m_lockWorkTime);	
	if (m_bSetWorkBegin)
	{ 	
		m_fTimeWorkEnd = QDateTime::currentDateTime();
		m_nWorkTime = m_fTimeWorkBegin.msecsTo(m_fTimeWorkEnd);
		m_bSetWorkEnd = true;
		m_bSetWorkBegin = false;
	} 
	else
	{
		m_bSetWorkEnd = false;		
		m_nWorkTime = 0;
	}

	return m_nWorkTime;
}

qint64 CWorkTimeLock::getNotworkTime()
{
	QMutexLocker lock(&m_lockWorkTime);
	QDateTime timeNow;
	if (true == m_bSetWorkBegin && false == m_bSetWorkEnd)
	{
		timeNow = QDateTime::currentDateTime();
		m_nNotWorkTime = m_fTimeWorkBegin.msecsTo(timeNow);
	}
	else
	{
		m_nNotWorkTime = 0;
		return m_nNotWorkTime;
	}
	return m_nNotWorkTime;
}


qint64 CWorkTimeLock::getWorkTime()
{
	QMutexLocker lock(&m_lockWorkTime);
	return m_nWorkTime;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CWorkTimeNoLock::CWorkTimeNoLock(qint32 nWorkTimeCode )
{
	m_nWorkTimeCode = nWorkTimeCode;

	m_fTimeWorkBegin = QDateTime::currentDateTime();
	m_fTimeWorkEnd = QDateTime::currentDateTime();
	m_nWorkTime = 0;	
	m_bSetWorkBegin = false;
	m_bSetWorkEnd = false;
	m_nNotWorkTime = 0;

}
CWorkTimeNoLock::~CWorkTimeNoLock(void)
{
}

void CWorkTimeNoLock::workBegin()
{
	m_fTimeWorkBegin = QDateTime::currentDateTime();
	m_fTimeWorkEnd = QDateTime::currentDateTime();
	m_bSetWorkBegin = true;
	m_bSetWorkEnd = false;

}

qint64 CWorkTimeNoLock::workEnd()
{
	if (m_bSetWorkBegin)
	{ 	
		m_fTimeWorkEnd = QDateTime::currentDateTime();
		m_nWorkTime = m_fTimeWorkBegin.msecsTo(m_fTimeWorkEnd);
		m_bSetWorkEnd = true;
		m_bSetWorkBegin = false;
	} 
	else
	{
		m_bSetWorkEnd = false;		
		m_nWorkTime = 0;
	}

	return m_nWorkTime;
}

qint64 CWorkTimeNoLock::getNotworkTime()
{
	QDateTime timeNow;
	if (true == m_bSetWorkBegin && false == m_bSetWorkEnd)
	{
		timeNow = QDateTime::currentDateTime();
		m_nNotWorkTime = m_fTimeWorkBegin.msecsTo(timeNow);
	}
	else
	{
		m_nNotWorkTime = 0;
		return m_nNotWorkTime;
	}
	return m_nNotWorkTime;
}


qint64 CWorkTimeNoLock::getWorkTime()
{
	return m_nWorkTime;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////













