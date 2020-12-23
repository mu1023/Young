#ifndef _YOUNG_DATAPOINTLOGGER_H_
#define _YOUNG_DATAPOINTLOGGER_H_
#include<YoungDefine.h>
#include<Singleton.h>
#include<YoungTime.h>
#include<AppenderBase.h>
#include<map>
#include<vector>
#include<fmt/format.h>
namespace Young
{
	enum class DataPointType
	{
		DATA_POINT_LOGIN = 1,
		DATA_POINT_DUNGEON = 2,
		DATA_POINT_MAX,
	};
	class DataPointLog:public Singleton<DataPointLog>
	{
		typedef std::shared_ptr<AppenderBase> AppenderPtr ;
	public:
		void RegisterDataPoint(UInt32  type, AppenderPtr ptr);

		template<typename... Args>
		 void Send(UInt32 type, const char* fmtstr, Args... args);
	private:
		//key ¬Òµ„¿‡–Õ,
		std::map<UInt32, AppenderPtr >		 m_Map;
	};


	template<typename ...Args>
	inline void DataPointLog::Send(UInt32 type, const char * fmtstr, Args ...args)
	{
		if (m_Map.count(type) == 0)return;
		try
		{
			logBuf buf;
			fmt::format_to(buf, fmtstr, args...);
			LogMsg msg(string_view_t(buf.data(), buf.size()));
			{
				m_Map[type]->Append(msg);
			}
		}
		catch (const std::exception&)
		{

		}
	}
}

#endif // !_YOUNG_DATAPOINTLOGGER_H_

