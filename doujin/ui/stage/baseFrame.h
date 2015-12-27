#ifndef _BASEFRAME_H_
#define _BASEFRAME_H_
#pragma once

#include "LImage.h"
// 游戏中背景框的显示
class BaseFrame : public IComponent
{
public:
	BaseFrame();
	virtual ~BaseFrame(void){};

	virtual void Update() override;
	virtual void Draw(LPainter& painter) override;

private:
	LImage m_leftFrame;
	LImage m_topFrame;
	LImage m_rightFrame;
	LImage m_bottomFrame;
};

#endif