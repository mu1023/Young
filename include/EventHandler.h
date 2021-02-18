#ifndef _YOUNH_EventHandler_H_
#define _YOUNH_EventHandler_H_
#include<NetWorkAPI.h>
#include<Reactor.h>
#include<memory>
namespace Young
{
	class EventHandler
	{
	public:
		EventHandler(std::shared_ptr<Reactor> ptr):m_Reactor(ptr){ }

		virtual void HandleRead() = 0;

		virtual void HandleWrite() = 0;

		virtual void HandleError() = 0;

		virtual SocketFd GetFd() = 0;

		std::shared_ptr<Reactor> GetReactor(){ return m_Reactor; }
	
	protected:
		std::shared_ptr<Reactor>	m_Reactor;
	private:
	};
}
#endif // !
