#include "Reactor.h"
#include<Connector.h>
void Young::Reactor::OnConnected(SocketFd sockfd)
{
	std::shared_ptr<Connector> conn = std::make_shared<Connector>(sockfd,shared_from_this());
	m_EventDemultiplexer->RegisterHandler(conn, m_EventDemultiplexer->ReadEvent());
}

void Young::Reactor::PushEvent(std::function<void()> func)
{
	std::lock_guard<std::mutex> gd(m_QueueMutex);
	m_Queue.push(func);
}
