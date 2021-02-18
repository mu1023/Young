#include "Acceptor.h"
#include<Logging.h>
namespace Young
{

	Acceptor::Acceptor(SocketFd fd, std::shared_ptr<Reactor>& reactor):EventHandler(reactor),m_Fd(fd)
	{
	}

	void Acceptor::HandleRead()
	{
		sockaddr_in saddr;
		socklen_t len = sizeof saddr;
		SocketFd connfd = accept(m_Fd, (sockaddr*)&saddr, &len);
		if (connfd == YOUNG_INVALID_SOCKET)
		{
			LOGGER_DEBUG("accept error : {0}", WSAGetLastError());
			return ;
		}

		m_Reactor->OnConnected(connfd);
	}

	void Acceptor::HandleWrite()
	{
	}

	void Acceptor::HandleError()
	{
		m_Reactor->RemoveHandler(shared_from_this());
	}

	SocketFd Acceptor::GetFd()
	{
		return m_Fd;
	}

}