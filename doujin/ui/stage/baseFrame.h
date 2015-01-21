#ifndef _BASEFRAME_H_
#define _BASEFRAME_H_
#pragma once
#include "interfaceDef.h"
// 游戏中背景框的显示
class BaseFrame : public IComponent
{
public:
	~BaseFrame(void){};

	virtual void Update();
	virtual void Draw();

private:
};

#endif