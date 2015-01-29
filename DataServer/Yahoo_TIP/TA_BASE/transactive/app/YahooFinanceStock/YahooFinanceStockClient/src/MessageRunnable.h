#ifndef __CLASS_MESSAGE_RUNNABLE_H__
#define __CLASS_MESSAGE_RUNNABLE_H__

#include <QtCore/QRunnable>
#include <QtCore/QBitArray>

class CMessageProcesser;

class CMessageRunnable : public QRunnable
{
public:
	CMessageRunnable(qint32 nHanle, QByteArray* pMessage);
	~CMessageRunnable();
protected:
	//This is not a thread. This is a task executed on a thread, in a threadpool
	void run(); 
private:
	void _ProcessMessage();
private:
	void _ProcessMessage_Req(qint32 nMessageType, qint32 nDataType);
	void _ProcessMessage_ReqLogin();
	void _ProcessMessage_ReqLogout();
	void _ProcessMessage_ReqSynYahoo();
	void _ProcessMessage_ReqDownLoadStock();
	void _ProcessMessage_ReqStockMinTimeMaxTime();
	void _ProcessMessage_ReqStockHistoryData();
	void _ProcessMessage_ReqCreateUser();
	void _ProcessMessage_ReqTrade();
	void _ProcessMessage_ReqDownLoadTrade();
	void _ProcessMessage_ReqHistoryTrade();
	void _ProcessMessage_ReqAccount();
private:
	void _ProcessMessage_Ack(qint32 nMessageType, qint32 nDataType);
	void _ProcessMessage_AckLogin();
	void _ProcessMessage_AckLogout();
	void _ProcessMessage_AckSynYahoo();
	void _ProcessMessage_AckDownLoadStock();
	void _ProcessMessage_AckStockMinTimeMaxTime();
	void _ProcessMessage_AckStockHistoryData();
	void _ProcessMessage_AckCreateUser();
	void _ProcessMessage_AckTrade();
	void _ProcessMessage_AckDownLoadTrade();
	void _ProcessMessage_AckHistoryTrade();
	void _ProcessMessage_AckAccount();

private:
	qint32 m_nHanle;
	QByteArray* m_pMessage; 
	CMessageProcesser* m_pMessageProcesser;
};

#endif//__CLASS_MESSAGE_RUNNABLE_H__
