#include "DataUserAccount.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"
#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"


CDataUserAccount* CDataUserAccount::m_pInstance = 0;
QMutex CDataUserAccount::m_mutexInstance;

CDataUserAccount& CDataUserAccount::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserAccount();
	}
	return (*m_pInstance);
}

void CDataUserAccount::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserAccount::CDataUserAccount()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();


	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.clear();
	}
}

CDataUserAccount::~CDataUserAccount()
{
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}


	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.clear();
	}
}




void CDataUserAccount::onAccountDownloaded( Account& account )
{
	{
		QMutexLocker lock(&m_mutexForMapAccount);
		m_MapAccount.insert(account.getAccountID(), &account);
	}
}

Account* CDataUserAccount::getAccount(int nAccountID)
{
	Account* pAccount = NULL;
	QMutexLocker lock(&m_mutexForMapAccount);
	if (m_MapAccount.isEmpty())
	{
		MYLOG4CPP_ERROR<<" "<<"m_MapAccount is empty";
		pAccount = NULL;
		return pAccount;
	}
	pAccount = m_MapAccount.begin().value();

	return pAccount;
}


