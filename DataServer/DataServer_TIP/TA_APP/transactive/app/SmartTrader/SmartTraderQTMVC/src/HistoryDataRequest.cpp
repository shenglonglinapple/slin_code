#include "HistoryDataRequest.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


CHistoryDataRequest::CHistoryDataRequest()
{
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

	m_nInstrumentID = 0;
	m_nBarType = FIVE_MINUTE;//5 * 60
	m_nBarTypeSeconds = m_nBarType;
	


	
}

CHistoryDataRequest::~CHistoryDataRequest()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}
	m_nInstrumentID = 0;
	m_nBarType = FIVE_MINUTE;//5 * 60
	m_nBarTypeSeconds = m_nBarType;
}

void CHistoryDataRequest::logInfo()
{
	if (HistoryRequestType_0_From_To == m_nRequestType)
	{
		LOG_DEBUG<<" "<<"HistoryRequestType_0_From_To"
			<<" "<<"m_nRequestID="<<m_nRequestID
			<<" "<<"m_nBarType="<<m_nBarType
			<<" "<<"m_nInstrumentID="<<m_nInstrumentID
			<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode
			<<" "<<"nFromTime="<<m_pUtilityFun->dataTimeToStr(m_nFromTime_Type0).c_str()
			<<" "<<"nToTime="<<m_pUtilityFun->dataTimeToStr(m_nToTime_Type0).c_str();
	}


}

