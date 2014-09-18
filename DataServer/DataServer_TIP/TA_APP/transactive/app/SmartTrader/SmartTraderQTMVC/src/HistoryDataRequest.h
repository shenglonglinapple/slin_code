#ifndef  __CLASS__HISTORY_DATA_REQUEST_H__
#define  __CLASS__HISTORY_DATA_REQUEST_H__

#include <iostream>
#include <QtCore/QMap>
#include "Bar.h"

class Instrument;
class CProjectUtilityFun;

class CHistoryDataRequest
{
public:
	CHistoryDataRequest();
	~CHistoryDataRequest();
public:
	enum enCHistoryRequestType
	{
		HistoryRequestType_0_From_To,
		HistoryRequestType_1_Number_Subscribe,
		HistoryRequestType_2_Number_From_Count_Subscribe,
	};
public:
	enCHistoryRequestType m_nRequestType;
public:
	Instrument* m_pInstrument;
	BarType m_nBarType;
public:
	//RequestType_From_To
	unsigned int m_nFromTime_Type0;
	unsigned int m_nToTime_Type0;
public:
	//RequestType_Number_Subscribe
	unsigned short m_nNumber_Type1;
	bool m_bSubscribe_Type1;
public:
	//RequestType_Number_From_Count_Subscribe
	unsigned int m_nFromTime_Type2;
	unsigned short m_nCount_Type2;
	bool m_bSubscribe_Type2;
public:
	int m_nBarTypeSeconds;
	std::string m_strInstrumentCode;
	unsigned int m_nInstrumentID;
public:	
	unsigned int m_nRequestID;
public:
	void logInfo();
private:
	CProjectUtilityFun* m_pUtilityFun;
};

#endif// __CLASS__HISTORY_DATA_REQUEST_H__



