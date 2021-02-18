#ifndef _YOUNG_REACTOR_H_
#define _YOUNG_REACTOR_H_
#include<EventDemultiplexer.h>
#include<memory>
#include<mutex>
#include<queue>
#include<functional>
namespace Young
{

	class Reactor : public std::enable_shared_from_this<Reactor>
	{
	public:
		Reactor(std::shared_ptr<EventDemultiplexer> ptr):m_EventDemultiplexer(ptr)
		{
		}

		virtual void Run()
		{
			while (true)
			{
				m_EventDemultiplexer->Run(1000);
			}
		};
		void RegisterHandler(EventHandlerPtr EventHandler, Events events)
		{
			m_EventDemultiplexer->RegisterHandler(EventHandler, events);
		}
		void RemoveHandler(EventHandlerPtr EventHandler)
		{
			m_EventDemultiplexer->RemoveHandler(EventHandler);
		}
		void UpdateHandler(EventHandlerPtr EventHandler, Events events)
		{
			m_EventDemultiplexer->UpdateHandler(EventHandler, events);
		}
		Events ReadEvent(){return m_EventDemultiplexer->ReadEvent(); }
		Events WriteEvent(){return m_EventDemultiplexer->WriteEvent(); }
		Events ErrorEvent(){return m_EventDemultiplexer->ErrorEvent(); }


		virtual void OnConnected(SocketFd sockfd);

		void PushEvent(std::function<void()> func);
	private:
		std::shared_ptr<EventDemultiplexer> m_EventDemultiplexer;

		std::queue<std::function<void ()>>	m_Queue;
		std::mutex							m_QueueMutex;
	};
}

#endif // _YOUNG_REACTOR_H_
