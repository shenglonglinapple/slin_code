#ifndef __CLASS_MESSAGE_MANAGER_HH__
#define __CLASS_MESSAGE_MANAGER_HH__

#include <QtCore/QObject>

class QByteArray;
class QThreadPool;

class CMessageManager : public QObject
{
	Q_OBJECT
public:
	CMessageManager(QObject* parent = 0);
	~CMessageManager();
signals:
	void signalSendMessage(qint32 handle, QByteArray* pMessage);

public slots:
	void slotRecvMessage(qint32 handle, QByteArray* pMessage);
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);
public:
	void sendReqLogin(qint32 handle,	const QString& strUserName,	const QString& strPassWord);
	void sendReqSynYahoo( qint32 handle, const QString& strSymbolUse);
private:
	QThreadPool* m_pThreadPool;
};
#endif  // __CLASS_MESSAGE_MANAGER_HH__



