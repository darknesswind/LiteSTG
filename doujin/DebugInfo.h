#ifndef _DEBUGINFO_H_
#define _DEBUGINFO_H_
#pragma once
#include "interfaceDef.h"

// 显示Debug信息的类
class DebugInfo : public IComponent
{
public:
	DebugInfo(void)
	{
	}
	virtual ~DebugInfo(void) {}

	virtual void Update();
	virtual void Draw();

private:
};

#endif