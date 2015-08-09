#ifndef ELIPSE_ENTITY_H
#define ELIPSE_ENTITY_H

#pragma once
#include "entity.h"
class ElipseEntity :
	public Entity
{
public:
	ElipseEntity(float rx, float ry, const Vector2 &center = Vector2::zero())
		: Entity(center), rx(rx), ry(ry){}
	ElipseEntity(float rx, float ry, float cx = 0, float cy = 0)
		: Entity(Vector2(cx, cy)), rx(rx), ry(ry){}

public:
	virtual bool isCollideWithPlayer(const Vector2 &self, Radian rad) const override;
	virtual void draw(LPainter& painter, const Vector2 &pos, Radian rad) const override;

protected:
	float rx;
	float ry;
};

#endif