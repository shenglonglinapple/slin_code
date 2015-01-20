#ifndef __CLASS_TCP_COM_PROTOCOL_H__
#define __CLASS_TCP_COM_PROTOCOL_H__


#include <QtCore/QString>


class CTcpComProtocol
{
public:
	//4 Byte
	enum EMsgType 
	{
		MsgType_Req = 0x00,
		MsgType_Ack = 0x01,
		MsgType_Notify = 0x02,
		MsgType_Unknown = 0xFF,
	};

	//4 Bytes
	enum EDataType
	{
		DataType_Login  = 0x00000000,
		DataType_LogOut  = 0x00000001,
		DataType_DownLoadStock  = 0x00000002,
		DataType_SynYahoo  = 0x00000003,
		DataType_StockMinTimeMaxTime  = 0x00000004,
		DataType_HistoryData  = 0x00000005,
		DataType_CreateUser  = 0x00000006,
		DataType_Trade  = 0x00000007,
		DataType_Unknown  = 0x0FFFFFFF,
	};

	enum ETradeType
	{
		ETradeType_Buy  = 0x00,
		ETradeType_Sell  = 0x01,

		ETradeType_Unknown  = 0x0FFFFFFF,
	};

	//4 Bytes
	enum EDataTypeLoginResult
	{
		DataType_LoginResult_OK  = 0x00000000,
		DataType_LoginResult_ERROR  = 0x00000001,
		DataType_LoginResult_Unknown  = 0x0FFFFFFF,
	};

	//4 Bytes
	enum EDataTypeLogoutResult
	{
		DataType_LogoutResult_OK  = 0x00000000,
		DataType_LogoutResult_ERROR  = 0x00000001,
		DataType_LogoutResult_Unknown  = 0x0FFFFFFF,
	};
	//4 Bytes
	enum EDataTypeSynYahooResult
	{
		DataType_SynYahooResult_SynYahooStart = 0x00000000,
		DataType_SynYahooResult_SendReqToYahoo  = 0x00000001,
		DataType_SynYahooResult_WaitAckFromYahoo  = 0x00000002,
		DataType_SynYahooResult_RecvAckFromYahoo  = 0x00000003,
		DataType_SynYahooResult_ProcessAckFromYahoo  = 0x00000004,
		DataType_SynYahooResult_SynYahooFinished  = 0x00000005,
		DataType_SynYahooResult_ERROR  = 0x00000006,
		DataType_SynYahooResult_Unknown  = 0x0FFFFFFF,
	};
public:
	CTcpComProtocol();
	virtual ~CTcpComProtocol();
public:
	static QString getUUID();
public:
	static QString getStringValue(EMsgType nValue);
	static QString getStringValue( EDataType nValue );
	static QString getStringValue( EDataTypeLoginResult nValue );
	static QString getStringValue( EDataTypeLogoutResult nValue );
	static QString getStringValue( EDataTypeSynYahooResult nValue );
	static QString getStringValue( ETradeType nValue );

	
};





#endif //__CLASS_TCP_COM_PROTOCOL_H__



