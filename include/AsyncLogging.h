#ifndef _YOUNG_ASYNCLOGGING_H_
#define _YOUNG_ASYNCLOGGING_H_
#include<YoungDefine.h>
#include<Logging.h>
//#include<CircleQueue.h>
#include<mutex>
namespace Young
{
	class AsyncLogger 
	{
	public:
		template<typename ...Args>
		void Log(LogLevel lvl, SourceLoc loc, const char* formatStr, Args... args)
		{
			/*if (lvl < m_LogLevel)
			{
				return;
			}*/
			logBuf buf;
			try
			{
				fmt::format_to(buf, formatStr, args...);

			}
			catch (...)
			{
				return;
			}
			LogMsg* lg = new LogMsg(loc, string_view_t(buf.data(), buf.size()));
			{
				std::lock_guard<::YoungMutex> g(m_Mutex);
				//m_CircleQueue.push(lg);
				//auto pt = m_CircleQueue.pop();
				//delete pt;
			}
			
		}
	private:
		std::mutex					m_Mutex;
	//	CircleQueue<LogMsg,1024>	m_CircleQueue;
	};

}
#endif // _YOUNG_ASYNCLOGGING_H_
