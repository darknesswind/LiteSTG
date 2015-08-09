#pragma once
#include "Entity.h"
class CircleEntity : public Entity
{
public:
	CircleEntity(float r)
		: Entity(Vector2(0, 0)), r(r){}

	CircleEntity(const Vector2 &center, float r)
		: Entity(center), r(r){}

	CircleEntity(float cx, float cy, float r)
		: Entity(Vector2(cx, cy)), r(r){}

	~CircleEntity(void){}

public: // Entity
	virtual bool isCollideWithPlayer(const Vector2 &self, Radian) const override;
	virtual void draw(LPainter& painter, const Vector2 &pos, Radian rad) const override;

public:
	const float radius() const { return r; }

private:
	float r;
};

