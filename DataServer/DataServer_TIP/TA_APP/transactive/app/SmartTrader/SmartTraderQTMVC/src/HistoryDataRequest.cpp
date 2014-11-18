#include "HistoryDataRequest.h"
#include "ProjectUtilityFun.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <QtCore/QDateTime>
#include "Bar.h"

#include "SmartTraderClient.h"

#include "Log4cppLogger.h"



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



CHistoryDataRequest::CHistoryDataRequest()
{
	m_pUtilityFun = NULL;

	m_nRequestType = HistoryRequestType_Time;
	m_pInstrumentRef = NULL;
	m_nBarType = FIVE_SECOND;
	m_nTimeFrom = 0;
	m_nTimeTo =0;
	m_nBarCount = 0;
	m_bSubscribe = false;	
	m_pMyTradeClientRef = NULL;

	m_pUtilityFun = new CProjectUtilityFun();
}

CHistoryDataRequest::~CHistoryDataRequest()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

	m_nRequestType = HistoryRequestType_Time;
	m_pInstrumentRef = NULL;
	m_nBarType = FIVE_SECOND;
	m_nTimeFrom = 0;
	m_nTimeTo =0;
	m_nBarCount = 0;
	m_bSubscribe = false;	
	m_pMyTradeClientRef = NULL;
}


std::string CHistoryDataRequest::_GetRequestStrValue()
{
	std::string strRequestStrValue;

	switch (m_nRequestType)
	{
	case HistoryRequestType_Time:
		{
			strRequestStrValue = "HistoryRequestType_Time";
		}
		break;
	case HistoryRequestType_NumberSubscribe:
		{
			strRequestStrValue = "HistoryRequestType_NumberSubscribe";
		}
		break;
	case HistoryRequestType_NumberTimeSubscribe:
		{
			strRequestStrValue = "HistoryRequestType_NumberTimeSubscribe";
		}
		break;
	default:
		break;
	}

	return strRequestStrValue;

}
void CHistoryDataRequest::logInfo()
{
	MYLOG4CPP_DEBUG<<" "<<"m_nRequestType="<<_GetRequestStrValue()
		<<" "<<"m_nInstrumentID="<<m_pInstrumentRef->getInstrumentID()
		<<" "<<"m_strInstrumentCode="<<m_pInstrumentRef->getInstrumentCode()
		<<" "<<"m_nBarType="<<m_nBarType
		<<" "<<"m_nTimeFrom="<<m_pUtilityFun->dateTimeToStr_Qt(m_nTimeFrom).c_str()
		<<" "<<"m_nTimeTo="<<m_pUtilityFun->dateTimeToStr_Qt(m_nTimeTo).c_str()
		<<" "<<"m_nBarCount="<<m_nBarCount
		<<" "<<"m_bSubscribe="<<m_bSubscribe
		<<" "<<"m_nRequestID="<<m_nRequestID;


	//m_strTimeTo = m_pUtilityFun->dateTimeToStr_Qt(m_nTimeTo);

}

void CHistoryDataRequest::setRequestType( enCHistoryRequestType nRequestType )
{
	m_nRequestType = nRequestType;
}

void CHistoryDataRequest::setInstrumentHandle( Instrument* pInstrumentRef )
{
	m_pInstrumentRef = pInstrumentRef;
}
void CHistoryDataRequest::setBarType(BarType nBarType)
{
	m_nBarType = nBarType;
}

void CHistoryDataRequest::setSubscribe( bool bSubscribe )
{
	m_bSubscribe = bSubscribe;

}

void CHistoryDataRequest::setBarCount( unsigned short nBarCount )
{
	m_nBarCount = nBarCount;
}

void CHistoryDataRequest::setTimeFrom( unsigned int nTimeFrom )
{
	m_nTimeFrom = nTimeFrom;
}

void CHistoryDataRequest::setTimeTo( unsigned int nTimeTo )
{
	m_nTimeTo = nTimeTo;
}
void CHistoryDataRequest::sentRequest(CSmartTraderClient* pMyTradeClient)
{
	m_pMyTradeClientRef = pMyTradeClient;
	_SentRequestToServer();
}

void CHistoryDataRequest::_SentRequestToServer()
{
	//unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int from, unsigned int to );
	//unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned short number, bool subscribe );
	//unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int fromTime, unsigned short count, bool subscribe );

	switch (m_nRequestType)
	{
	case HistoryRequestType_Time:
		{
			m_nRequestID = m_pMyTradeClientRef->downloadHistoryData(*m_pInstrumentRef, m_nBarType, m_nTimeFrom, m_nTimeTo);
		}
		break;
	case HistoryRequestType_NumberSubscribe:
		{
			m_nRequestID = m_pMyTradeClientRef->downloadHistoryData(*m_pInstrumentRef, m_nBarType, m_nBarCount, m_bSubscribe);
		}
		break;
	case HistoryRequestType_NumberTimeSubscribe:
		{
			m_nRequestID = m_pMyTradeClientRef->downloadHistoryData(*m_pInstrumentRef, m_nBarType, m_nTimeFrom, m_nBarCount, m_bSubscribe);
		}
		break;
	default:
		break;
	}

}

int CHistoryDataRequest::getBarType()
{
	return m_nBarType;
}
