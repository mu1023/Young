#include "Connector.h"
#include<iostream>
#include<mutex>
#include<Logging.h>
#include<Protocol.h>
namespace Young
{
	void Connector::Close()
	{
		LOGGER_DEBUG("Close Socket Fd {0}", m_Fd);
		m_Status = NetConnectionStatus::NCS_CLOSED;
		//m_Reactor->RemoveHandler(shared_from_this());
	}
	Connector::Connector(SocketFd fd, std::shared_ptr<Reactor> reactor) :EventHandler(reactor),m_Fd(fd), m_ReadBuffer(READ_BUFFER_SIZE),m_WriteBuffer(WRITE_BUFFER_SIZE)
	{
		m_Status = NCS_NORMAL;
	}
	Connector::~Connector()
	{
		if (m_Fd)
		{
			closesocket(m_Fd);
		}
	}
	void Connector::HandleRead()
	{
		if (m_Status != NetConnectionStatus::NCS_NORMAL)
		{
			return;
		}
		m_ReadBuffer.Align();
		if (m_ReadBuffer.ReadableBytes() < Protocol::HEAD_SIZE)
		{
			Int32 len = recv(m_Fd, m_ReadBuffer.BeginWrite(), Protocol::HEAD_SIZE - m_ReadBuffer.ReadableBytes(), 0);
			if (len < 0)
			{
				Close();
				return ;
			}
		}
		if (m_ReadBuffer.ReadableBytes() >= Protocol::HEAD_SIZE)
		{

		}
	}
	void Connector::HandleWrite()
	{
		if (m_Status != NetConnectionStatus::NCS_NORMAL)
		{
			return;
		}
		std::lock_guard<std::mutex> gd(m_Mutex);
		Int32 ret = ::send(m_Fd, m_WriteBuffer.BeginRead(), m_WriteBuffer.ReadableBytes(), 0);

		if (ret > 0)
		{
			m_WriteBuffer.Retrieve(ret);
			return;
		}
		else if (ret == 0)
		{
			Close();
			return;
		}
		else
		{
			auto err = sock_error();
			if (err == YOUNG_EAGAIN || err == YOUNG_EWOULDBLOCK)
			{
				return;
			}
			else
			{
				Close();
			}
		}
	}
	void Connector::HandleError()
	{
	}
	SocketFd Connector::GetFd()
	{
		return m_Fd;
	}
	UInt32 Connector::Write(const char * msg, UInt32 len)
	{
		std::lock_guard<std::mutex> gd(m_Mutex);
		if (m_Status != NetConnectionStatus::NCS_NORMAL)
		{
			return 0;
		}
		m_WriteBuffer.Align();
		m_WriteBuffer.Append(msg, len);
		m_Reactor->PushEvent(std::bind(&Reactor::UpdateHandler, m_Reactor, shared_from_this(), m_Reactor->ReadEvent() | m_Reactor->WriteEvent()));
		//m_Reactor->UpdateHandler(shared_from_this(), m_Reactor->ReadEvent()|m_Reactor->WriteEvent());
		return len;
	}
}

