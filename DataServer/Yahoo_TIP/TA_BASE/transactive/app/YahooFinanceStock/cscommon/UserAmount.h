#ifndef __CLASS_USER_AMOUNT_H__
#define __CLASS_USER_AMOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

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
public:
	QString m_strUserID;
	double m_fInitAmount;
	double m_fLeftAmount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	double m_fFloatingAmount;
	QString m_strUpdateTime;
};


#endif //__CLASS_USER_AMOUNT_H__
