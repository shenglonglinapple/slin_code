#ifndef RAW_DATAGRAM_SOCKET_H
#define RAW_DATAGRAM_SOCKET_H

#include "core/CppSocket/src/IDatagramSocket.h"

namespace TA_Base_Core
{
	class RawDatagramSocket : public IDatagramSocket
	{
	public:
		RawDatagramSocket(const std::string& protocolName, bool stripHeader = false);
		~RawDatagramSocket();

		bool send(InetAddress &addr, Datagram &datagram);

		bool receive(InetAddress &outAddr, Datagram &outDG);
		
		// create and destroy socket resources.
		bool open();
		bool close();
		bool isOpen();

	protected:
		#ifdef WIN32
		SOCKET getSocketId() {return m_socket;};
		#else
		int getSocketId() {return m_socket;};
		#endif

	private:
		bool m_isOpen;
		std::string m_protocolName;

		bool m_stripHeader;

		#ifdef WIN32
		SOCKET m_socket;
		#else
		int m_socket;
		#endif
	};
}

#endif
