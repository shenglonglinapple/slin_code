#ifndef __CLASS_USER_ACCOUNT_H__
#define __CLASS_USER_ACCOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>


class CUserTradeInfo;
class CUserHoldAmount;
class CAckAccount;

class CUserAccount
{
public:
	CUserAccount();
	virtual ~CUserAccount();
public:
	CUserAccount& operator=(const CUserAccount& objectCopy);
private:
	void _Init();
public:
	void resetUpdateTime();
	void updateLeftAmount( double fLeftAmount, const QString& strTime );
	void updateHoldAmount(double fHoldAmount, const QString& strTime);
public:
	void setValue(const CAckAccount* pData);
public:
	QString m_strUserID;
	double m_fInitAmount;
	double m_fLeftAmount;
	double m_fHoldAmount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	QString m_strUpdateTime;
};


#endif //__CLASS_USER_ACCOUNT_H__
