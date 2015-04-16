#ifndef INET_ADDRESS_H
#define INET_ADDRESS_H

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#else

#define WIN32_LEAN_AND_MEAN 

#include <winsock2.h>
#endif // !WIN32

#include <string>
#include "core/utilities/src/CppException.h"

namespace TA_Base_Core
{
	class InetAddress
	{
	public:
		InetAddress();
		InetAddress(const char* host);
		InetAddress(const std::string &host);
		InetAddress(const in_addr& address);
		InetAddress(const InetAddress &copy);

		bool isValid(); // is the host resolvable?
		const std::string& getHostName();
		const in_addr& getIPAddress();
		void setIPAddress(const in_addr& address);
	
	private:
		in_addr m_address;
		bool m_isResolved, m_doResolve;
		std::string m_hostname;

//			#ifdef WIN32
//    		WSAData winsockData;
//			#endif // WIN32
	};
}
#endif
