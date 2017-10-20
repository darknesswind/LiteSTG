#ifndef BULLETSYSTEM_H
#define BULLETSYSTEM_H
#pragma once
#include <vector>

template <uint g_objectSize, uint c_chunkSize = 1024>
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
	struct chunk_t { FreeListNode node[c_chunkSize]; };

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
			FreeListNode* pFreeNode = static_cast<FreeListNode*>(pObject);
			pFreeNode->pNext = m_pFreeListHeader;
			m_pFreeListHeader = pFreeNode;
		}
	}


protected:
	void allocNewChunk()
	{
		chunk_t* pChunk = new (std::nothrow) chunk_t;
		if (pChunk)
		{
			for (uint i = 0; i < c_chunkSize - 1; ++i)
			{
				pChunk->node[i].pNext = &(pChunk->node[i + 1]);
			}
			pChunk->node[c_chunkSize - 1].pNext = m_pFreeListHeader;
			m_pFreeListHeader = pChunk->node;
			m_chunkList.push_back(pChunk);
		}
	}

	void freeChunk(uint idx)
	{
		if (idx < m_chunkList.size())
		{
			delete m_chunkList[idx];
		}
	}

	uint getObjectLocal(const void* pObject)
	{
		for (uint i = 0; i < m_chunkList.size(); ++i)
		{
			const int nOffset = static_cast<const FreeListNode*>(pObject) - static_cast<const FreeListNode*>(m_chunkList[i]->node);
			if (nOffset >= 0 && nOffset < c_chunkSize)
				return i;
		}
		return (uint)-1;
	}


private:
	std::vector<chunk_t*> m_chunkList;
	FreeListNode* m_pFreeListHeader;
	uint m_nAllocCount;
};

#endif // !BULLETSYSTEM_H


