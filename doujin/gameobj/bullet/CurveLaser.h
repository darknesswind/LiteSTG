#ifndef __CURVELASER_H__
#define __CURVELASER_H__
#pragma once
#include "bullet.h"
#include "CollideEntity/RectEntity.h"
#include <QQueue>

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
	typedef QQueue<LaserGrid> LaserGrids;
public:
	CurveLaser(IGameObject* pParent)
		: Bullet(pParent)
		, m_nWidth(10)
	{
	}
	virtual ~CurveLaser(){}
	virtual void Update();
	virtual void Draw();
	virtual BulletType GetType() const { return BulletType::CurveLaser; }

private:
	LaserGrids m_grids;
	int m_nWidth;

private:
	static const int g_MaxGridSize = 40;
};

#endif