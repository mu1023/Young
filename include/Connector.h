#ifndef _YOUNG_CONNECTOR_H_
#define _YOUNG_CONNECTOR_H_
#include<EventHandler.h>
#include<memory>
#include<Reactor.h>
namespace Young
{

	enum NetConnectionType
	{
		NCT_ACTIVE,	//主动连接
		NCT_PASSIVE,	//被动连接
	};

	/**
	 *@brief 连接状态
	 */
	enum NetConnectionStatus
	{
		NCS_CLOSED,			//初始状态，还没连接
		NCS_VERIFY,			//验证阶段
		NCS_NORMAL			//正常通信状态
	};
	class Connector :public EventHandler, public std::enable_shared_from_this<Connector>
	{
	public:
		Connector(SocketFd fd, std::shared_ptr<Reactor>& reactor);
		void HandleRead()override;
		void HandleWrite()override;
		void HandleError()override;
		SocketFd GetFd()override;
	private:
		SocketFd m_Fd;
		std::shared_ptr<Reactor> m_Reactor;
		char m_Buffer[10086];
		NetConnectionStatus m_Status;
	};
}
#endif // !_YOUNG_CONNECTOR_H_
