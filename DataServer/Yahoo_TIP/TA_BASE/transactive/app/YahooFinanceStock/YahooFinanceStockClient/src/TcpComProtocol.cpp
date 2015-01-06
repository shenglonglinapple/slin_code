#include "TcpComProtocol.h"
#include <QtCore/QDateTime>
#include <QtCore/QUuid>



CTcpComProtocol::CTcpComProtocol()
{

}

CTcpComProtocol::~CTcpComProtocol()
{

}
//static
QString CTcpComProtocol::getUUID()
{
	QUuid newUuid = QUuid::createUuid();
	//std::cout << qPrintable(newUuid.toString()) << std::endl;
	QString strUUID;
	strUUID = newUuid.toString();
	return strUUID;
}
//static
QString CTcpComProtocol::getStringValue( EMsgType nValue )
{
	QString strValue;
	switch (nValue)
	{
	case MsgType_Req:
		strValue = "MsgType_Req";
		break;
	case MsgType_Ack:
		strValue = "MsgType_Ack";
		break;
	case MsgType_Unknown:
		strValue = "MsgType_Unknown";
		break;
	}
	return strValue;
}

//static
QString CTcpComProtocol::getStringValue( EDataType nValue )
{
	QString strValue;
	switch (nValue)
	{
	case DataType_Login:
		strValue = "DataType_Login";
		break;
	case DataType_LogOut:
		strValue = "DataType_LogOut";
		break;
	case DataType_Unknown:
		strValue = "DataType_Unknown";
		break;
	}
	return strValue;
}

//static
QString CTcpComProtocol::getStringValue( EDataTypeLoginResult nValue )
{
	QString strValue;
	switch (nValue)
	{
	case DataType_LoginResult_OK:
		strValue = "DataType_LoginResult_OK";
		break;
	case DataType_LoginResult_ERROR:
		strValue = "DataType_LoginResult_ERROR";
		break;
	case DataType_LoginResult_Unknown:
		strValue = "DataType_LoginResult_Unknown";
		break;
	}
	return strValue;
}

//static
QString CTcpComProtocol::getStringValue( EDataTypeLogoutResult nValue )
{
	QString strValue;
	switch (nValue)
	{
	case DataType_LogoutResult_OK:
		strValue = "DataType_LogoutResult_OK";
		break;
	case DataType_LogoutResult_ERROR:
		strValue = "DataType_LogoutResult_ERROR";
		break;
	case DataType_LogoutResult_Unknown:
		strValue = "DataType_LogoutResult_Unknown";
		break;
	}
	return strValue;
}

