#ifndef __LPAINTER_H__
#define __LPAINTER_H__
#pragma once

#include "LRgb.h"
#include "base/DxHandleManager.h"
#include "DebugPainter.h"
#include <stack>

#define Painter LPainter::Instance

#pragma region pre-define
class PosType;
class LImage;
class Vector2;
using DxLib::VERTEX2D;
#pragma endregion

class LPainter
{
public:
	static LPainter Instance;
	~LPainter();
	
public:	// 几何图形绘制函数
	void drawPixel(int x, int y, LRgb Color) const;										// 绘制点
	template <typename PosType>
	void drawPixel(const PosType& pt, LRgb Color) const
	{
		drawPixel(pt.x(), pt.y(), Color);
	}

	void drawLine(int x1, int y1, int x2, int y2, LRgb Color, int Thickness = 1) const;	// 绘制线段
	template <typename PosType>
	void drawLine(const PosType& pt1, const PosType& pt2, LRgb Color, int Thickness = 1) const
	{
		drawLine(pt1.x(), pt1.y(), pt2.x(), pt2.y(), Color, Thickness);
	}

	void drawBox(int x1, int y1, int x2, int y2, LRgb Color, bool FillFlag) const;		// 绘制矩形
	template <typename PosType>
	void drawBox(const PosType& pt1, const PosType& pt2, LRgb Color, bool FillFlag) const
	{
		drawBox(pt1.x(), pt1.y(), pt2.x(), pt2.y(), Color, FillFlag);
	}

	void drawFillBox(int x1, int y1, int x2, int y2, LRgb Color) const;					// 绘制有填充的矩形
	template <typename PosType>
	void drawFillBox(const PosType& pt1, const PosType& pt2, LRgb Color) const
	{
		drawFillBox(pt1.x(), pt1.y(), pt2.x(), pt2.y(), Color);
	}

	void drawLineBox(int x1, int y1, int x2, int y2, LRgb Color) const;					// 绘制无填充的矩形
	template <typename PosType>
	void drawLineBox(const PosType& pt1, const PosType& pt2, LRgb Color) const
	{
		drawLineBox(pt1.x(), pt1.y(), pt2.x(), pt2.y(), Color);
	}

	void drawCircle(int x, int y, int r, LRgb Color, bool FillFlag = true) const;		// 绘制圆形
	template <typename PosType>
	void drawCircle(const PosType& pt, int r, LRgb Color, bool FillFlag = true) const
	{
		drawCircle(pt.x(), pt.y(), r, Color, FillFlag);
	}

	void drawOval(int x, int y, int rx, int ry, LRgb Color, bool FillFlag) const;		// 绘制椭圆
	template <typename PosType>
	void drawOval(const PosType& pt, const PosType& radius, LRgb Color, bool FillFlag) const
	{
		drawOval(pt.x(), pt.y(), radius.x(), radius.y(), Color, FillFlag);
	}

	void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int Color, int FillFlag) const;						// 绘制三角形
	template <typename PosType>
	void drawTriangle(const PosType& pt1, const PosType& pt2, const PosType& pt3, LRgb Color, bool FillFlag) const
	{
		drawTriangle(pt1.x(), pt1.y(), pt2.x(), pt2.y(), pt3.x(), pt3.y(), Color, FillFlag);
	}

	void drawQuadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, LRgb Color, bool FillFlag) const;	// 绘制四边形
	template <typename PosType>
	void drawQuadrangle(const PosType& pt1, const PosType& pt2, const PosType& pt3, const PosType& pt4, LRgb Color, bool FillFlag) const
	{
		drawQuadrangle(pt1.x(), pt1.y(), pt2.x(), pt2.y(), pt3.x(), pt3.y(), pt4.x(), pt4.y(), Color, FillFlag);
	}

public:	// 字符串绘制
	void drawString(int x, int y, LPCWSTR pStr, LRgb Color, LRgb EdgeColor = LRgb::Transparent) const;		// 使用默认FontHandle绘制字符串
	template <typename PosType>
	void drawString(const PosType& pt, LPCWSTR pStr, LRgb Color, LRgb EdgeColor = LRgb::Transparent) const
	{
		drawString(pt.x(), pt.y(), pStr, Color, EdgeColor);
	}

	void drawVString(int x, int y, LPCWSTR pStr, LRgb Color, LRgb EdgeColor = LRgb::Transparent) const;		// 使用默认FontHandle纵向绘制字符串
	template <typename PosType>
	void drawVString(const PosType& pt, LPCWSTR pStr, LRgb Color, LRgb EdgeColor = LRgb::Transparent) const
	{
		drawVString(pt.x(), pt.y(), pStr, Color, EdgeColor);
	}

public:	// 图形绘制
	void drawGraph(int x, int y, const LImage& img, bool TransFlag);					// 绘制实际大小图像
	template <typename PosType>
	void drawGraph(const PosType& pt, const LImage& img, bool TransFlag)
	{
		drawGraph(pt.x(), pt.y(), img.m_handle, TransFlag);
	}

	void drawRotaGraphF(float xf, float yf, double ExRate, Radian Angle, const LImage& img, bool TransFlag, bool TurnFlag = false);	// 绘制旋转后的图像
	template <typename PosType>
	void drawRotaGraphF(const PosType& pos, double ExRate, Radian Angle, const LImage& img, bool TransFlag, bool TurnFlag = false)
	{
		drawRotaGraphF(pos.x(), pos.y(), ExRate, Angle, img.m_handle, TransFlag, TurnFlag);
	}

	void drawExtRotaGraph(float fx, float fy, float ExRateX, float ExRateY, Radian RAD, const LImage& img, bool turnFlag = false);
	template <typename PosType>
	void drawExtRotaGraph(const PosType &pos, float ExRateX, float ExRateY, Radian RAD, const LImage& img, bool turnFlag = false)
	{
		drawExtRotaGraph(pos.x(), pos.y(), ExRateX, ExRateY, RAD, img, turnFlag);
	}

public:	// 图元绘制
	void drawPrimitive2D(VERTEX2D* vertexs, int nCount, PrimitiveType type, LHandle hGraph, bool bTrans);

public:
	void save();
	void restore();
	void setPaintArgument(const PaintArgument& arg);
	void setDrawBlendMode(DxBlendMode mode, uchar param);
	void setDrawMode(DxDrawMode mode);
	DxBlendMode getDrawBlendMode(int* pParam = nullptr);
	DxDrawMode getDrawMode();

private:
	LPainter();

private:
	DeleteFunc(LPainter(const LPainter&));			// delete
	DeleteFunc(void operator=(const LPainter&));	// delete

private:
	std::stack<PaintArgument> m_argStack;
};

#endif // !__LPAINTER_H__
