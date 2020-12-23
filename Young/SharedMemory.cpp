#include "SharedMemory.h"
#include<iostream>

#ifdef WINDOWS_YOUNG
bool ShareMemory::Init(std::string key, UInt32 ssize)
{
	m_Handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, TEXT(key.c_str()));
	if (!m_Handle)
	{
		m_Handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, ssize, TEXT(key.c_str()));
		if (!m_Handle)
		{
			return false;
		}
		m_Mem = MapViewOfFile(m_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (m_Mem == NULL)
		{
			return false;
		}
		m_IsCreate = true;
	}
	else
	{
		m_Mem = MapViewOfFile(m_Handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (m_Mem == NULL)
		{
			return false;
		}
		m_IsCreate = false;
	}
	m_Size = ssize;
	return true;
}
bool ShareMemory::Remove()
{

	if (m_Mem != NULL)
	{
		UnmapViewOfFile(m_Mem);
		m_Mem = NULL;
	}
	if (m_Handle)
	{
		CloseHandle(m_Handle);
		m_Handle = NULL;
	}
	return true;
}
#else

bool ShareMemory::Init(key_t key, UInt32 ssize)
{
	m_ShmId = shmget(key, ssize, IPC_CREAT | IPC_EXCL | 0666);
	if (m_ShmId < 0)
	{
		m_ShmId = shmget(key, ssize, 0666);
		if (m_ShmId < 0)
		{
			std::cout << "shmat err: " << strerror(errno) << std::endl;
			return false;
		}
		m_IsCreate = false;
	}
	else
	{
		m_IsCreate = true;
	}

	m_Mem = shmat(m_ShmId, NULL, 0);
	if (m_Mem == (void *)-1)
	{
		std::cout << "shmat err: " << strerror(errno) << std::endl;
		return false;
	}
	m_Size = ssize;
	return true;
}
bool ShareMemory::Remove()
{
	if (m_Mem != NULL)
	{
		shmdt(m_Mem);
		m_Mem = NULL;
	}
	if (m_ShmId)
	{
		shmctl(m_ShmId, IPC_RMID, 0);
		m_ShmId = NULL;
	}
	return true;
}
#endif
