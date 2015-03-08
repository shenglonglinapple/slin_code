#ifndef __CLASS_USER_ACCOUNT_H__
#define __CLASS_USER_ACCOUNT_H__

#include <QtCore/QString>
#include <QtCore/QStringList>


class CUserTradeInfo;
class CUserHoldAccount;
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
	void updateLeftAccount( double fLeftAmount, const QString& strTime );
	void updateHoldAccount(double fHoldAmount, const QString& strTime);
public:
	void setValue(const CAckAccount* pData);
	void logInfo( const QString& fileName, qint32 lineNumber ) const;
public:
	QString m_strUserID;
	double m_fInitAccount;
	double m_fLeftAccount;
	double m_fHoldAccount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	QString m_strUpdateTime;
};


#endif //__CLASS_USER_ACCOUNT_H__
