#ifndef __CLASS_STOCK_MIN_TIME_MAX_TIME_H__
#define __CLASS_STOCK_MIN_TIME_MAX_TIME_H__

#include <QtCore/QString>


class CStockMinTimeMaxTime
{
public:
    CStockMinTimeMaxTime(void);
	~CStockMinTimeMaxTime(void);

public:
	CStockMinTimeMaxTime& operator=(const CStockMinTimeMaxTime& objectCopy);
private:
	void _Clear();
public:
	QString m_strSymbolUse;
	QString m_strMinTime;
	QString m_strMaxTime;
	qint32 m_nCount;
};

#endif//__CLASS_STOCK_MIN_TIME_MAX_TIME_H__
