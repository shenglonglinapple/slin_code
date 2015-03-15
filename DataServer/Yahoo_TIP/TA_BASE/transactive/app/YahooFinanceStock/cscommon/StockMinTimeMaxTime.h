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
public:
	void logInfo(const QString& fileName, qint32 lineNumber);

private:
	void _Clear();
public:
	QString m_strSymbolUse;
	QString m_strMinTime;
	QString m_strMaxTime;
	qint32 m_nCount;
	double m_fLow;
	double m_fHigh;
	double m_fCurrent;
	//%.8lf  const float EPSINON = 0.0000001;  if((x >= - EPSINON) && (x <= EPSINON) (equal)
	double m_fCurrentPercentage;//(m_fCurrent-m_fLow)/(m_fHigh-m_fLow)  no 0 
};

#endif//__CLASS_STOCK_MIN_TIME_MAX_TIME_H__
