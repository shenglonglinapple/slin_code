#ifndef __CLASS_CREATE_REQ_HELPER__HH__
#define __CLASS_CREATE_REQ_HELPER__HH__

#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>


#include "TcpComProtocol.h"

class QByteArray;
class CUserTradeInfo;

class CCreateReqHelper
{
public:
	CCreateReqHelper(void);
	~CCreateReqHelper(void);
public:
	QByteArray* create_req_ReqCreateUser(const QString& strUserName, const QString& strPassWord);
	QByteArray* create_req_ReqLogin(const QString& strUserName, const QString& strPassWord);
	QByteArray* create_req_ReqDownLoadStock();
	QByteArray* create_req_ReqStockMinTimeMaxTime(const QString& strSymbolUse);
	QByteArray* create_req_ReqHistoryTrade(const QString& strUserID, const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType );
	QByteArray* create_req_ReqUserAccount(const QString& strUserID, const QString& strTime);
	QByteArray* create_req_ReqUserHoldAccount( const QString& strUserID, const QString& strSymbolUse );
	QByteArray* create_req_ReqSynYahoo(const QString& strSymbolUse);
	QByteArray* create_req_ReqStockHistoryData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo);
	QByteArray* create_req_NewOrder(const CUserTradeInfo* pData);
};

//QT_END_NAMESPACE

#endif //__CLASS_CREATE_REQ_HELPER__HH__


