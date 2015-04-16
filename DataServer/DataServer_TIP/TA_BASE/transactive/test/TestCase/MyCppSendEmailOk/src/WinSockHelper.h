#ifndef _WINSOCK_HELPER_H_
#define _WINSOCK_HELPER_H_
//
#include <exception>
#include <string>
#include <winsock2.h>
//
namespace MUtils {

class WinSockException : public std::exception
{
public:

    WinSockException(const std::string message = "")
     : _message(message)
    {
    }

    const char *what() const throw ()
    {
        return _message.c_str();
    }

private:

    std::string _message;
};

class WinSockHelper
{
public:

    WinSockHelper()
    {
        WSADATA wsaData;
        int result = WSAStartup(0x0002, &wsaData);

        if ( result != 0 )
        {
            throw WinSockException("WSAStartup error");
        }

        if ( wsaData.wVersion != 0x0002)
        {
            WSACleanup( );
            throw WinSockException("Winsock version not support");
        }
    }

    ~WinSockHelper() throw()
    {
        WSACleanup();
    }
};

} // namespace MUtils

#endif // _WINSOCK_HELPER_H_