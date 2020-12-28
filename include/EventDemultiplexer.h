#ifndef  _H_YOUNG_EVENTDEMULTIPLEXER_H
#define  _H_YOUNG_EVENTDEMULTIPLEXER_H
#include<EventHandler.h>
#include<unordered_map>
#include<memory>
namespace Young
{
	typedef std::shared_ptr<EventHandler> EventHandlerPtr;

	class EventDemultiplexer
	{
	public:
		virtual void UpdateHandler(EventHandlerPtr EventHandler, Events events) = 0;

		void RegisterHandler(EventHandlerPtr EventHandler, Events events){ UpdateHandler(EventHandler, events); }

		virtual void RemoveHandler(EventHandlerPtr EventHandler){ UpdateHandler(EventHandler, NoneEvent);}
		virtual void Run(UInt32 timeout) = 0;
		virtual Events ReadEvent() = 0;
		virtual Events WriteEvent() = 0;
		virtual Events ErrorEvent() = 0;
	protected:
		std::unordered_map<SocketFd, EventHandlerPtr> m_Handlers;
	};
}
#endif // !
