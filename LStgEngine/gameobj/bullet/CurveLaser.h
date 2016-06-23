#ifndef __CURVELASER_H__
#define __CURVELASER_H__
#pragma once
#include "bullet.h"
#include <deque>

struct LaserGrid
{
	Vector2 trunkPos;
	Vector2 leftPos;
	Vector2 rightPos;

	LaserGrid() {}
	LaserGrid(const Vector2& trunk)
		: trunkPos(trunk)
	{}
	LaserGrid(const Vector2& trunk, const Vector2& left, const Vector2& right)
		: trunkPos(trunk), leftPos(left), rightPos(right)
	{}
};

class CurveLaser
	: public Bullet
{
	typedef std::deque<LaserGrid> LaserGrids;
public:
	CurveLaser(IGameObject* pParent)
		: Bullet(pParent)
		, m_nWidth(10)
	{
	}
	virtual ~CurveLaser(){}
	virtual void Update();
	virtual void draw(LPainter& painter);
	virtual BulletType GetType() const { return BulletType::CurveLaser; }

private:
	LaserGrids m_grids;
	int m_nWidth;

private:
	static const int g_MaxGridSize = 40;
};

#endif