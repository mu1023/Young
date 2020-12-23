#ifndef _YOUNG_FIXEDBUFFER_H_
#define _YOUNG_FIXEDBUFFER_H_

#include<YoungDefine.h>
#include<cstring>

namespace Young
{
	template<UInt64 N>
	class FixedBuffer
	{
	public:
		FixedBuffer() :m_CurPtr(m_Data) {};
		void			Add(const Int8 * msg, UInt64 len);
		void			bzero() { memset(m_Data, 0, sizeof(m_Data)); }
		const UInt64		Avail() { return End() - m_CurPtr; }
		const Int8*		End() { return m_Data + sizeof(m_Data); }
		const Int8*		Buffer() { return m_Data; };
		void			Clear() { m_CurPtr = m_Data; }
		UInt64			Length() { return m_CurPtr - m_Data; }
	private:
		Int8				m_Data[N];
		Int8*				m_CurPtr;
	};


	template<UInt64 N>
	inline void FixedBuffer<N>::Add(const Int8 * msg, UInt64 len)
	{
		if (Avail() > len)
		{
			memcpy(m_CurPtr, msg, len);
			m_CurPtr += len;
		}
	}
}
#endif // 