#ifndef __CLASS_CLIENT_ACTOR_H__
#define __CLASS_CLIENT_ACTOR_H__

#include <QtCore/QObject>

#include "ClientActorParam.h"
#include "MyQtThread.h"

class CClientWorker;
class QByteArray;

class CClientActor : public CMyQtThread
{
	Q_OBJECT
public:
	CClientActor(const CClientActorParam& param, QObject* parent=0);
	virtual ~CClientActor();
public:
	virtual void run();	
	virtual void terminate();
signals:
	void signalConnectToServer();
public:
	void sendMessage(qint32 nHandle, QByteArray* pMessage);
public slots:
	void slotConnected(qint32 nHandle);
	void slotDisconnected(qint32 nHandle);
private:
	CClientWorker* m_pClientWorker;
	CClientActorParam m_ClientActorParam;
};


#endif //__CLASS_CLIENT_ACTOR_H__
