#include "ProjectLogHelper.h"

#include "MyInstrument.h"
#include "QtTimeHelper.h"
#include "Log4cppLogger.h"



CProjectLogHelper::CProjectLogHelper( void )
{
	m_QtTimeHelper = NULL;
	m_QtTimeHelper = new CQtTimeHelper();
}

CProjectLogHelper::~CProjectLogHelper( void )
{
	if (NULL != m_QtTimeHelper)
	{
		delete m_QtTimeHelper;
		m_QtTimeHelper = NULL;
	}
}


void CProjectLogHelper::log_Instrument_info(
	const std::string& file, int line, 
	 const std::string& strLogInfo, 
	 CMyInstrument* pInstrument)
{
	unsigned int nGetInstrumentID = 0;
	std::string  strGetInstrumentCode;
	std::string  strGetUnderlyingCode;
	std::string  strGetExchangeName;
	char chGetDecimalPlace = 0;
	float fGetTickSize = 0;
	float fGetTickValue = 0;
	int nGetBidVolume = 0;
	int nGetAskVolume = 0;
	int nGetLastVolume = 0;
	int nGetTotalVolume = 0;
	float fGetBidPrice = 0;
	float fGetAskPrice = 0;
	float fGetLowPrice = 0;
	float fGetHighPrice = 0;
	float fGetLastPrice = 0;
	float fGetOpeningPrice = 0;
	float fGetSettlementPrice = 0;
	unsigned int timeGetUpdateTime = 0;//time
	std::string strGetupdateTime;
	double fGetValuePerPoint = 0;
	int nGetLegSize = 0;
	unsigned int nGetLegSecurityID = 0;
	int nGetMarketStatus = 0;
	int nGetSecurityType = 0;
	unsigned int nGetOrderTypes = 0;

}

//QT_END_NAMESPACE

















