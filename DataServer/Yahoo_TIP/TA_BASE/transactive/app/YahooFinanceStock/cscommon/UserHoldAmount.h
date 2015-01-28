#ifndef __CLASS_USER_HOLD_AMOUNT_H__
#define __CLASS_USER_HOLD_AMOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CUserTradeInfo;

class CUserHoldAmount
{
public:
	CUserHoldAmount();
	virtual ~CUserHoldAmount();
public:
	CUserHoldAmount& operator=(const CUserHoldAmount& objectCopy);
private:
	void _Init();
public:
	void setValue_FirstBuy(const CUserTradeInfo* pData);
	void updateValue(const CUserTradeInfo* pData);
	void updatePrice(double fNewPrice, const QString& strTime);
public:
	QString m_strUserID;
	QString m_strSymbolUse;
	double m_fPrice;
	qint32 m_nVolume;
	QString m_strTime;
	double m_fAmount;
};


#endif //__CLASS_USER_HOLD_AMOUNT_H__
