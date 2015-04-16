#ifndef IDATAGRAM_SOCKET_H
#define IDATAGRAM_SOCKET_H

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#else
#include <winsock2.h>
#endif // !WIN32

#include "core/utilities/src/CppException.h"
#include "core/CppSocket/src/Datagram.h"
#include "core/CppSocket/src/InetAddress.h"
#include "core/CppSocket/src/SocketSet.h"

namespace TA_Base_Core
{
	class IDatagramSocket
	{
	public:
		virtual ~IDatagramSocket() 
		{
			return;
		};

		// send and receive return true on success.
		virtual bool send(InetAddress &addr, Datagram &datagram) = 0;

		virtual bool receive(InetAddress &outAddr, Datagram &outDG) = 0;
		
		// create and destroy socket resources.
		virtual bool open() = 0;
		virtual bool close() = 0;

		// if failed to open then this will be false.  However, a good
		// socket could go bad so this is for testing.
		virtual bool isOpen() = 0;

	protected:
		// generally, users will not care to directly access the socket
		// handle however some friends might...
		#ifdef WIN32
		virtual SOCKET getSocketId() = 0;
		#else
		virtual int getSocketId() = 0;
		#endif

		// declare all friends here...
		friend class SocketSet<IDatagramSocket>;
	};
}

#endif
