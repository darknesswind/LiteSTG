#ifndef _BASEFRAME_H_
#define _BASEFRAME_H_
#pragma once

// 游戏中背景框的显示
class BaseFrame : public IComponent
{
public:
	BaseFrame();
	virtual ~BaseFrame(void){};

	virtual void Update() override;
	virtual void Draw(LPainter& painter) override;

private:
	LGraphHandle m_leftFrame;
	LGraphHandle m_topFrame;
	LGraphHandle m_rightFrame;
	LGraphHandle m_bottomFrame;
};

#endif