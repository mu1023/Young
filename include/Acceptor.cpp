#include "Acceptor.h"
namespace Young
{

	Acceptor::Acceptor(SocketFd fd, std::shared_ptr<Reactor>& reactor) :m_Fd(fd), m_Reactor(reactor)
	{
	}

	void Acceptor::HandleRead()
	{
		sockaddr_in saddr;
		socklen_t len = sizeof saddr;
		SocketFd connfd = accept(m_Fd, (sockaddr*)&saddr, &len);
		printf("%d\n", WSAGetLastError());
		std::shared_ptr<Connector> conn = std::make_shared<Connector>(connfd, m_Reactor);
		m_Reactor->RegisterHandler(conn,m_Reactor->ReadEvent());
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