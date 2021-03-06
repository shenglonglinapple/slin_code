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
std::string CProjectLogHelper::getStdString(const std::string& strValue)
{
	return strValue;
}
std::string CProjectLogHelper::getStdString(const QString& strValue)
{
	return strValue.toStdString();
}

void CProjectLogHelper::log_MyInstrument_info(
	const std::string& file, int line, 
	 const std::string& strLogInfo, 
	 CMyInstrument* pInstrument)
{
	CQtTimeHelper timeHelper;

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



	nGetInstrumentID = pInstrument->getInstrumentID();
	strGetInstrumentCode = pInstrument->getInstrumentCode();
	strGetUnderlyingCode = pInstrument->getUnderlyingCode();
	strGetExchangeName = pInstrument->getExchangeName();
	chGetDecimalPlace = pInstrument->getDecimalPlace();
	fGetTickSize = pInstrument->getTickSize();
	fGetTickValue = pInstrument->getTickValue();
	nGetBidVolume = pInstrument->getBidVolume();
	nGetAskVolume = pInstrument->getAskVolume();
	nGetLastVolume = pInstrument->getLastVolume();
	nGetTotalVolume = pInstrument->getTotalVolume();
	fGetBidPrice = pInstrument->getBidPrice();
	fGetAskPrice = pInstrument->getAskPrice();
	fGetLowPrice = pInstrument->getLowPrice();
	fGetHighPrice = pInstrument->getHighPrice();
	fGetLastPrice = pInstrument->getLastPrice();
	fGetOpeningPrice = pInstrument->getOpeningPrice();
	fGetSettlementPrice = pInstrument->getSettlementPrice();
	timeGetUpdateTime = pInstrument->getUpdateTime();
	strGetupdateTime = timeHelper.dateTimeToStr_Qt(timeGetUpdateTime);
	fGetValuePerPoint = pInstrument->getValuePerPoint();
	nGetLegSize = pInstrument->getLegSize();
	//nGetLegSecurityID = pInstrument->getLegSecurityID();
	nGetMarketStatus = pInstrument->getMarketStatus();
	nGetSecurityType = pInstrument->getSecurityType();
	nGetOrderTypes = pInstrument->getOrderTypes();


	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<strLogInfo
		<<" "<<"nGetInstrumentID="<<nGetInstrumentID
		<<" "<<"strGetInstrumentCode="<<strGetInstrumentCode
		<<" "<<"strGetUnderlyingCode="<<strGetUnderlyingCode
		<<" "<<"strGetExchangeName="<<strGetExchangeName
		<<" "<<"chGetDecimalPlace="<<chGetDecimalPlace
		<<" "<<"fGetTickSize="<<fGetTickSize
		<<" "<<"fGetTickValue="<<fGetTickValue
		<<" "<<"nGetBidVolume="<<nGetBidVolume
		<<" "<<"nGetAskVolume="<<nGetAskVolume
		<<" "<<"nGetLastVolume="<<nGetLastVolume
		<<" "<<"nGetTotalVolume="<<nGetTotalVolume
		<<" "<<"fGetBidPrice="<<fGetBidPrice
		<<" "<<"fGetAskPrice="<<fGetAskPrice
		<<" "<<"fGetLowPrice="<<fGetLowPrice
		<<" "<<"fGetHighPrice="<<fGetHighPrice
		<<" "<<"fGetLastPrice="<<fGetLastPrice
		<<" "<<"fGetOpeningPrice="<<fGetOpeningPrice
		<<" "<<"fGetSettlementPrice="<<fGetSettlementPrice
		<<" "<<"fGetBidPrice="<<fGetBidPrice
		<<" "<<"timeGetUpdateTime="<<timeGetUpdateTime
		<<" "<<"strGetupdateTime="<<strGetupdateTime		
		<<" "<<"fGetValuePerPoint="<<fGetValuePerPoint
		<<" "<<"nGetLegSize="<<nGetLegSize
		//<<" "<<"nGetLegSecurityID="<<nGetLegSecurityID
		<<" "<<"nGetMarketStatus="<<nGetMarketStatus
		<<" "<<"nGetSecurityType="<<nGetSecurityType
		<<" "<<"nGetOrderTypes="<<nGetOrderTypes;
}

//QT_END_NAMESPACE

















