#include "stdafx.h"
#include "RoundEntity.h"
#include "Globle.h"
#include "player/player.h"
#include "LPainter.h"
#include "Engine.h"

bool CircleEntity::isCollideWithPlayer(const Vector2 &self, Radian rad) const
{
	Player* pPlayer = Engine.GetActivePlayer();
	Vector2 VectorB2A = pPlayer->position() - self;
	CircleEntity* playEntity = (CircleEntity*)pPlayer->getEntity();

	if (VectorB2A.manhattanLength() > 2 * (playEntity->radius() + r) + center.manhattanLength())
		return false;

	Vector2 target = self - center.rotated(rad + Radian90);
	DebugPat.AddLine(pPlayer->position(), target, LRgb::White);

	VectorB2A += center.rotated(rad + Radian90);
	auto sum = playEntity->radius() + r;
	auto len = VectorB2A.lengthSquared();
	return len < sum*sum;
}

void CircleEntity::draw(const Vector2 &pos, Radian rad) const
{
	Vector2 target = pos - center.rotated(rad);
	DebugPat.AddCircle(target.x(), target.y(), r, LRgb::White);
}
