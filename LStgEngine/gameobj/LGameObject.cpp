#include "stdafx.h"
#include "LGameObject.h"
#include "LHandle.h"

LGameObject::LGameObject(IGameObject* pParent /*= nullptr*/)
	: m_bValid(true)
	, m_pParent(pParent)
{

}

//////////////////////////////////////////////////////////////////////////
#define center m_entity.center
#define radius m_entity.halfWidth

void LCollideObject::DrawHitBox(LPainter& painter)
{
	if (LRgb::White == m_hitboxClr)
		return;

#define left	center.x() - m_entity.halfWidth
#define top		center.y() - m_entity.halfHeight
#define right	center.x() + m_entity.halfWidth
#define bottom	center.y() + m_entity.halfHeight

	Radian rad = m_phyData.radian + Radian90;
	switch (m_entity.type)
	{
	case EntityData::tCircle:
	{
		Vector2 target = position() + center.rotated(rad);
		DebugPat.AddCircle(target.x(), target.y(), radius, m_hitboxClr);
		break;
	}
	case EntityData::tRectangle:
	{
		Vector2 vLTop = position() + Vector2(left, top).rotate(rad);
		Vector2 vRTop = position() + Vector2(right, top).rotate(rad);
		Vector2 vRBottom = position() + Vector2(right, bottom).rotate(rad);
		Vector2 vLBottom = position() + Vector2(left, bottom).rotate(rad);
		painter.drawQuadrangle(vLTop, vRTop, vRBottom, vLBottom, m_hitboxClr, false);
		break;
	}
	default:
		break;
	}
#undef left
#undef top
#undef right
#undef bottom
}

bool LCollideObject::CollideWith(const LCollideObject& other)
{
	bool bResult = false;
	switch (other.m_entity.type)
	{
	case EntityData::tCircle:
		bResult = CollideWithCircle(other);
		break;
	case EntityData::tRectangle:
		bResult = CollideWithRectangle(other);
		break;
	default:
		break;
	}
	m_hitboxClr = (bResult ? LRgb::Red : LRgb::White);
	return bResult;
}

bool LCollideObject::CollideWithCircle(const LCollideObject& other) const
{
	LAssert(EntityData::tCircle == other.m_entity.type);
	
	Radian rad = m_phyData.radian + Radian90;
	Radian radOther = other.m_phyData.radian + Radian90;
	switch (m_entity.type)
	{
	case EntityData::tCircle:
	{
		Vector2 vSelf2Other = other.position() - position();
		float radiusSum = other.radius + radius;

		if (vSelf2Other.manhattanLength() >= radiusSum + center.manhattanLength() + other.center.manhattanLength())
			return false;

		if (!center.isNull())
			vSelf2Other -= center.rotated(rad);
		if (!other.center.isNull())
			vSelf2Other += other.center.rotated(radOther);

		return (vSelf2Other.lengthSquared() < radiusSum * radiusSum);
	}
	case EntityData::tRectangle:
	{
		Vector2 vSelf2Other = other.position() - position();
		float radiusSum = m_entity.halfWidth + m_entity.halfHeight + other.radius;

		if (vSelf2Other.manhattanLength() >= radiusSum + center.manhattanLength() + other.center.manhattanLength())
			return false;

		if (!other.center.isNull())
			vSelf2Other += other.center.rotated(radOther);

		vSelf2Other.rotate(-rad);
		vSelf2Other -= center;
		vSelf2Other.abs();

		float r = other.radius;
		if (vSelf2Other.x() > m_entity.halfWidth + r) return false;
		if (vSelf2Other.y() > m_entity.halfHeight + r) return false;

		Vector2 newVect = vSelf2Other - Vector2(m_entity.halfWidth, m_entity.halfHeight);
		if (newVect.x() > 0 &&
			newVect.y() > 0 &&
			newVect.lengthSquared() > r * r)
		{
			return false;
		}
		return true;
	}
	default:
		return false;
	}
}

bool LCollideObject::CollideWithRectangle(const LCollideObject& other) const
{
	LAssert(EntityData::tRectangle == other.m_entity.type);
	switch (m_entity.type)
	{
	case _InnerEntityData::tCircle:
		return other.CollideWithCircle(*this);
	default:
		LAssert(!"Not Impl");
		return false;
	}
}

#undef center
#undef radius

// bool ElipseEntity::isCollideWithPlayer(const Vector2 &self, Radian rad) const
// {
// 	Player* pPlayer = StgEngine::engine()->GetActivePlayer();
// 	const CircleEntity& playEntity = (const CircleEntity&)pPlayer->entity();
// 
// 	const float &r = playEntity.radius();
// 	Vector2 Vba = pPlayer->position() - self;
// 	if (Vba.manhattanLength() > rx() + ry() + 2 * r + center.manhattanLength())
// 		return false;
// 
// 	Vba.rotate(rad + Radian90);
// 	Vba -= center;
// 
// 	float ar = rx() + r;
// 	float br = ry() + r;
// 	ar *= ar;
// 	br *= ar;
// 
// 	if (Vba.x() * Vba.x() * br + Vba.y() * Vba.y() * ar > ar*br)// (x0/(a+r))^2 + (y0/(b+r))^2 > 1
// 		return false;
// 
// 	return true;
// }
