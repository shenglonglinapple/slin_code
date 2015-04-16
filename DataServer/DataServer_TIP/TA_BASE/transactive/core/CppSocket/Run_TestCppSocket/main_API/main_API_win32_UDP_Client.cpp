#include "stdafx.h"  
#include <stdio.h>  
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")   

int main(int argc, char* argv[])  
{  
	WORD socketVersion = MAKEWORD(2,2);  
	WSADATA wsaData;   
	if(WSAStartup(socketVersion, &wsaData) != 0)  
	{  
		return 0;  
	}  
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  

	sockaddr_in sin;  
	sin.sin_family = AF_INET;  
	sin.sin_port = htons(8888);  
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  
	int len = sizeof(sin);  

	char * sendData = "来自客户端的数据包.\n";  
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);  

	char recvData[255];       
	int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);  
	if(ret > 0)  
	{  
		recvData[ret] = 0x00;  
		printf(recvData);  
	}  

	closesocket(sclient);  
	WSACleanup();  
	return 0;  
}  


/*
三、Linux 与 Windows Socket 的区别
1)头文件 
windows下winsock.h或winsock2.h
linux下netinet/in.h（大部分都在这儿），unistd.h（close函数在这儿），sys/socket.h（在in.h里已经包含了，可以省了）

2)初始化
windows下需要用WSAStartup启动Ws2_32.lib，并且要用#pragma comment(lib,"Ws2_32")来告知编译器链接该lib。
linux下不需要

3)关闭socket
windows下closesocket(...)
linux下close(...)

4)类型
windows下SOCKET
linux下int（我喜欢用long，这样保证是4byte，因为-1我总喜欢写成0xFFFF）

5)获取错误码 
windows下getlasterror()/WSAGetLastError()
linux下，未能成功执行的socket操作会返回-1；如果包含了errno.h，就会设置errno变量

6)设置非阻塞
windows下ioctlsocket()
linux下fcntl()，需要头文件fcntl.h

7)send函数最后一个参数
windows下一般设置为0
linux下最好设置为MSG_NOSIGNAL，如果不设置，在发送出错后有可能会导致程序退出

8)毫秒级时间获取
windows下GetTickCount()
linux下gettimeofday()

9)多线程 
windows下包含process.h，使用_beginthread和_endthread
linux下包含pthread.h，使用pthread_create和pthread_exit

10)用IP定义一个地址（sockaddr_in的结构的区别）
windows下addr_var.sin_addr.S_un.S_addr
linux下addr_var.sin_addr.s_addr
而且Winsock里最后那个32bit的S_addr也有几个以联合（Union）的形式与它共享内存空间的成员变量（便于以其他方式赋值），而Linux的Socket没有这个联合，就是一个32bit的s_addr。遇到那种得到了是4个char的IP的形式（比如127一个，0一个，0一个和1一个共四个char），WinSock可以直接用4个S_b来赋值到S_addr里，而在Linux下，可以用边向左移位（一下8bit，共四下）边相加的方法赋值。

11)异常处理
linux下当连接断开，还发数据的时候，不仅send()的返回值会有反映，而且还会像系统发送一个异常消息，如果不作处理，系统会出BrokePipe，程序会退出。为此，send()函数的最后一个参数可以设MSG_NOSIGNAL，禁止send()函数向系统发送异常消息。

*/