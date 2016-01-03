#include "stdafx.h"
#include "EntityFactory.h"

const EntityData EntityFactory::bulletEntity[20] = 
{
	_InnerEntityData{ EntityData::tCircle, { 0, -5 }, 10 },
	_InnerEntityData{ EntityData::tRectangle,{ 0, 3 }, 2, 2 },
};

const EntityData EntityFactory::playerEntity[4] =
{
	_InnerEntityData{ EntityData::tCircle, { 0, 0 }, 3, 3 },
};

const EntityData EntityFactory::laserEntity[20] =
{
	_InnerEntityData{ EntityData::tRectangle, { 0, 0 }, 0.5, 4 },
	_InnerEntityData{ EntityData::tRectangle, { 0, 0 }, 0.5, 3.5 }, // ¡€µØ
};
