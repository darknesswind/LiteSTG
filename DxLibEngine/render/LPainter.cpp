#include "stdafx.h"
#include "LPainter.h"
#include "tools/LPoint.h"
#include "tools/LSize.h"
#include "tools/Vector2.hpp"

LPainter::LPainter()
{
}

LPainter::~LPainter()
{
}

#pragma region 几何图形绘制

void LPainter::drawPixel(int x, int y, LRgb Color) const
{
	CheckRes(DxLib::DrawPixel(x, y, Color));
}

void LPainter::drawLine(int x1, int y1, int x2, int y2, LRgb Color, int Thickness /*= 1*/) const
{
	CheckRes(DxLib::DrawLine(x1, y1, x2, y2, Color, Thickness));
}

void LPainter::drawBox(int x1, int y1, int x2, int y2, LRgb Color, bool FillFlag) const
{
	CheckRes(DxLib::DrawBox(x1, y1, x2, y2, Color, FillFlag));
}

void LPainter::drawFillBox(int x1, int y1, int x2, int y2, LRgb Color) const
{
	CheckRes(DxLib::DrawFillBox(x1, y1, x2, y2, Color));
}

void LPainter::drawLineBox(int x1, int y1, int x2, int y2, LRgb Color) const
{
	CheckRes(DxLib::DrawLineBox(x1, y1, x2, y2, Color));
}

void LPainter::drawCircle(int x, int y, int r, LRgb Color, bool FillFlag /*= true*/) const
{
	CheckRes(DxLib::DrawCircle(x, y, r, Color, FillFlag));
}

void LPainter::drawOval(int x, int y, int rx, int ry, LRgb Color, bool FillFlag) const
{
	CheckRes(DxLib::DrawOval(x, y, rx, ry, Color, FillFlag));
}

void LPainter::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int Color, int FillFlag) const
{
	CheckRes(DxLib::DrawTriangle(x1, y1, x2, y2, x3, y3, Color, FillFlag));
}

void LPainter::drawQuadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, LRgb Color, bool FillFlag) const
{
	CheckRes(DxLib::DrawQuadrangle(x1, y1, x2, y2, x3, y3, x4, y4, Color, FillFlag));
}

#pragma endregion

#pragma region 字符串绘制

void LPainter::drawString(int x, int y, LPCWSTR pStr, LRgb Color, LRgb EdgeColor /*= LRgb::Transparent*/) const
{
	CheckRes(DxLib::DrawString(x, y, pStr, Color, EdgeColor));
}

void LPainter::drawVString(int x, int y, LPCWSTR pStr, LRgb Color, LRgb EdgeColor /*= LRgb::Transparent*/) const
{
	CheckRes(DxLib::DrawVString(x, y, pStr, Color, EdgeColor));
}

#pragma endregion

#pragma region 图形绘制

void LPainter::drawGraph(int x, int y, LGraphHandle hGraph, bool TransFlag)
{
	CheckRes(DxLib::DrawGraph(x, y, hGraph, TransFlag));
}

void LPainter::drawRotaGraphF(float xf, float yf, double ExRate, Radian Angle, LGraphHandle hGraph, bool TransFlag, bool TurnFlag /*= false*/)
{
	CheckRes(DxLib::DrawRotaGraphF(xf, yf, ExRate, Angle.radian(), hGraph, TransFlag, TurnFlag));
}

void LPainter::drawExtRotaGraph(float fx, float fy, float ExRateX, float ExRateY, Radian RAD, LGraphHandle hGraph, bool turnFlag /*= false*/)
{
	LSize size;
	hGraph.getSize(size);
	float x = size.width() / 2.0f, y = size.height() / 2.0f;

	std::array<Vector2, 4> rc = 
	{
		Vector2(-x * ExRateX, -y),
		Vector2(x * ExRateX + 1, -y),
		Vector2(x * ExRateX + 1, y * ExRateY),
		Vector2(-x * ExRateX, y * ExRateY)
	};

	if (turnFlag)
	{
		float fHead = y * ExRateY;
		rc[0].setY(fHead);
		rc[1].setY(fHead);
		rc[2].setY(-y);
		rc[3].setY(-y);
	}

	for (Vector2& pt : rc)
	{
		pt.rotate(RAD);
		pt.rx() += fx;
		pt.ry() += fy;
	}
	// 	DrawCircle(pos.x, pos.y, 2, 0xFFFF, 0);
	// 	DrawQuadrangle(p1.x, p1.y,	p2.x, p2.y,
	// 		p3.x, p3.y,	p4.x, p4.y, 0xFFFFFF, false);
	CheckRes(DxLib::DrawModiGraphF(rc[0].x(), rc[0].y(), rc[1].x(), rc[1].y(), rc[2].x(), rc[2].y(), rc[3].x(), rc[3].y(), hGraph, true));
}

#pragma endregion


void LPainter::setDrawBlendMode(DxBlendMode mode, uchar param)
{
	CheckRes(DxLib::SetDrawBlendMode((int)mode, param));
}

void LPainter::setDrawMode(DxDrawMode mode)
{
	CheckRes(DxLib::SetDrawMode((int)mode));
}

DxDrawMode LPainter::getDrawMode()
{
	return static_cast<DxDrawMode>(DxLib::GetDrawMode());
}

DxBlendMode LPainter::getDrawBlendMode(int* pParam /*= nullptr*/)
{
	int blendMode;
	CheckRes(DxLib::GetDrawBlendMode(&blendMode, pParam));
	return static_cast<DxBlendMode>(blendMode);
}

void LPainter::drawPrimitive2D(VERTEX2D* vertexs, int nCount, PrimitiveType type, LHandle hGraph, bool bTrans)
{
	DxLib::DrawPrimitive2D(vertexs, nCount, static_cast<int>(type), hGraph, bTrans);
}

void LPainter::save()
{
	PaintArgument arg;
	arg.drawMode = getDrawMode();
	arg.blendMode = getDrawBlendMode(&arg.blendParam);
	m_argStack.push(arg);
}

void LPainter::restore()
{
	setPaintArgument(m_argStack.top());
	m_argStack.pop();
}

void LPainter::setPaintArgument(const PaintArgument& arg)
{
	setDrawMode(arg.drawMode);
	setDrawBlendMode(arg.blendMode, static_cast<uchar>(arg.blendParam));
}

