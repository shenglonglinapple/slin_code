#ifndef  __CLASS__HISTORY_DATA_ACK_H__
#define  __CLASS__HISTORY_DATA_ACK_H__

#include <QtCore/QMap>
#include "MyBar.h"

class CDataHistoryQuotes
{
public:
	CDataHistoryQuotes();
	~CDataHistoryQuotes();
public:
	std::string m_strInstrumentCode;//KEY
	unsigned int m_nInstrumentID;//KEY
	EMyBarType m_nBarType;//KEY

	QMap<unsigned int, CMyBar> m_MapBarData; //bars indexed by interval
private:
	void _ResetTimeValue();
public:
	void initTestData();
	void logInfo(const std::string& file, int line);
public:
	unsigned int getTimeFrom();
	unsigned int getTimeTo();
	void setBarType(EMyBarType nBarType);
	EMyBarType getBarType();
public:
	void onHistoryDataDownloaded(pSetMyBarsPtr bars );
	void onBarDataUpdate( const CMyBarSummary &barData );

private:
	unsigned int m_nTimeFrom;
	unsigned int m_nTimeTo;
	std::string m_strTimeFrom;
	std::string m_strTimeTo;

};

#endif// __CLASS__HISTORY_DATA_ACK_H__



