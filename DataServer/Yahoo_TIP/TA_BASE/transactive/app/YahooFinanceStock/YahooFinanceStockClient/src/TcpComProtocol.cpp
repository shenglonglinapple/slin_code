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
	case MsgType_Notify:
		strValue = "MsgType_Notify";
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
	case DataType_DownLoadStock:
		strValue = "DataType_DownLoadStock";
		break;
	case DataType_SynYahoo:
		strValue = "DataType_SynYahoo";
		break;
	case DataType_StockMinTimeMaxTime:
		strValue = "DataType_StockMinTimeMaxTime";
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

QString CTcpComProtocol::getStringValue( EDataTypeSynYahooResult nValue )
{
	QString strValue;
	switch (nValue)
	{
	case DataType_SynYahooResult_SynYahooStart:
		strValue = "DataType_SynYahooResult_SynYahooStart";
		break;
	case DataType_SynYahooResult_SendReqToYahoo:
		strValue = "DataType_SynYahooResult_SendReqToYahoo";
		break;
	case DataType_SynYahooResult_WaitAckFromYahoo:
		strValue = "DataType_SynYahooResult_WaitAckFromYahoo";
		break;
	case DataType_SynYahooResult_RecvAckFromYahoo:
		strValue = "DataType_SynYahooResult_RecvAckFromYahoo";
		break;
	case DataType_SynYahooResult_ProcessAckFromYahoo:
		strValue = "DataType_SynYahooResult_ProcessAckFromYahoo";
		break;
	case DataType_SynYahooResult_SynYahooFinished:
		strValue = "DataType_SynYahooResult_SynYahooFinished";
		break;
	case DataType_SynYahooResult_ERROR:
		strValue = "DataType_SynYahooResult_ERROR";
		break;
	case DataType_SynYahooResult_Unknown:
		strValue = "DataType_SynYahooResult_Unknown";
		break;
	}
	return strValue;
}

