#ifndef  _YOUNG_ACCEPTOR_H_
#define  _YOUNG_ACCEPTOR_H_
#include<EventHandler.h>
#include<memory>
#include<Reactor.h>
#include<Connector.h>
namespace Young
{

	class Acceptor :public EventHandler, public std::enable_shared_from_this<Acceptor>
	{
	public:
		Acceptor(SocketFd fd, std::shared_ptr<Reactor>& reactor);
		void HandleRead()override;
		void HandleWrite()override;
		void HandleError()override;
		SocketFd GetFd()override;
	private:
		SocketFd m_Fd;
		std::shared_ptr<Reactor> m_Reactor;
	};
}
#endif // ! _YOUNG_ACCEPTOR_H_
