#ifndef ENTITY_H
#define ENTITY_H
#include "Vector2.hpp"

class RectEntity;
class CircleEntity;
class ElipseEntity;
class LPainter;

class Entity	// Åö×²ÊµÌå
{
	friend class EntityFactory;
public:
	Entity()	{ }
	Entity(const Vector2 &center)
		: center(center)
	{
	}
	virtual ~Entity(void) = 0 { }

public:
	virtual bool isCollideWithPlayer(const Vector2 &self, Radian rad) const
	{
		return false;
	}
// 	virtual bool isCollideWith(Entity* pOther) const = 0;
// 	virtual bool isCollideWith(RectEntity* pOther) const = 0;
// 	virtual bool isCollideWith(CircleEntity* pOther) const = 0;
// 	virtual bool isCollideWith(ElipseEntity* pOther) const = 0;

public:
	virtual void draw(LPainter& painter, const Vector2 &pos, Radian rad) const = 0;

public:
	Vector2 center;
};

#endif