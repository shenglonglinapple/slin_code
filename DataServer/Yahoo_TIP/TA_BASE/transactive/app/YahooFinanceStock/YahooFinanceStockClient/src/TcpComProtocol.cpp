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