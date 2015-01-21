//////////////////////////////////////////////////////////////////////////
//								计时器组
//	每次调用update将使所有加载的计时器计数减1.到达0时执行绑定的函数
//	update()	计时器更新
//	setup(timerFunc, int)	为传入的函数新建一个计时器并附加到更新列表
//	[]操作符	直接访问计时器更新列表中计时器的计数
//////////////////////////////////////////////////////////////////////////
#ifndef _MY_TIMER_
#define _MY_TIMER_
#pragma once
#include "FastFunc.hpp"
#include <vector>
using namespace ssvu;
typedef FastFunc<void(int&)> timerFunc;
class MyTimer
{
public:
	MyTimer(){}
	~MyTimer(void){};
	
	struct DATA
	{
		DATA(int c = 0, timerFunc f = nullptr)
			: counter(c), func(f)
		{
		}
		int counter;
		timerFunc func;
	};
	void update(void)
	{
		for each(auto d in tim)
		{
			if (d.counter >= 0 && --d.counter == 0)
			{
				d.func(d.counter);
			}
		}		
	}
	// 装载计时器函数
	void setup(timerFunc f, int time)
	{
		tim.push_back(DATA(time,f));
	}
	int& operator[](const int n)
	{
		return tim[n].counter;
	}
	const int operator[](const int n) const
	{
		return tim[n].counter;
	}
private:	
	std::vector<DATA> tim;
};
#endif