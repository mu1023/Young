#ifndef _YOUNG_UDPAPPENDER_H_
#define _YOUNG_UDPAPPENDER_H_
#include<AppenderBase.h>
#include<YoungDefine.h>
#include<Formatter.h>
#include<SocketAPI.h>
#include<fmt/format.h>
#include<iostream>
#include<tuple>
#include<functional>
#include<vector>
#include<string>
#include<mutex>
#include<assert.h> 

namespace Young
{
	template<typename Mutex,typename Formatter = NoCacheTimestampFormatter >
	class UdpAppender :public Appender<Mutex>
	{
	public:
		UdpAppender(const char* ip, UInt32 port);
		~UdpAppender();
	protected:
		void Put(const LogMsg& msg)override;
	private:

		const char*					m_Ip;
		UInt32						m_Port;
		socket_t					m_Sock;

		Formatter					m_Formatter;
	};

	



	template<typename Mutex, typename Formatter>
	inline UdpAppender<Mutex, Formatter>::UdpAppender(const char * ip, UInt32 port) :m_Ip(ip), m_Port(port)
	{
		if (ip == NULL )
		{
			return;
		}
		m_Sock = socket(AF_INET, SOCK_DGRAM , 0);

		if (m_Sock == YOUNG_INVALID_SOCKET) 
		{
			std::cout << "create socket err : errcode = " << WSAGetLastError() << std::endl;

			return;
		}

		sockaddr_in addr;

		memset(&addr, 0, sizeof addr);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (inet_pton(AF_INET, ip, &addr.sin_addr.s_addr) < 0) 
		{
			std::cout << "inet pton err : errcode = " << WSAGetLastError() << std::endl;
			return;
		}

		::connect(m_Sock, (struct sockaddr*)&addr, sizeof addr);

	}

	template<typename Mutex, typename Formatter>
	inline UdpAppender<Mutex, Formatter>::~UdpAppender()
	{
		::closesocket(m_Sock);
	}

	template<typename Mutex, typename Formatter>
	inline void UdpAppender<Mutex, Formatter>::Put(const LogMsg & msg)
	{
		logBuf dest;
		m_Formatter.format(msg, dest);

		::send(m_Sock, dest.data(), (Int32)dest.size(), 0);
	}



}
#endif