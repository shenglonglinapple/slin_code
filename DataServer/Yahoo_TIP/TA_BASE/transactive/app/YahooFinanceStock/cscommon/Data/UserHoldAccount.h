#ifndef __CLASS_USER_HOLD_ACCOUNT_H__
#define __CLASS_USER_HOLD_ACCOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CUserTradeInfo;

class CUserHoldAccount
{
public:
	CUserHoldAccount();
	virtual ~CUserHoldAccount();
public:
	CUserHoldAccount& operator=(const CUserHoldAccount& objectCopy);
private:
	void _Init();
public:
	void setValue_FirstBuy(const CUserTradeInfo* pData);
	void updateHoldAmountValue(const CUserTradeInfo* pData);
	void updatePrice(double fNewPrice, const QString& strTime);
	void logInfo( const QString& fileName, qint32 lineNumber ) const;
public:
	QString m_strUserID;
	QString m_strSymbolUse;
	double m_fPrice;
	qint32 m_nVolume;
	QString m_strTime;
	double m_fHoldAccount;
};


#endif //__CLASS_USER_HOLD_ACCOUNT_H__
