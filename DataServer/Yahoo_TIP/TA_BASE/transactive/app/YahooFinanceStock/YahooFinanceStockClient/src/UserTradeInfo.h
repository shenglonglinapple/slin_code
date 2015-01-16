#ifndef __CLASS_USER_TRADE_INFO_H__
#define __CLASS_USER_TRADE_INFO_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CReqBuy;
class CAckBuy;

class CUserTradeInfo
{
public:
	CUserTradeInfo();
	virtual ~CUserTradeInfo();
public:
	CUserTradeInfo& operator=(const CUserTradeInfo& objectCopy);
private:
	void _Init();
public:
	void setValue(const QString& strUseID, const CReqBuy* pReq );

public:
	void setValue(const CAckBuy* pAck);

public:
	QString m_strUseID;
	QString m_strTradeUUID;
	QString m_strTradeTime;
	qint32 m_nTradeType;
	QString m_strSymbolUse;
	double m_fTradePrice;
	qint32 m_nTradeVolume;
	double m_fTradeAmount;
	double m_fTradeFees;
	double m_fTotalTradeFee;
	double m_fTotalTradeAmount;

};


#endif //__CLASS_USER_TRADE_INFO_H__
