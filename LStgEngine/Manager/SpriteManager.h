#ifndef _SPRITEMANAGE_H_
#define _SPRITEMANAGE_H_
#pragma once
#include "LEngine.h"
#include "render/LRender.h"

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
		clear();
	}

	virtual void update()
	{
		updateChildren();
		m_thisList.remove_if([](T *pItem)
		{
			return !(pItem->IsValid());
		});

		for (T *pItem : m_removeList)
		{
			delete pItem;
		}		
		m_removeList.clear();
	}

	virtual void updateChildren()
	{
		for (T *pItem : m_thisList)
		{
			pItem->Update();
		}
	}

	void commitRender()
	{
		LRender* pRender = LEngine::render();
		for (T* pItem : m_thisList)
		{
			pRender->PushItem(pItem);
		}
	}

	void remove(T* pItem)
	{
		m_removeList.push_back(pItem);
		pItem->SetValid(false);
	}

	int size() 
	{
		return m_thisList.size();
	}

	auto begin() { return m_thisList.begin(); }
	auto end() { return m_thisList.end(); }

	void deleteChildOf(int parent)
	{
		m_thisList.remove_if([parent](T* pItem)
		{
			return (pItem->parent == parent);
		});
	}

	void clear()
	{
		for (T* pItem : m_thisList)
		{
			delete pItem;
		}
		m_thisList.clear();
	}

protected:
	std::list<T*> m_thisList;
	std::vector<T*> m_removeList;
};

#endif