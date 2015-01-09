#ifndef __CLASS_SERVER_COM_MANAGER_HH__
#define __CLASS_SERVER_COM_MANAGER_HH__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

class CServerComWorker;
class QByteArray;

class CServerComManager : public QObject
{
	Q_OBJECT
public:
	CServerComManager(QObject* parent = 0);
	~CServerComManager();
signals:
	void signalRecvMessage(qint32 handle, QByteArray* pMessage);

public slots:
	void slotRecvMessage(qint32 handle, QByteArray* pMessage);
	void slotDisconnected(qint32 handle);
public slots:
	void slotSendMessage(qint32 handle, QByteArray* pMessage);
public:
	void incomingConnection(qint32 handle);


private:
	QMutex m_mutex_MapServerComWorker;
	QMap<qint32, CServerComWorker*> m_MapServerComWorker;

};
#endif  // __CLASS_SERVER_COM_MANAGER_HH__



