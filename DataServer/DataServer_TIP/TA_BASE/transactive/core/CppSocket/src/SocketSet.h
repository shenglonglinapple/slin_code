#ifndef SOCKET_SET_H
#define SOCKET_SET_H

#include <vector>

namespace TA_Base_Core
{
	template <class SocketType>
	class SocketSet
	{
	public:
		SocketSet();
		~SocketSet();
		
		void addSocket(const SocketType *socket);
		void removeSocket(const SocketType *socket);
		unsigned int getSize();

		// canRead and canWrite are only valid after a waitForIO call and they
		// are true if the socket can do either without blocking.
		SocketType* getSocket(unsigned int index, bool &canRead, bool &canWrite);

		// wait for io on only one socket.  One of read or write must be
		// true otherwise function will return immediately with false.
		static bool waitForOneIO(SocketType *socket, bool read, bool write,
								 bool &canRead, bool &canWrite,
								 unsigned int timeMillis);

		// wait for io on all in set.  One of read or write must be
		// true otherwise function will return immediately with false.
		int waitForIO(bool read, bool write, unsigned int timeMillis);

	private:
		struct SocketRecord
		{
			SocketType* socket;
			bool canRead;
			bool canWrite;
		};

		std::vector<SocketRecord> m_socketRecords;
	};
}

// the implementation...
#include "SocketSetP.h"

#endif
