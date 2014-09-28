#ifndef  __CLASS__HISTORY_DATA_ACK_H__
#define  __CLASS__HISTORY_DATA_ACK_H__

#include <iostream>
#include <QtCore/QMap>
#include "Bar.h"



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
	void logInfo();
public:
	unsigned int getTimeFrom();
	unsigned int getTimeTo();
	void setBarType(BarType nBarType);
	BarType getBarType();


private:
	unsigned int m_nTimeFrom;
	unsigned int m_nTimeTo;
	std::string m_strTimeFrom;
	std::string m_strTimeTo;
};

#endif// __CLASS__HISTORY_DATA_ACK_H__



