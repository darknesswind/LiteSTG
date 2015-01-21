#ifndef _SPRITEMANAGE_H_
#define _SPRITEMANAGE_H_
#pragma once
#include "LRender.h"

#define QuickImplGameObjAdd(Type)	\
{									\
	Type* pItem = new Type(pParent);\
	m_thisList.push_back(pItem);	\
	return pItem;					\
}

template <class T>
class SpriteManager
{
public:
	typedef T ElemType;
	typedef std::list<T*> ListType;

	SpriteManager(void) = default;
	virtual ~SpriteManager(void)
	{
		Clear();
	}

	void Update()
	{
		for each (T *pItem in m_thisList)
		{
			pItem->Update();
		}
		m_thisList.remove_if([](T *pItem)
		{
			return !(pItem->IsValid());
		});

		for each(T *pItem in m_removeList)
		{
			delete pItem;
		}		
		m_removeList.clear();
	}
	void CommitRender()
	{
		for each(T* pItem in m_thisList)
		{
			Render.PushItem(pItem);
		}
	}

	void Remove(T* pItem)
	{
		m_removeList.push_back(pItem);
		pItem->SetValid(false);
	}
	int GetCount()
	{
		return m_thisList.size();
	}
	void deleteChildOf(int parent)
	{
		m_thisList.remove_if([parent](T* pItem)
		{
			return (pItem->parent == parent);
		});
	}

	void Clear()
	{
		for each(T* pItem in m_thisList)
		{
			delete pItem;
		}
		m_thisList.clear();
	}

protected:
	std::list<T*> m_thisList;
	std::list<T*> m_removeList;
};

#endif