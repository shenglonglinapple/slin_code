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
	std::string m_strInstrumentCode;
	unsigned int m_nInstrumentID;
	BarType m_nBarType;
	QMap<unsigned int, Bar> m_MapBarData; //bars indexed by interval
private:
	void _ResetTimeValue();
public:
	void initTestData();
	void logInfo(const std::string& file, int line);
public:
	unsigned int getTimeFrom();
	unsigned int getTimeTo();
	void setBarType(BarType nBarType);
	BarType getBarType();
public:
	void setInstrumentID(unsigned int nInstrumentID);
	unsigned int getInstrumentID();
public:
	void onHistoryDataDownloaded(BarsPtr bars );
	void onBarDataUpdate( const BarSummary &barData );

private:
	CProjectUtilityFun* m_pUtilityFun;
	unsigned int m_nTimeFrom;
	unsigned int m_nTimeTo;
	std::string m_strTimeFrom;
	std::string m_strTimeTo;
};

#endif// __CLASS__HISTORY_DATA_ACK_H__



