#include "stdafx.h"
#include "DebugPainter.h"

DebugPainter DebugPainter::Instance;

DebugPainter::DebugPainter()
{
}

DebugPainter::~DebugPainter()
{
}

void DebugPainter::Draw()
{
	for (uint i = 0; i < m_quadrangles.size(); ++i)
	{
		Quadrangle& quad = m_quadrangles[i];
		DxLib::DrawQuadrangle(quad.topLeft.x(), quad.topLeft.y(),
			quad.topRight.x(), quad.topRight.y(),
			quad.bottomRight.x(), quad.bottomRight.y(),
			quad.bottomLeft.x(), quad.bottomLeft.y(),
			quad.color, false);
	}
	for (uint i = 0; i < m_circles.size(); ++i)
	{
		Circle& circle = m_circles[i];
		DxLib::DrawCircle(circle.x, circle.y, circle.r, circle.color, false);
	}
	for (uint i = 0; i < m_lines.size(); ++i)
	{
		Line& line = m_lines[i];
		DxLib::DrawLine(line.point1.x(), line.point1.y(), line.point2.x(), line.point2.y(), line.color);
	}

	m_quadrangles.clear();
	m_circles.clear();
	m_lines.clear();
}
