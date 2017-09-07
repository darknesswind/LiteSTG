#ifndef __LPOINT_H__
#define __LPOINT_H__
#pragma once
class LPoint
{
public:
	LPoint(int x, int y) : m_x(x), m_y(y) {}
	LPoint() : LPoint(0, 0) {}
	LPoint(Vector2 v) : LPoint(v.x(), v.y()) {}

	int x() const { return m_x; }
	int y() const { return m_y; }
	int& rx() { return m_x; }
	int& ry() { return m_y; }

private:
	int m_x;
	int m_y;
};

#endif
