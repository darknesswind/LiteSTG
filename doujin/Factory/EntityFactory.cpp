#include "stdafx.h"
#include "EntityFactory.h"
#include "CollideEntity/RectEntity.h"
#include "CollideEntity/RoundEntity.h"
#include "CollideEntity/ElipseEntity.h"

// const Entity* EntityFactory::getBulletEntity( int type )
// {
// 	return bulletEntity[0];
// }
// 
// const RoundEntity* EntityFactory::getPlayerEntity( int type )
// {
// 	return playerEntity[0];
// }

const Entity *EntityFactory::bulletEntity[20] = 
{
// 	new CircleEntity(Vector2(-3, 0), 2)
	new CircleEntity(0, 0, 10),
	new RectEntity(0, 3, 2, 2),
};

const CircleEntity *EntityFactory::playerEntity[4] =
{
	new CircleEntity(3)
};

const RectEntity *EntityFactory::laserEntity[20] =
{
	new RectEntity(0.5, 4),
	new RectEntity(0.5, 3.5),		// ¡€µØ
};


// const Entity* EntityFactory::getLaserEntity( int type )
// {
// 	return laserEntity[0]
// }
