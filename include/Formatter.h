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

	//ͬһ���ڻ���ʱ��,�̲߳���ȫ��
	class CacheTimestampFormatter :public FormatterBase
	{
	public:
		void format(const LogMsg& msg, logBuf& dest)override;
	private:
		UInt64						m_CacheSec;
		timeBuffer					m_CachedDatetime;
	};

	//������
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
