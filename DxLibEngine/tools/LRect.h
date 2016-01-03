#pragma once
#include "LPoint.h"
#include "LSize.h"
class LRect
{
public:
	LRect() = default;

	int& rx() { return m_x; }
	int& ry() { return m_y; }
	int x() const { return m_x; }
	int y() const { return m_y; }
	LPoint pos() const { return LPoint(m_x, m_y); }
	void setPos(int x, int y) { m_x = x; m_y = y; }

	int& rwidth() { return m_width; }
	int& rheight() { return m_height; }
	int width() const { return m_width; }
	int height() const { return m_height; }
	LSize size() const { return LSize(m_width, m_height); }
	void setSize(int width, int height) { m_width = width; m_height = height; }

private:
	int m_x = 0;
	int m_y = 0;
	int m_width = 0;
	int m_height = 0;
};