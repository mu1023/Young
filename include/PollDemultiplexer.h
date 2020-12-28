#pragma once
#include "EventDemultiplexer.h"
#include<vector>
#include<unordered_map>
namespace Young
{
	class PollDemultiplexer :public EventDemultiplexer
	{
	public:
		//���¼�
		virtual Events ReadEvent()override;
		
		//д�¼�
		virtual Events WriteEvent()override;
		
		//�����¼�
		virtual Events ErrorEvent()override;


		virtual void Run(UInt32 timeout)override;

		//�޸����ӵļ����¼�
		virtual void UpdateHandler(EventHandlerPtr EventHandler, Events events)override;

	private:
		typedef std::vector<struct pollfd> PollFdList;
		PollFdList m_Pollfds;
		std::unordered_map<SocketFd, UInt32> m_IndexBySocketFd;
	};

}

