#include "PollDemultiplexer.h"
#include<iostream>
namespace Young
{
	Events PollDemultiplexer::ReadEvent()
	{
#ifdef WINDOWS_YOUNG
		return POLLIN;
#else 
		return POLLIN | POLLPRI;
#endif // WINDOWS_YOUNG

	}
	Events PollDemultiplexer::WriteEvent()
	{
		return POLLOUT;
	}
	Events PollDemultiplexer::ErrorEvent()
	{
		return POLLERR;
	}
	void PollDemultiplexer::Run(UInt32 timeout)
	{
		UInt32 nums = poll(&*m_Pollfds.begin(), m_Pollfds.size(), timeout);
		std::vector<pollfd> activityFds;
		//把活跃的fd取出来。防止执行handler事件时删除句柄，而此时又在遍历m_Pollfds
		for (UInt32 i = 0; i < m_Pollfds.size() && nums > 0; i++)
		{
			if (m_Pollfds[i].revents)
			{
				--nums;
				activityFds.push_back(m_Pollfds[i]);
			}
			
		}
		for (UInt32 i = 0; i < activityFds.size(); i++)
		{
			SocketFd sfd = activityFds[i].fd;
			if (activityFds[i].revents & ReadEvent())
			{
				m_Handlers[sfd]->HandleRead();
			}
			if (activityFds[i].revents & WriteEvent())
			{
				m_Handlers[sfd]->HandleWrite();
			}
			if (activityFds[i].revents & ErrorEvent())
			{
				m_Handlers[sfd]->HandleError();
			}
		}
	}
	void PollDemultiplexer::UpdateHandler(EventHandlerPtr EventHandler, Events events)
	{
		if (EventHandler == NULL)
		{
			return;
		}
		SocketFd sfd = EventHandler->GetFd();
		if (m_IndexBySocketFd.count(sfd) == 0)
		{
			//没事件
			if (events == NoneEvent)
			{
				return;
			}
			pollfd pfd;
			pfd.events = events;
			pfd.fd = EventHandler->GetFd();

			m_Pollfds.push_back(pfd);

			m_IndexBySocketFd[sfd] = m_Pollfds.size() - 1;

			m_Handlers[sfd] = EventHandler;
		}
		else
		{
			UInt32 idx = m_IndexBySocketFd[EventHandler->GetFd()];

			if (events == NoneEvent)
			{

				std::iter_swap(m_Pollfds.begin() + idx, m_Pollfds.end() - 1);
				m_Pollfds.pop_back();
				m_IndexBySocketFd.erase(sfd);
				m_Handlers.erase(sfd);
			}
			else
			{
				m_Pollfds[idx].events = events;
			}
		}
	}
}