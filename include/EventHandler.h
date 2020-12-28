#ifndef _YOUNH_EventHandler_H_
#define _YOUNH_EventHandler_H_
#include<NetWorkAPI.h>
namespace Young
{
	class EventHandler
	{
	public:
		virtual void HandleRead() = 0;

		virtual void HandleWrite() = 0;

		virtual void HandleError() = 0;

		virtual SocketFd GetFd() = 0;
	private:
	};
}
#endif // !
