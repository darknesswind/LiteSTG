// 组件管理器
// 对所管理的对象集中进行update和draw操作
//
#ifndef _COMMANAGE_H_
#define _COMMANAGE_H_
#pragma once
#include "interdef.h"
#include <list>
__interface IComponent;
class ComManager 	// 一般的组件管理器
{
	typedef std::list<IComponent*> ComList;
public:
	ComManager(void) {};
	virtual ~ComManager(void) {};

	void Update();
	void Draw() const;
	void push_back(IComponent *component)
	{
		thisList.push_back(component);
	}
	void push_front(IComponent *component)
	{
		thisList.push_front(component);
	}
	void Remove(IComponent *component);
	void clear() { thisList.clear(); }
	ComList::size_type size() const { return thisList.size(); }

protected:
	std::list<IComponent*> thisList;

private:
	ComManager(const ComManager&) = delete;
	ComManager& operator=(const ComManager&) = delete;
};

#endif