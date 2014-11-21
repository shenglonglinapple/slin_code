#ifndef  __CLASS__HISTORY_DATA_REQUEST_H__
#define  __CLASS__HISTORY_DATA_REQUEST_H__

#include <iostream>
#include <QtCore/QMap>
#include "Bar.h"

class Instrument;
class CProjectUtilityFun;
class CSmartTraderClient;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CHistoryDataRequest
{
public:
	CHistoryDataRequest();
	~CHistoryDataRequest();
public:
	enum enCHistoryRequestType
	{
		HistoryRequestType_Time,
		HistoryRequestType_NumberSubscribe,
		HistoryRequestType_NumberTimeSubscribe,
	};
public:
	enCHistoryRequestType m_nRequestType;
	Instrument* m_pInstrumentRef;
	BarType m_nBarType;
	bool m_bSubscribe;
	unsigned short m_nBarCount;
	unsigned int m_nTimeFrom;
	unsigned int m_nTimeTo;
	CSmartTraderClient* m_pMyTradeClientRef;
public:
	unsigned int m_nRequestID;
public:
	void logInfo(const std::string& file, int line);
	int getBarType();
public:
	void setRequestType(enCHistoryRequestType nRequestType);
	void setInstrumentHandle(Instrument* pInstrumentRef);
	void setBarType(BarType nBarType);
	void setTimeFrom(unsigned int nTimeFrom);
	void setTimeTo(unsigned int nTimeTo);
	void setBarCount(unsigned short nBarCount);
	void setSubscribe(bool bSubscribe);
	void sentRequest(CSmartTraderClient* pMyTradeClient);
private:
	void _SentRequestToServer();
	std::string _GetRequestStrValue();
private:
	CProjectUtilityFun* m_pUtilityFun;
};

#endif// __CLASS__HISTORY_DATA_REQUEST_H__



