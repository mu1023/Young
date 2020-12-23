#ifndef _YOUNG_SHAREMEMORY_H_
#define _YOUNG_SHAREMEMORY_H_
#include<YoungDefine.h>
#include<cstring>
#include<string>
#ifdef WINDOWS_YOUNG
#include<windows.h>
#else
#include<sys/shm.h>
#endif
typedef  unsigned int UInt32;
typedef  unsigned long long  UInt64;
class ShareMemory
{
public:
#ifdef WINDOWS_YOUNG
	ShareMemory() :m_Mem(NULL), m_Size(0), m_Handle(0), m_IsCreate(false)
	{
	}
	bool Init(std::string Key, UInt32 ssize);
#else
	ShareMemory() : m_Mem(NULL), m_Size(0), m_ShmId(0), m_IsCreate(false)
	{
	}
	bool Init(key_t Key, UInt32 ssize);
#endif
	void* GetMem()
	{
		return m_Mem;
	}
	bool IsCreate()
	{
		return m_IsCreate;
	}
	bool Remove();
private:
	void*						m_Mem;
	UInt32						m_Size;
#ifdef WINDOWS_YOUNG
	HANDLE						m_Handle;
#else
	int						m_ShmId;
#endif
	bool						m_IsCreate;
};


#endif 
