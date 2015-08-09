#include "stdafx.h"
#include "ElipseEntity.h"
#include "Globle.h"
#include "RoundEntity.h"
#include "player/player.h"
#include "LPainter.h"
#include "Engine.h"

bool ElipseEntity::isCollideWithPlayer(const Vector2 &self, Radian rad) const
{
	Player* pPlayer = StgEngine::engine()->GetActivePlayer();
	CircleEntity* playEntity = (CircleEntity*)pPlayer->getEntity();

	const float &r = playEntity->radius();
	Vector2 Vba = pPlayer->position() - self;
	if (Vba.manhattanLength() > rx + ry + 2 * r + center.manhattanLength())
		return false;

	Vba.rotate(rad + Radian90);
	Vba -= center;

	float ar = rx + r;
	float br = ry + r;
	ar *= ar;
	br *= ar;

	if (Vba.x() * Vba.x() * br + Vba.y() * Vba.y() * ar > ar*br)// (x0/(a+r))^2 + (y0/(b+r))^2 > 1
		return false;

	return true;
}

void ElipseEntity::draw(LPainter& painter, const Vector2 &pos, Radian rad) const
{
	painter.drawOval(pos.x() + center.x(), pos.y() + center.y(), rx, ry, LRgb32::White, 0);
}
