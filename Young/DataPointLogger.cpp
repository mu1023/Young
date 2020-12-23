#include<DataPointLogger.h>
namespace Young
{

	void DataPointLog::RegisterDataPoint(UInt32 type, AppenderPtr  ptr)
	{
		if (ptr == nullptr)
		{
			return;
		}
		m_Map[type] = ptr;
	}
}