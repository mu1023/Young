#pragma once
#include "EventDemultiplexer.h"
#include<vector>
#include<unordered_map>
namespace Young
{
	class PollDemultiplexer :public EventDemultiplexer
	{
	public:
		//读事件
		virtual Events ReadEvent()override;
		
		//写事件
		virtual Events WriteEvent()override;
		
		//错误事件
		virtual Events ErrorEvent()override;


		virtual void Run(UInt32 timeout)override;

		//修改连接的监听事件
		virtual void UpdateHandler(EventHandlerPtr EventHandler, Events events)override;

	private:
		typedef std::vector<struct pollfd> PollFdList;
		PollFdList m_Pollfds;
		std::unordered_map<SocketFd, UInt32> m_IndexBySocketFd;
	};

}

