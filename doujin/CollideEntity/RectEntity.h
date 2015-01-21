#ifndef BULLETENTITY_H
#define BULLETENTITY_H

#pragma once
#include "Entity.h"
class RectEntity : public Entity
{
public:
	RectEntity(float halfofwidth, float halfofheight)
		: Entity(Vector2(0, 0)), halfOfWidth(halfofwidth), halfOfHeight(halfofheight){}

	RectEntity(const Vector2 &center, float halfofwidth, float halfofheight)
		: Entity(center), halfOfWidth(halfofwidth), halfOfHeight(halfofheight){}

	RectEntity(float cx, float cy, float halfofwidth, float halfofheight)
		: Entity(Vector2(cx, cy)), halfOfWidth(halfofwidth), halfOfHeight(halfofheight){}

public:
	virtual void draw(const Vector2 &pos, Radian rad) const;

public:
	virtual bool isCollideWithPlayer(const Vector2 &self, Radian rad) const;
// 	virtual bool isCollideWith(Entity* pOther) { return pOther->isCollideWith(this); }
// 	virtual bool isCollideWith(RectEntity* pOther);
// 	virtual bool isCollideWith(CircleEntity* pOther);
// 	virtual bool isCollideWith(ElipseEntity* pOther);

public:
	float left() const { return center.x() - halfOfWidth; }
	float top() const { return center.y() - halfOfHeight; }
	float right() const { return center.x() + halfOfWidth; }
	float bottom() const { return center.y() + halfOfHeight; }
	Vector2 leftTop() const { return Vector2(left(), top()); }
	Vector2 rightTop() const { return Vector2(right(), top()); }
	Vector2 rightBottom() const { return Vector2(right(), bottom()); }
	Vector2 leftBottom() const { return Vector2(left(), bottom()); }

public:
	float halfOfWidth;
	float halfOfHeight;

private:
	mutable int color;
};

class ExtRectEntity : public RectEntity
{
public:
	ExtRectEntity();
	~ExtRectEntity();

private:

};

#endif