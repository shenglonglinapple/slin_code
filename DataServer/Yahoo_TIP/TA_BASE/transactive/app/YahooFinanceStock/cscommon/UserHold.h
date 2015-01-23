#ifndef __CLASS_USER_HOLD_H__
#define __CLASS_USER_HOLD_H__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include "TcpComProtocol.h"

class CUserTradeInfo;

class CUserHold
{
public:
	CUserHold();
	virtual ~CUserHold();
public:
	CUserHold& operator=(const CUserHold& objectCopy);
public:
	void clear();
public:
	void setValue(const CUserTradeInfo* pData);
public:
	//TABLE_USER_HOLD
	QString m_strUserID;
	QString m_strSymbolUse;

	QString m_strBuyUUID;
	QString m_strBuyTime;
	double m_fBuyPrice;
	qint32 m_nBuyVolume;
	double m_fBuyFees;//0.007
	double m_fBuyAmount;//(m_fBuyPrice*m_nBuyVolume)(1+m_fBuyFees)

	QString m_strCurrentTime;
	double m_fCurrentPrice;
	double m_fCurrentFees;//0.007
	double m_fCurrentAmount;//(m_fCurrentPrice*m_nBuyVolume)(1-m_fCurrentFees)

	double m_fProfitLoss;//m_fCurrentAmount-m_fBuyAmount
	double m_fProfitLossPersentage;//(m_fCurrentAmount-m_fBuyAmount)/m_fBuyAmount
};


#endif //__CLASS_USER_HOLD_H__
