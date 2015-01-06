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
		MsgType_Unknown = 0xFF,
	};

	//4 Bytes
	enum EDataType
	{
		DataType_Login  = 0x00000000,
		DataType_LogOut  = 0x00000001,
		DataType_Unknown  = 0x0FFFFFFF,
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

};





#endif //__CLASS_TCP_COM_PROTOCOL_H__



