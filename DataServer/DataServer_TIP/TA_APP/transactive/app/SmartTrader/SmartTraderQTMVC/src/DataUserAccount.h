#ifndef __CLASS_DATA_USER_ACCOUNT_HH__
#define __CLASS_DATA_USER_ACCOUNT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "Account.h"

class CProjectLogHelper;


class CDataUserAccount
{ 
public:
	static CDataUserAccount& getInstance();
	static void removeInstance();

private:
	static CDataUserAccount* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserAccount(); 
	virtual ~CDataUserAccount(); 
public:
	void onAccountDownloaded( Account& account );
	Account* getAccount(int nAccountID);
private:
	QMutex m_mutexForMapAccount;
	QMap<int, Account*> m_MapAccount;//AccountID
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_USER_ACCOUNT_HH__



