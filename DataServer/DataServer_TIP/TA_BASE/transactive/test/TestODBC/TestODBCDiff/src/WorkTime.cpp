#include "WorkTime.h"







//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CAWorkTime::CAWorkTime()
{

}
CAWorkTime::~CAWorkTime()
{

}

std::string CAWorkTime::getCurrentTime( struct timeb* pfbtime )
{
	struct tm*			pTm = NULL;
	std::string			strCurrentTime;

	if (NULL != pfbtime)
	{
		ftime(pfbtime);	
		
		//format to string
		/*
		char szCurTime[256] = {0};
		pTm = localtime(&(pfbtime->time));
		if ( NULL != pTm && NULL != pfbtime)
		{
			sprintf(szCurTime, "[%02d/%02d/%02d %02d:%02d:%02d:%03d]",
				pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,
				pTm->tm_hour, pTm->tm_min, pTm->tm_sec, pfbtime->millitm); 

			strCurrentTime = szCurTime;     
		}
		TA_DB_Sync::trim(strCurrentTime);
		*/

	}
	return strCurrentTime;
}

UBigInt64 CAWorkTime::getDiffTime( struct timeb* pfbtimeBegin, struct timeb* pfbtimeEnd )
{
	UBigInt64             nDiffTimeRes = 0;
	time_t				diffSeconds;

	if (NULL != pfbtimeBegin && NULL != pfbtimeEnd)
	{
		diffSeconds = pfbtimeEnd->time - pfbtimeBegin->time;
		nDiffTimeRes = (UBigInt64)(diffSeconds*1000.0 + pfbtimeEnd->millitm - pfbtimeBegin->millitm);//double
	}

	//format to str		
	//char szCurTime[256] = {0};
	//sprintf(szCurTime, "%10.3f ms", diffAll); 
	//strDiffTime =	szCurTime;
	//TA_DB_Sync::trim(strDiffTime);


	return nDiffTimeRes;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CWorkTimeNoLock::CWorkTimeNoLock(int nWorkTimeCode )
{
	m_nWorkTimeCode = nWorkTimeCode;	
	getCurrentTime(&m_fTimeWorkBegin);
	getCurrentTime(&m_fTimeWorkEnd);
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
	int nFunRes = 0;
	getCurrentTime(&m_fTimeWorkBegin);
	getCurrentTime(&m_fTimeWorkEnd);
	m_bSetWorkBegin = true;
	m_bSetWorkEnd = false;

	return;
}

UBigInt64 CWorkTimeNoLock::workEnd()
{
	int nFunRes = 0;

	if (m_bSetWorkBegin)
	{ 	
		getCurrentTime(&m_fTimeWorkEnd);
		m_nWorkTime = getDiffTime(&m_fTimeWorkBegin, &m_fTimeWorkEnd);

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

UBigInt64 CWorkTimeNoLock::getNotworkTime()
{
	int nFunRes = 0;
	struct timeb m_fTimeNow;


	if (true == m_bSetWorkBegin && false == m_bSetWorkEnd)
	{
		getCurrentTime(&m_fTimeNow);
		m_nNotWorkTime = getDiffTime(&m_fTimeWorkBegin, &m_fTimeNow);
	}
	else
	{
		m_nNotWorkTime = 0;
		return m_nNotWorkTime;
	}



	return m_nNotWorkTime;
}


UBigInt64 CWorkTimeNoLock::getWorkTime()
{
	int nFunRes = 0;
	return m_nWorkTime;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////










