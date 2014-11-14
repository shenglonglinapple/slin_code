#include "core/CppSendEmailLib/src/WinSockHelper.h"


//
#include <exception>
#include <string>
#include <winsock2.h>
//#pragma comment(lib, "Ws2_32.lib")//winsock2

NS_BEGIN(TA_Base_Core)

TA_Base_Core::WinSockHelper::WinSockHelper()
{
	WSADATA wsaData;
	int result = WSAStartup(0x0002, &wsaData);

	if ( result != 0 )
	{
		throw std::exception("WSAStartup error");
	}

	if ( wsaData.wVersion != 0x0002)
	{
		WSACleanup();
		throw std::exception("Winsock version not support");
	}
}

TA_Base_Core::WinSockHelper::~WinSockHelper()
{
	int result = 0;
	result = WSACleanup();
}

NS_END(TA_Base_Core)

