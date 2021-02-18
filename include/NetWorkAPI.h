#ifndef _YOUNG_NETWORKAPI_H_
#define _YOUNG_NETWORKAPI_H_

#include<YoungDefine.h>

#ifdef WINDOWS_YOUNG
#ifndef FD_SETSIZE
#define FD_SETSIZE 1024
#endif
#include <Winsock2.h>
#include <windows.h>
#include<WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib") 

#else
#ifndef socklen_t
#define socklen_t __socklen_t
#endif
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/tcp.h>
#endif
namespace Young {
#ifdef WINDOWS_YOUNG
	typedef SOCKET SocketFd;
	typedef int	   socklen_t;
#	define YOUNG_INVALID_SOCKET		INVALID_SOCKET
#	define YOUNG_SOCK_ERROR			SOCKET_ERROR

#	define YOUNG_ECONNABORTED		WSAECONNABORTED
#	define YOUNG_EWOULDBLOCK		WSAEWOULDBLOCK
#	define YOUNG_ECONNRESET			WSAECONNRESET
#	define YOUNG_EINTR				WSAEINTR
#	define YOUNG_ENOBUFS			WSAENOBUFS
#	define YOUNG_EAGAIN				WSAEWOULDBLOCK
#	define YOUNG_ETIMEDOUT			WSAETIMEDOUT

	typedef UInt32 Events;
	const UInt32 NoneEvent = 0;
#define poll(fdarray,fds,timeout) WSAPoll((fdarray),(fds),(timeout))


#define SOCKET_STARTUP WSADATA wsaData;\
	WSAStartup(MAKEWORD(2, 2), &wsaData);

#define SOCKET_CLEANUP WSACleanup();
#else

	typedef int SocketFd;
#	define YOUNG_INVALID_SOCKET		 -1
#	define YOUNG_SOCK_ERROR			 -1

#	define closesocket close

#	define YOUNG_ECONNABORTED		ECONNABORTED
#	define YOUNG_EWOULDBLOCK		EWOULDBLOCK
#	define YOUNG_ECONNRESET			ECONNRESET
#	define YOUNG_EINTR				EINTR
#	define YOUNG_ENOBUFS			ENOBUFS
#	define YOUNG_EAGAIN				EAGAIN
#	define YOUNG_ETIMEDOUT			ETIMEDOUT

#define SOCKET_STARTUP

#define SOCKET_CLEANUP
#endif

	inline int sock_error()
	{
#ifdef   WINDOWS_YOUNG
		return WSAGetLastError();
#else
		return errno;
#endif
	}

}

#endif // !_YOUNG_NETWORKAPI_H_
