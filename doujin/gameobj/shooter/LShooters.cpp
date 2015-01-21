#include "stdafx.h"
#include "LShooters.h"
#include "LSegShooter.h"
#include "LRayShooter.h"

LShooters::LShooters()
{
}

LShooters::~LShooters()
{
}

LShooter* LShooters::Add(ShooterType type, IGameObject* pParent)
{
	LShooter* pShooter = nullptr;
	switch (type)
	{
	case ShooterType::Normal:
		pShooter = new LShooter(pParent);
		break;
	case ShooterType::Segment:
		pShooter = new LSegShooter(pParent);
		break;
	case ShooterType::Ray:
		pShooter = new LRayShooter(pParent);
		break;
	case ShooterType::Curve:
		break;
	default:
		break;
	}
	m_thisList.push_back(pShooter);
	return pShooter;
}

LShooter* LShooters::AddNormalShooter(IGameObject* pParent)
{
	QuickImplGameObjAdd(LShooter);
}

LSegShooter* LShooters::AddSegShooter(IGameObject* pParent)
{
	QuickImplGameObjAdd(LSegShooter);
}

LRayShooter* LShooters::AddRayShooter(IGameObject* pParent)
{
	QuickImplGameObjAdd(LRayShooter);
}
