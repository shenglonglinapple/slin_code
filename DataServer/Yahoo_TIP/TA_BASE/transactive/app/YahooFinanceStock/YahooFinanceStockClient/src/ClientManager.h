#ifndef __CLASS_CLIENT_MANAGER_H__
#define __CLASS_CLIENT_MANAGER_H__

#include <QtCore/QObject>

class CStockTcpClientActor;

class CClientManager : public QObject
{
	Q_OBJECT
public:
    CClientManager(QObject* parent=0);
	~CClientManager(void);
public slots:
	void slotDeleteConnection(CStockTcpClientActor* pActor);
public:	
	void createClient(int nCount);
};

#endif//__CLASS_CLIENT_MANAGER_H__
