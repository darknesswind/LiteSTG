#ifndef _DEBUGINFO_H_
#define _DEBUGINFO_H_
#pragma once

// 显示Debug信息的类
class DebugInfo
{
public:
	DebugInfo(void)
	{
	}
	~DebugInfo(void) {}

	void Update();
	void Draw(LPainter& painter);

private:
};

#endif