#include "HistoryDataRequest.h"

#include "QtTimeHelper.h"
#include "Log4cppLogger.h"


CHistoryDataRequest::CHistoryDataRequest()
{
	m_nRequestType = HistoryRequestType_Time;
	m_nBarType = FIVE_SECOND;
	m_nTimeFrom = 0;
	m_nTimeTo =0;
	m_nBarCount = 0;
	m_bSubscribe = false;	

}

CHistoryDataRequest::~CHistoryDataRequest()
{
	m_nRequestType = HistoryRequestType_Time;
	m_nBarType = FIVE_SECOND;
	m_nTimeFrom = 0;
	m_nTimeTo =0;
	m_nBarCount = 0;
	m_bSubscribe = false;	

}

CHistoryDataRequest& CHistoryDataRequest::operator=( const CHistoryDataRequest& objectCopy )
{
	m_nRequestType = objectCopy.m_nRequestType;
	m_nBarType = objectCopy.m_nBarType;
	m_nTimeFrom = objectCopy.m_nTimeFrom;
	m_nTimeTo = objectCopy.m_nTimeTo;
	m_nBarCount = objectCopy.m_nBarCount;
	m_bSubscribe = objectCopy.m_bSubscribe;

	m_nRequestID = objectCopy.m_nRequestID;
	m_strInstrumentCode = objectCopy.m_strInstrumentCode;
	m_nInstruemntID = objectCopy.m_nInstruemntID;


	return *this;
}

std::string CHistoryDataRequest::_GetRequestStrValue()
{
	std::string strRequestStrValue;
	switch (m_nRequestType)
	{
	case HistoryRequestType_Time:
		strRequestStrValue = "HistoryRequestType_Time";
		break;
	default:
		break;
	}
	return strRequestStrValue;
}

void CHistoryDataRequest::logInfo(const std::string& file, int line)
{
	CQtTimeHelper qtTimehelper;
	
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"m_nBarType="<<m_nBarType
		<<" "<<"m_nTimeFrom="<<qtTimehelper.dateTimeToStr_Qt(m_nTimeFrom)
		<<" "<<"m_nTimeTo="<<qtTimehelper.dateTimeToStr_Qt(m_nTimeTo)
		<<" "<<"m_nBarCount="<<m_nBarCount
		<<" "<<"m_bSubscribe="<<m_bSubscribe
		<<" "<<"m_nRequestID="<<m_nRequestID;
}
