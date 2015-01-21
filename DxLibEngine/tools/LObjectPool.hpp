#ifndef BULLETSYSTEM_H
#define BULLETSYSTEM_H
#pragma once
#include <vector>

template <uint g_objectSize, uint g_chunkSize = 1024>
class LObjectPool
{
	static_assert(
		g_objectSize > sizeof(void*),
		"object size must be greater then size of pointer"
		);

	union FreeListNode
	{
		uchar bytes[g_objectSize];
		FreeListNode* pNext;
	};


public:
	LObjectPool(void)
		: m_pFreeListHeader(NULL)
		, m_nAllocCount(0)
	{
	}

	~LObjectPool(void)
	{
		for (uint i = 0; i < m_chunkList.size(); ++i)
		{
			freeChunk(i);
		}
	}

	void* malloc()
	{
		if (!m_pFreeListHeader)
			allocNewChunk();

		++m_nAllocCount;
		FreeListNode* pObject = m_pFreeListHeader;
		m_pFreeListHeader = m_pFreeListHeader->pNext;
// 		::new ((void*)pObject)ObjectType();/* std::allocator<ObjectType>().construct(pObject);*/

		LAssert(!m_pFreeListHeader || getObjectLocal(m_pFreeListHeader) < m_chunkList.size());
		return pObject;
	}

	void free(void* pObject)
	{
		if (pObject)
		{
			LAssert(getObjectLocal(pObject) < m_chunkList.size());

			--m_nAllocCount;
// 			((ObjectType*)pObject)->~ObjectType();
			((FreeListNode*)pObject)->pNext = m_pFreeListHeader;
			m_pFreeListHeader = (FreeListNode*)pObject;
		}
	}


protected:
	void allocNewChunk()
	{
		FreeListNode* pChunk = (FreeListNode*)::malloc(g_chunkSize * sizeof(FreeListNode));
		if (pChunk)
		{
			for (uint i = 0; i < g_chunkSize - 1; ++i)
			{
				pChunk[i].pNext = &(pChunk[i + 1]);
			}
			pChunk[g_chunkSize - 1].pNext = m_pFreeListHeader;
			m_pFreeListHeader = pChunk;
			m_chunkList.push_back(pChunk);
		}
	}

	void freeChunk(uint idx)
	{
		if (idx < m_chunkList.size())
		{
			::free(m_chunkList[idx]);
		}
	}

	uint getObjectLocal(void* pObject)
	{
		for (uint i = 0; i < m_chunkList.size(); ++i)
		{
			int nOffset = (FreeListNode*)pObject - m_chunkList[i];
			if (nOffset >= 0 && nOffset < g_chunkSize)
				return i;
		}
		return -1;
	}


private:
	std::vector<FreeListNode*> m_chunkList;
	FreeListNode* m_pFreeListHeader;
	uint m_nAllocCount;
};

#endif // !BULLETSYSTEM_H


