#ifndef _YOUNG_CONNECTOR_H_
#define _YOUNG_CONNECTOR_H_
#include<EventHandler.h>
#include<memory>
#include<Reactor.h>
namespace Young
{

	enum NetConnectionType
	{
		NCT_ACTIVE,	//��������
		NCT_PASSIVE,	//��������
	};

	/**
	 *@brief ����״̬
	 */
	enum NetConnectionStatus
	{
		NCS_CLOSED,			//��ʼ״̬����û����
		NCS_VERIFY,			//��֤�׶�
		NCS_NORMAL			//����ͨ��״̬
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
