﻿#ifndef __LBULLETS_H__
#define __LBULLETS_H__

#pragma once
#include "Manager/SpriteManager.h"
#include "Bullet.h"

class SegmentLaser;
class RayLaser;
class CurveLaser;
class Bullet;
class LBulletStyles;
class LBullets : public SpriteManager<Bullet>
{
public:
	LBullets();
	void updateChildren() override;
	LBulletStyles* styles() { return m_spStyles.get(); }

public:
	Bullet* Add(BulletType type, IGameObject* pParent);
	Bullet* AddGenericBullet(IGameObject* pParent);
	SegmentLaser* AddSegmentLaser(IGameObject* pParent);
	RayLaser* AddRayLaser(IGameObject* pParent);
	CurveLaser* AddCurveLaser(IGameObject* pParent);

private:
	std::unique_ptr<LBulletStyles> m_spStyles;
};

#endif
