#ifndef _YOUNG_CONNECTOR_H_
#define _YOUNG_CONNECTOR_H_
#include<EventHandler.h>
#include<memory>
#include<NetBuffer.h>
#include<FixedBuffer.h>
#include<mutex>
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
		const UInt32 WRITE_BUFFER_SIZE = 10000;
		const UInt32 READ_BUFFER_SIZE = 10000;

		void Close();

		Connector(SocketFd fd, std::shared_ptr<Reactor> reactor);
		~Connector();
		void HandleRead()override;

		void HandleWrite()override;

		void HandleError()override;

		SocketFd GetFd()override;

		UInt32 Write(const char* msg, UInt32 len);


	private:
		SocketFd m_Fd;


		NetBuffer					m_ReadBuffer;
		NetBuffer					m_WriteBuffer;
		std::mutex				    m_Mutex;
		NetConnectionStatus			m_Status;
	};
}
#endif // !_YOUNG_CONNECTOR_H_
