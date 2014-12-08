#ifndef __CLASS_HISTORY_DATA_H__
#define __CLASS_HISTORY_DATA_H__

#include <string>

#include <QtCore/QString>
#include <QtCore/QStringList>



class CHistoryData
{
public:
	CHistoryData();
	virtual ~CHistoryData();
public:
	/*
	Date,Open,High,Low,Close,Volume,Adj Close
	2014-11-14,9.27,9.27,9.27,9.27,000,9.27
	*/
	void resetValue(const QString& strLine);
private:
	void _Init();
public:
	QString m_strDate;
	QString m_strOpen;
	QString m_strHigh;
	QString m_strLow;
	QString m_strClose;
	QString m_strVolume;
	QString m_strAdjClose;
};


#endif //__CLASS_SQLITE_DB_OPER_H__
