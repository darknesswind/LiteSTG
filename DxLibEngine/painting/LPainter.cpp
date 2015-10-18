#include "stdafx.h"
#include "LPainter.h"
#include "LImage.h"
#include "LPoint.h"
#include "Vector2.hpp"

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

void LPainter::drawGraph(int x, int y, LImage img, bool TransFlag)
{
	CheckRes(DxLib::DrawGraph(x, y, img.m_handle, TransFlag));
}

void LPainter::drawRotaGraphF(float xf, float yf, double ExRate, Radian Angle, LImage img, bool TransFlag, bool TurnFlag /*= false*/)
{
	CheckRes(DxLib::DrawRotaGraphF(xf, yf, ExRate, Angle.radian(), img.m_handle, TransFlag, TurnFlag));
}

void LPainter::drawExtRotaGraph(float fx, float fy, float ExRateX, float ExRateY, Radian RAD, LImage img, bool turnFlag /*= false*/)
{
	QSize size = img.size();
	float x = size.width() / 2.0f, y = size.height() / 2.0f;

	Vector2 p1(-x * ExRateX, -y);
	Vector2 p2(x * ExRateX + 1, -y);
	Vector2 p3(x * ExRateX + 1, y * ExRateY);
	Vector2 p4(-x * ExRateX, y * ExRateY);

	if (turnFlag)
	{
		float fHead = y * ExRateY;
		p1.setY(fHead);
		p2.setY(fHead);
		p3.setY(-y);
		p4.setY(-y);
	}
	Vector2 *ar[4] = { &p1, &p2, &p3, &p4 };
	for (int i = 0; i < 4; ++i)
	{
		ar[i]->rotate(RAD);
		ar[i]->rx() += fx;
		ar[i]->ry() += fy;
	}
	// 	DrawCircle(pos.x, pos.y, 2, 0xFFFF, 0);
	// 	DrawQuadrangle(p1.x, p1.y,	p2.x, p2.y,
	// 		p3.x, p3.y,	p4.x, p4.y, 0xFFFFFF, false);
	CheckRes(DxLib::DrawModiGraphF(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y(), p4.x(), p4.y(), img.m_handle, true));
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
	return (DxDrawMode)DxLib::GetDrawMode();
}

DxBlendMode LPainter::getDrawBlendMode(int* pParam /*= nullptr*/)
{
	int blendMode;
	CheckRes(DxLib::GetDrawBlendMode(&blendMode, pParam));
	return (DxBlendMode)blendMode;
}

void LPainter::drawPrimitive2D(VERTEX2D* vertexs, int nCount, PrimitiveType type, LHandle hGraph, bool bTrans)
{
	DxLib::DrawPrimitive2D(vertexs, nCount, (int)type, hGraph, bTrans);
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
	setDrawBlendMode(arg.blendMode, (uchar)arg.blendParam);
}

