#ifndef  __CLASS__HISTORY_DATA_ACK_H__
#define  __CLASS__HISTORY_DATA_ACK_H__

#include <iostream>
#include <QtCore/QMap>
#include "Bar.h"


class Instrument;
class CProjectUtilityFun;

class CHistoryDataACK
{
public:
	CHistoryDataACK();
	~CHistoryDataACK();
public:
	Instrument* m_pInstrument;
	BarType m_nBarType;
public:
	unsigned int m_nFromTime;
	unsigned int m_nToTime;
	int m_nBarTypeSeconds;
	std::string m_strInstrumentCode;
	unsigned int m_nInstrumentID;
	unsigned int m_nRequestID;
	QMap<unsigned int, Bar> m_MapBarData; //bars indexed by interval
public:
	void initTestData();

public:
	void logInfo();
	void onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars );
private:
	CProjectUtilityFun* m_pUtilityFun;
};

#endif// __CLASS__HISTORY_DATA_ACK_H__



