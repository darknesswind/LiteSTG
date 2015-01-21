#ifndef __LPOINT_H__
#define __LPOINT_H__
#pragma once
#include <QPoint>
// 暂时没有特化的需要
class LPoint : public QPoint
{
public:
	LPoint()
	{
	}

	LPoint(int xpos, int ypos) : QPoint(xpos, ypos)
	{
	}

};
typedef QPointF LPointF;

#endif
