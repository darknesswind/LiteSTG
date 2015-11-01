#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#pragma once
class EntityFactory
{
public:
	static const EntityData& getBulletEntity(int type)
	{
		return bulletEntity[0];
	}
	static const EntityData& getLaserEntity(int type)
	{
		return laserEntity[0];
	}
	static const EntityData& getPlayerEntity(int type)
	{
		return playerEntity[0];
	}

private:
	EntityFactory();
	static const EntityData bulletEntity[20];
	static const EntityData laserEntity[20];
	static const EntityData playerEntity[4];

};

#endif