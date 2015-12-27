#ifndef __DEBUG_PAINTER_H__
#define __DEBUG_PAINTER_H__
#pragma once
#include <vector>
#include <array>
#include "Vector2.hpp"
#include "LRgb.h"
#include "LPoint.h"

#define  DebugPat DebugPainter::instance()
class DebugPainter
{
	struct Circle
	{
		Circle() : x(0), y(0), r(0) {}
		Circle(int cx, int cy, int cr, LRgb clr)
			: x(cx), y(cy), r(cr), color(clr)
		{
		}
		int x, y, r;
		LRgb color;
	};
	struct Quadrangle
	{
		Quadrangle(LPoint ptTopLeft, LPoint ptTopRight
			, LPoint ptBottomRight, LPoint ptBottomLeft
			, LRgb clr)
			: topLeft(ptTopLeft), topRight(ptTopRight)
			, bottomRight(ptBottomRight), bottomLeft(ptBottomLeft)
			, color(clr)
		{
		}
		LPoint topLeft, topRight;
		LPoint bottomRight, bottomLeft;
		LRgb color;
	};
	struct Line
	{
		Line() = default;
		Line(LPoint p1, LPoint p2, LRgb clr)
			: point1(p1), point2(p2), color(clr)
		{
		}
		LPoint point1, point2;
		LRgb color;
	};
#if USE_PPL
	typedef concurrent_vector<Quadrangle> QuadrangleList;
	typedef concurrent_vector<Circle> CircleList;
	typedef concurrent_vector<Line> LineList;
#else
	typedef std::vector<Quadrangle> QuadrangleList;
	typedef std::vector<Circle> CircleList;
	typedef std::vector<Line> LineList;
#endif

public:
	DebugPainter();
	~DebugPainter();

	static DebugPainter& instance() { return Instance; }
	void Draw();

public:
	template<typename PosType>
	void AddLine(PosType p1, PosType p2, LRgb clr)
	{
		m_lines.push_back(Line((LPoint)p1, (LPoint)p2, clr));
	}
	void AddCircle(int x, int y, int r, LRgb clr)
	{
		m_circles.push_back(Circle(x, y, r, clr));
	}
	template<typename PosType>
	void AddQuadrangle(PosType topLeft, PosType topRight, PosType bottomRight, PosType bottomLeft, LRgb clr)
	{
		m_quadrangles.push_back(Quadrangle(topLeft, topRight, bottomRight, bottomLeft, clr));
	}

private:
	static DebugPainter Instance;
	QuadrangleList m_quadrangles;
	CircleList	m_circles;
	LineList	m_lines;
};

#endif
