#include "stdafx.h"
#include "RectEntity.h"
#include "Globle.h"
#include "RoundEntity.h"
#include "player/player.h"
#include "LPainter.h"
#include "Engine.h"

bool RectEntity::isCollideWithPlayer(const Vector2 &self, Radian rad) const
{
	Player* pPlayer = Engine.GetActivePlayer();
	CircleEntity* playEntity = (CircleEntity*)pPlayer->getEntity();

	float r = playEntity->radius();
	Vector2 VectToPlayer = pPlayer->position() - self;
	if (VectToPlayer.manhattanLength() > 2 * (halfOfWidth + halfOfHeight + r) + center.manhattanLength())
	{
		color = 0x00FF00;
		return false;
	}
	VectToPlayer.rotate(rad + Radian90);
	VectToPlayer -= center;
	VectToPlayer.abs();
	Painter.drawLine(pPlayer->position(), self, LRgb::White);

	color = 0x1111FF;
	if (VectToPlayer.x() > halfOfWidth + r) return false;
	if (VectToPlayer.y() > halfOfHeight + r) return false;
	Vector2 newVect = VectToPlayer - Vector2(halfOfWidth, halfOfHeight);
	if (newVect.x() > 0 && newVect.y() > 0
		&& newVect.lengthSquared() > r*r)
	{
		return false;
	}
	color = 0xFF0000;
	return true;
}

void RectEntity::draw(const Vector2 &pos, Radian rad) const
{
	Vector2 vLTop = pos + leftTop().rotate(rad);
	Vector2 vRTop = pos + rightTop().rotate(rad);
	Vector2 vRBottom = pos + rightBottom().rotate(rad);
	Vector2 vLBottom = pos + leftBottom().rotate(rad);
	Painter.drawQuadrangle(vLTop, vRTop, vRBottom, vLBottom, color, false);
}

// bool RectEntity::isCollideWith(RectEntity* pOther)
// {
// 
// }
// 
// bool RectEntity::isCollideWith(CircleEntity* pOther)
// {
// 
// }
// 
// bool RectEntity::isCollideWith(ElipseEntity* pOther)
// {
// 
// }
