#include "stdafx.h"
#include "LBullets.h"
#include "SegmentLaser.h"
#include "RayLaser.h"
#include "CurveLaser.h"
#include "LBulletStyles.h"

LBullets::LBullets()
{
	m_spStyles = std::make_unique<LBulletStyles>();
}

Bullet* LBullets::Add(BulletType type, IGameObject* pParent)
{
	Bullet* pItem = nullptr;
	switch (type)
	{
	default:
	case BulletType::Generic:
		pItem = new Bullet(pParent);
		break;
	case BulletType::SegmentLaser:
		pItem = new SegmentLaser(pParent);
		break;
	case BulletType::RayLaser:
		pItem = new RayLaser(pParent);
		break;
	case BulletType::CurveLaser:
		pItem = new CurveLaser(pParent);
		break;
	}

	m_thisList.push_back(pItem);
	return pItem;
}

Bullet* LBullets::AddGenericBullet(IGameObject* pParent)
{
	QuickImplGameObjAdd(Bullet);
}

SegmentLaser* LBullets::AddSegmentLaser(IGameObject* pParent)
{
	QuickImplGameObjAdd(SegmentLaser);
}

RayLaser* LBullets::AddRayLaser(IGameObject* pParent)
{
	QuickImplGameObjAdd(RayLaser);
}

CurveLaser* LBullets::AddCurveLaser(IGameObject* pParent)
{
	QuickImplGameObjAdd(CurveLaser);
}

void LBullets::UpdateChildren()
{
	parallel_for_each(parallel_begin(m_thisList), parallel_end(m_thisList), [](Bullet* pItem)
	{
		pItem->Update();
	});
}
