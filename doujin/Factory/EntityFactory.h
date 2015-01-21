#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#pragma once
class Entity;
class CircleEntity;
class RectEntity;
class EntityFactory
{
public:
	static const Entity* getBulletEntity(int type)
	{
		return bulletEntity[0];
	}
	static const RectEntity* getLaserEntity(int type)
	{
		return laserEntity[0];
	}
	static const CircleEntity* getPlayerEntity(int type)
	{
		return playerEntity[0];
	}

private:
	EntityFactory();
	static const Entity *bulletEntity[20];
	static const RectEntity *laserEntity[20];
	static const CircleEntity *playerEntity[4];

};

#endif