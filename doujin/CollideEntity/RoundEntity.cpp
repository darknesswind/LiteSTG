#include "stdafx.h"
#include "RoundEntity.h"
#include "Globle.h"
#include "player/player.h"
#include "LPainter.h"
#include "Engine.h"

bool CircleEntity::isCollideWithPlayer(const Vector2 &self, Radian rad) const
{
	Player* pPlayer = StgEngine::engine()->GetActivePlayer();
	Vector2 vSelf2Player = pPlayer->position() - self;
	CircleEntity* playEntity = (CircleEntity*)pPlayer->getEntity();

	if (vSelf2Player.manhattanLength() > 2 * (playEntity->radius() + r) + center.manhattanLength())
		return false;

	Vector2 target = self - center.rotated(rad + Radian90);
	DebugPat.AddLine(pPlayer->position(), target, LRgb::White);

	vSelf2Player += center.rotated(rad + Radian90);
	auto sum = playEntity->radius() + r;
	auto len = vSelf2Player.lengthSquared();
	return len < sum*sum;
}

void CircleEntity::draw(LPainter& painter, const Vector2 &pos, Radian rad) const
{
	Vector2 target = pos - center.rotated(rad);
	DebugPat.AddCircle(target.x(), target.y(), r, LRgb::White);
}
