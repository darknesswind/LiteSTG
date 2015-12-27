#ifndef __LSHOOTERS_H__
#define __LSHOOTERS_H__
#include "Manager/SpriteManager.h"
#include "LShooter.h"

class LSegShooter;
class LRayShooter;
class LShooters : public SpriteManager<LShooter>
{
public:
	LShooters();
	~LShooters();

public:
	LShooter* Add(ShooterType type, IGameObject* pParent);
	LShooter* AddNormalShooter(IGameObject* pParent);
	LSegShooter* AddSegShooter(IGameObject* pParent);
	LRayShooter* AddRayShooter(IGameObject* pParent);

private:

};

#endif
