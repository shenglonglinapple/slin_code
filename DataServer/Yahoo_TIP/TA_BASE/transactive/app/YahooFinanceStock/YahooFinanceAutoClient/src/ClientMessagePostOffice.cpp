#include "ClientMessagePostOffice.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThreadPool>
#include "Log4cppLogger.h"

#include "ClientMessageRunnable.h"


CClientMessagePostOffice::CClientMessagePostOffice( QObject* parent /*= 0*/ )
{
	m_pThreadPool = NULL;
	m_pThreadPool = new QThreadPool(this);
	//How many threads I want at any given time
	//If there are more connections, they will be queued until a threads is closed
	m_pThreadPool->setMaxThreadCount(1);
}

CClientMessagePostOffice::~CClientMessagePostOffice()
{
	if (NULL != m_pThreadPool)
	{
		delete m_pThreadPool;
		m_pThreadPool = NULL;
	}
}


void CClientMessagePostOffice::slotRecvMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageManager"
		<<" "<<"fun:"<<" "<<"slotRecvMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	CClientMessageRunnable* pMessageRunnable = NULL;
	pMessageRunnable = new CClientMessageRunnable(handle, pMessage);
	//Delete that object when you're done (instead of using signals and slots)
	pMessageRunnable->setAutoDelete(true);

	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool begin start()";

	m_pThreadPool->start(pMessageRunnable);
	pMessageRunnable = NULL;

	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool end start()";
}

void CClientMessagePostOffice::sendMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageManager"
		<<" "<<"fun:"<<" "<<"sendMessage"
		<<" "<<"emit:"<<" "<<"signalSendMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"pMessage=0x"<<pMessage;

	emit signalSendMessage(handle, pMessage);
}

