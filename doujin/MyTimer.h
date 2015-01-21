//////////////////////////////////////////////////////////////////////////
//								��ʱ����
//	ÿ�ε���update��ʹ���м��صļ�ʱ��������1.����0ʱִ�а󶨵ĺ���
//	update()	��ʱ������
//	setup(timerFunc, int)	Ϊ����ĺ����½�һ����ʱ�������ӵ������б�
//	[]������	ֱ�ӷ��ʼ�ʱ�������б��м�ʱ���ļ���
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
	// װ�ؼ�ʱ������
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