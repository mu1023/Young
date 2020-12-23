#ifndef _YOUNG_SHAREDMEMORYMAP_H_
#define _YOUNG_SHAREDMEMORYMAP_H_

#include<SharedMemory.h>
#include<YoungDefine.h>''
#include<vector>
#include<map>
#include<string>
template<typename T>
class SharedMemoryMap
{
	struct ChunkHead
	{
		bool   use;
		UInt64 key;
	};
public:
	SharedMemoryMap() {};
	bool Init(UInt64 key, UInt32 num)
	{
		m_ChunkNum = num;
		m_ChunkSize = (sizeof(ChunkHead) + sizeof(T) + 7) / 8 * 8;
		m_Size = m_ChunkNum * m_ChunkSize;
		//TODO
#ifdef WINDOWS_YOUNG
		bool errcode = m_ShareMemory.Init(std::to_string(key), m_Size);
#else
		bool errcode = m_ShareMemory.Init(key, m_Size);
#endif

		if (errcode == 0)
		{
			return false;
		}
		m_MemBegin = (char*)m_ShareMemory.GetMem();
		if (m_ShareMemory.IsCreate())
		{
			memset(m_MemBegin, 0, m_Size);
		}

		Load();
		return true;
	}
	void Load()
	{
		for (UInt32 i = 0; i < m_ChunkNum; i++)
		{
			ChunkHead* head = GetChunkHead(i);
			if (head->use)
			{
				m_SharedChunkByKey[head->key] = i;
			}
			else
			{
				m_FreeChunk.push_back(i);
			}
		}
	}
	ChunkHead* GetChunkHead(UInt32 i)
	{
		return (ChunkHead*)(m_MemBegin + m_ChunkSize * i);
	}
	T* GetChunkData(UInt32 i)
	{
		return (T*)(m_MemBegin + m_ChunkSize * i + sizeof(ChunkHead));
	}
	T* Get(UInt64 key)
	{
		if (m_SharedChunkByKey.count(key) == 0)
		{
			if (m_FreeChunk.empty())
			{
				return NULL;
			}
			UInt32  idx = m_FreeChunk.back();
			m_FreeChunk.pop_back();
			m_SharedChunkByKey[key] = idx;
			ChunkHead* head = GetChunkHead(idx);
			head->key = key;
			head->use = true;
			return GetChunkData(idx);
		}
		else
		{
			UInt32 idx = m_SharedChunkByKey[key];
			return GetChunkData(idx);
		}

	}
	T* Find(UInt64 key)
	{
		if (m_SharedChunkByKey.count(key) == 0)
		{
			return NULL;
		}
		UInt32 idx = m_SharedChunkByKey[key];
		return GetChunkData(idx);
	}
	void Remove(UInt64 key)
	{
		if (m_SharedChunkByKey.count(key) == 0)
		{
			return;
		}

		UInt32 idx = m_SharedChunkByKey[key];
		ChunkHead* head = GetChunkHead(idx);
		memset(head, 0, m_ChunkSize);
		m_SharedChunkByKey.erase(key);
		m_FreeChunk.push_back(idx);
	}
private:
	//多少块内存
	UInt32							m_ChunkNum;
	//每一块的大小
	UInt32							m_ChunkSize;
	//共享内存大小
	UInt32							m_Size;
	char*							m_MemBegin;
	std::vector<UInt32>				m_FreeChunk;
	std::map<UInt64, UInt32>		m_SharedChunkByKey;
	ShareMemory						m_ShareMemory;
};

#endif // _YOUNG_SHAREDMEMORYMAP_H_

//_(key,idx)__________________|__(value)______________________________________________