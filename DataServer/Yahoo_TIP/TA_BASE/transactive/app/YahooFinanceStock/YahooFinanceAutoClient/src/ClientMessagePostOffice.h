#ifndef __CLASS_CLIENT_MESSAGE_POST_OFFICE_HH__
#define __CLASS_CLIENT_MESSAGE_POST_OFFICE_HH__

#include <QtCore/QObject>

class QByteArray;
class QThreadPool;

class CClientMessagePostOffice : public QObject
{
	Q_OBJECT
public:
	CClientMessagePostOffice(QObject* parent = 0);
	~CClientMessagePostOffice();
signals:
	void signalSendMessage(qint32 handle, QByteArray* pMessage);
public slots:
	void slotRecvMessage(qint32 handle, QByteArray* pMessage);
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);
private:
	QThreadPool* m_pThreadPool;//Post Office Worker
};
#endif  // __CLASS_CLIENT_MESSAGE_POST_OFFICE_HH__



