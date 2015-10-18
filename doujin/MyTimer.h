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
#define USE_FASTFUNC 0
#if USE_FASTFUNC
#include "FastFunc.hpp"
using namespace ssvu;
typedef FastFunc<void(uint&)> timerFunc;
#else
typedef void (*timerFunc)(uint&);
#endif

class MyTimer
{
public:
	MyTimer(){}
	~MyTimer(void){};
	
	struct DATA
	{
		DATA(uint c = 0, timerFunc f = nullptr)
			: counter(c), func(f)
		{
		}
		uint counter;
		timerFunc func;
	};
	void update(void)
	{
		for each(auto d in tim)
		{
			if (--d.counter == 0)
			{
				d.func(d.counter);
			}
		}
	}
	// װ�ؼ�ʱ������
	void setup(timerFunc f, uint time)
	{
		tim.push_back(DATA(time,f));
	}
	uint& operator[](const uint n)
	{
		return tim[n].counter;
	}
	const uint operator[](const uint n) const
	{
		return tim[n].counter;
	}
private:	
	std::vector<DATA> tim;
};
#endif