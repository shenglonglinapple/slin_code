#ifndef __CLASS_USER_AMOUNT_H__
#define __CLASS_USER_AMOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>


class CUserTradeInfo;
class CUserHoldAmount;

class CUserAmount
{
public:
	CUserAmount();
	virtual ~CUserAmount();
public:
	CUserAmount& operator=(const CUserAmount& objectCopy);
private:
	void _Init();
public:
	void resetUpdateTime();
	void updateLeftAmount( double fLeftAmount, const QString& strTime );
	void updateHoldAmount(double fHoldAmount, const QString& strTime);
public:
	QString m_strUserID;
	double m_fInitAmount;
	double m_fLeftAmount;
	double m_fHoldAmount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	QString m_strUpdateTime;
};


#endif //__CLASS_USER_AMOUNT_H__
