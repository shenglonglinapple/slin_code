#ifndef __CLASS_MESSAGE_RUNNABLE_H__
#define __CLASS_MESSAGE_RUNNABLE_H__

#include <QtCore/QRunnable>
#include <QtCore/QBitArray>

class CReqLogin;
class CReqLogout;
class CReqSynYahoo;


class CAckLogin;
class CAckLogout;
class CAckSynYahoo;

class CMessageManager;


class CMessageRunnable : public QRunnable
{
public:
	CMessageRunnable(qint32 nHanle, QByteArray* pMessage);
	~CMessageRunnable();
protected:
	//This is not a thread. This is a task executed on a thread, in a threadpool
	void run(); 
public:
	void setHanle(CMessageManager* pHanleRef);
private:
	void _ProcessMessage();
private:
	void _ProcessMessage_Req(qint32 nMessageType, qint32 nDataType);
	void _ProcessMessage_ReqLogin();
	void _ProcessMessage_ReqLogout();
	void _ProcessMessage_ReqSynYahoo();
private:
	void _ProcessMessage_Ack(qint32 nMessageType, qint32 nDataType);
	void _ProcessMessage_AckLogin();
	void _ProcessMessage_AckLogout();
	void _ProcessMessage_AckSynYahoo();


public:
	void _ProcessReq(const CReqLogin* pReq);
	void _ProcessReq(const CReqLogout* pReq);
	void _ProcessReq(const CReqSynYahoo* pReq);
public:
	void processAck(const CAckLogin* pAck);
	void processAck(const CAckLogout* pAck);
	void processAck(const CAckSynYahoo* pAck);

private:
	qint32 m_nHanle;
	QByteArray* m_pMessage; 
	CMessageManager* pMessageManagerRef;
};

#endif//__CLASS_MESSAGE_RUNNABLE_H__
