#ifndef __CLASS_CLIENT_MESSAGE_PROCESSER_H__
#define __CLASS_CLIENT_MESSAGE_PROCESSER_H__

#include <QtCore/QString>
#include <QtCore/QBitArray>

class CReqLogin;
class CReqLogout;
class CReqSynYahoo;
class CReqDownLoadStock;
class CReqStockMinTimeMaxTime;
class CReqStockHistoryData;
class CReqCreateUser;
class CReqTrade;
class CReqHistoryTrade;
class CReqAccount;
class CReqHoldAccount;

class CAckLogin;
class CAckLogout;
class CAckSynYahoo;
class CAckDownLoadStock;
class CAckStockMinTimeMaxTime;
class CAckStockHistoryData;
class CAckCreateUser;
class CAckTrade;
class CAckHistoryTrade;
class CAckAccount;
class CAckHoldAccount;

class CClientMessageProcesser
{
public:
	CClientMessageProcesser(qint32 nHanle);
	~CClientMessageProcesser();
public:
	void processReq(const CReqLogin* pReq);
	void processReq(const CReqLogout* pReq);
	void processReq(const CReqSynYahoo* pReq);
	void processReq(const CReqDownLoadStock* pReq);
	void processReq(const CReqStockMinTimeMaxTime* pReq);
	void processReq(const CReqStockHistoryData* pReq);
	void processReq(const CReqCreateUser* pReq);
	void processReq(const CReqTrade* pReq);
	void processReq(const CReqHistoryTrade* pReq);
	void processReq(const CReqAccount* pReq);
	void processReq(const CReqHoldAccount* pReq);
	
public:
	void processAck(const CAckLogin* pAck);
	void processAck(const CAckLogout* pAck);
	void processAck(const CAckSynYahoo* pAck);
	void processAck(const CAckDownLoadStock* pAck);
	void processAck(const CAckStockMinTimeMaxTime* pAck);
	void processAck(const CAckStockHistoryData* pAck);
	void processAck(const CAckCreateUser* pAck);
	void processAck(const CAckTrade* pAck);
	void processAck(const CAckHistoryTrade* pAck);
	void processAck(const CAckAccount* pAck);
	void processAck(const CAckHoldAccount* pAck);

private:
	qint32 m_nHanle;
};

#endif//__CLASS_CLIENT_MESSAGE_PROCESSER_H__
