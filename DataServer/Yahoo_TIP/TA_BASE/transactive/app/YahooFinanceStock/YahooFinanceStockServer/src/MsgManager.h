#ifndef __CLASS_MSG_MANAGER_H__
#define __CLASS_MSG_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QBitArray>

class CMsgProcesser;

class CMsgManager : public QObject
{
    Q_OBJECT

public:
    CMsgManager(QObject* parent=0);
	~CMsgManager();
signals:
	void signalWriteMessage(QByteArray* pByteArray);

public slots:
	void slotProcessMessage(QByteArray* pMessage);
private:
	void _ProcessMessage_ReqLogin(const QByteArray* pMessage );
	void _ProcessMessage_ReqLogout(const QByteArray* pMessage );
private:
	CMsgProcesser* m_pServerMsgProcesser;

};

#endif//__CLASS_MSG_MANAGER_H__
