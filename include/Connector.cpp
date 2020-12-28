#include "Connector.h"
#include<iostream>
namespace Young
{
	Connector::Connector(SocketFd fd, std::shared_ptr<Reactor>& reactor) :m_Fd(fd), m_Reactor(reactor)
	{
		m_Status = NCS_NORMAL;
	}
	void Connector::HandleRead()
	{
		recv(m_Fd, m_Buffer, 1000,0);
		std::cout << m_Buffer << std::endl;
	}
	void Connector::HandleWrite()
	{
	}
	void Connector::HandleError()
	{
	}
	SocketFd Connector::GetFd()
	{
		return m_Fd;
	}
}

