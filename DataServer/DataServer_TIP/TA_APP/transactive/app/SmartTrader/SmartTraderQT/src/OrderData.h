#ifndef __CLASS_ORDER_DATA_HH__
#define __CLASS_ORDER_DATA_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

class CItemUserInstrument;

class COrderData 
{ 
public:
	enum ESide 
	{
		BUY = 49,
		SELL
	};

	enum EOrderInfoMask
	{
		HEDGING = 32,
		OPEN_POSITION = 64,
		CLOSE_POSITION = 128,
		CLOSE_TODAY_POSITION = 256,
		CLOSE_YESTERDAY_POSITION = 512,
		OPEN_TODAY_POSITION = 1024,
        ENTRY = 32768,
        EXIT = 65536,
        ALGO = 131072,
	};

	enum EOrderStatus
	{
		NEW = 48,
		PARTIALLY_FILLED,
		FILLED,
		DONE_FOR_DAY,
		CANCELED,
		REPLACED,
		PENDING_CANCEL,
		STOPPED,
		REJECTED,
		SUSPENDED,
		PENDING_NEW = 65,
		CALCULATED = 66,
		PENDING_REPLACE = 69,
	};

	enum EOrderType
	{
		MARKET = 64,
		MARKET_FAK = 128,
		MARKET_FOK = 256,
		LIMIT = 1,
		LIMIT_FAK = 2,
		LIMIT_FOK = 4,
		STOP = 8192,
		UNKNOWN = 0,
	};

	enum ERejectReason
	{
		OK = 0,
		/*
		 * System Errors
		 */

		SYSTEM_ERROR = 48,
		FUNCTION_NOT_IMPLEMENTED,
		ROUTING_FAILURE,
		INVALID_MSG_SIZE,
		EXCHANGE_NOT_AVAILABLE,

		/*
		 * 
		 */
		INVALID_EXCHANGE_ID,
		INVALID_SECURITY_ID,
		INVALID_ACCOUNT_ID,
		
		ORDER_NOT_FOUND,
		ACCOUNT_BLOCKED,

		LIMIT_BREACHED,
		LIMIT_NOT_ASSIGNED,
		RATING_NOT_ASSIGNED,
		CASH_LIMIT_BREACHED,
		CLIP_LIMIT_BREACHED,

		LIMIT_PRICE_TOO_HIGH,
		LIMIT_PRICE_TOO_LOW,
		STOP_PRICE_TOO_HIGH,
		STOP_PRICE_TOO_LOW,

		INVALID_ORDER_STATE,
		INVALID_LIMIT_PRICE,
		INVALID_ORDER_SIZE,
		INVALID_ORDER_TYPE,
		INVALID_CL_ORD_ID,
		INVALID_ORDER_ID,

		INCORRECT_ORDER_INFO,

		ORDER_IS_FILLED,
		ORDER_IS_CANCELED,
		ORDER_IS_REJECTED,
		ORDER_IN_PENDING_NEW,
		ORDER_IN_PENDING_CANCEL,
		ORDER_IN_PENDING_REPLACE,

		MARKET_CLOSED,
		INSTRUMENT_SUSPENDED,
	};
public:
	enum EOrderConfirm
	{
		OrderConfirm_OK,
		OrderConfirm_Cancel,
	};
public: 
	COrderData();
	virtual ~COrderData(); 
public: 
	COrderData& operator=(const COrderData& cParam);
public:
	void setDataByItem(CItemUserInstrument* pData);
	QString getESide(COrderData::ESide  nSide);
	EOrderType getEOrderType(const QString& strEOrderType);
	QString getEOrderType(COrderData::EOrderType nOrderType);
	
private:
	void _ClearData();
public:
	unsigned int m_nInstrumentID ;
	QString m_strInstrumentCode;
	float m_fLastPrice;
	int m_nQuantity;
public:
	ESide m_nSide;
	EOrderType m_nOrderType;
public:
	EOrderConfirm m_nOrderConfirm;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_USER_ORDER_INFO_HH__



