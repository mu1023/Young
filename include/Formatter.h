#ifndef _YOUNG_FORMATTER_H_
#define _YOUNG_FORMATTER_H_
#include<AppenderBase.h>
namespace Young
{
	class FormatterBase
	{
	public:
		virtual void format(const LogMsg& msg,logBuf& dest) = 0;
	};

	//同一秒内缓存时间,线程不安全的
	class CacheTimestampFormatter :public FormatterBase
	{
	public:
		void format(const LogMsg& msg, logBuf& dest)override;
	private:
		UInt64						m_CacheSec;
		timeBuffer					m_CachedDatetime;
	};

	//不缓存
	class NoCacheTimestampFormatter :public FormatterBase
	{
	public:
		void format(const LogMsg& msg, logBuf& dest)override;
	private:
		
	};

	class DataPointFormatter :public FormatterBase
	{
	public:
		void format(const LogMsg& msg, logBuf& dest)override;
	private:

	};
}
#endif // _YOUNG_FORMATTERBASE_H_
