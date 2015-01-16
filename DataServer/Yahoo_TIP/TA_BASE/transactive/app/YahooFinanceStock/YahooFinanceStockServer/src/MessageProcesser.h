#ifndef __CLASS_MESSAGE_PROCESSER_H__
#define __CLASS_MESSAGE_PROCESSER_H__

#include <QtCore/QString>
#include <QtCore/QBitArray>

class CReqLogin;
class CReqLogout;
class CReqSynYahoo;
class CReqDownLoadStock;
class CReqStockMinTimeMaxTime;
class CReqStockHistoryData;
class CReqCreateUser;
class CReqBuy;

class CAckLogin;
class CAckLogout;
class CAckSynYahoo;
class CAckDownLoadStock;
class CAckStockMinTimeMaxTime;
class CAckStockHistoryData;
class CAckCreateUser;
class CAckBuy;



class CMessageProcesser
{
public:
	CMessageProcesser(qint32 nHanle);
	~CMessageProcesser();
public:
	void processReq(const CReqLogin* pReq);
	void processReq(const CReqLogout* pReq);
	void processReq(const CReqSynYahoo* pReq);
	void processReq(const CReqDownLoadStock* pReq);
	void processReq(const CReqStockMinTimeMaxTime* pReq);
	void processReq(const CReqStockHistoryData* pReq);
	void processReq(const CReqCreateUser* pReq);
	void processReq(const CReqBuy* pReq);

public:
	void processAck(const CAckLogin* pAck);
	void processAck(const CAckLogout* pAck);
	void processAck(const CAckSynYahoo* pAck);
	void processAck(const CAckDownLoadStock* pAck);
	void processAck(const CAckStockMinTimeMaxTime* pAck);
	void processAck(const CAckStockHistoryData* pAck);
	void processAck(const CAckCreateUser* pAck);
	void processAck(const CAckBuy* pAck);

private:
	qint32 m_nHanle;
};

#endif//__CLASS_MESSAGE_PROCESSER_H__