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

	Radian rad = m_phyData.radian + Radian90;
	switch (m_entity.type)
	{
	case EntityData::tCircle:
	{
		DebugPat.AddCircle(position().x(), position().y(), radius, m_hitboxClr);
		break;
	}
	case EntityData::tRectangle:
	{
		float left = center.x() - m_entity.halfWidth;
		float top = center.y() - m_entity.halfHeight;
		float right = center.x() + m_entity.halfWidth;
		float bottom = center.y() + m_entity.halfHeight;

		Vector2 vLTop = position() + Vector2(left, top).rotate(rad);
		Vector2 vRTop = position() + Vector2(right, top).rotate(rad);
		Vector2 vRBottom = position() + Vector2(right, bottom).rotate(rad);
		Vector2 vLBottom = position() + Vector2(left, bottom).rotate(rad);
		DebugPat.AddQuadrangle(vLTop, vRTop, vRBottom, vLBottom, m_hitboxClr);
		break;
	}
	case EntityData::tOffsetCircle:
	{
		Vector2 target = position() + center.rotated(rad);
		DebugPat.AddCircle(target.x(), target.y(), radius, m_hitboxClr);
		break;
	}
	case EntityData::tOffsetRect:
	{
		float left = -m_entity.halfWidth;
		float top = -m_entity.halfHeight;
		float right = +m_entity.halfWidth;
		float bottom = +m_entity.halfHeight;

		Vector2 vLTop = position() + Vector2(left, top).rotate(rad);
		Vector2 vRTop = position() + Vector2(right, top).rotate(rad);
		Vector2 vRBottom = position() + Vector2(right, bottom).rotate(rad);
		Vector2 vLBottom = position() + Vector2(left, bottom).rotate(rad);
		DebugPat.AddQuadrangle(vLTop, vRTop, vRBottom, vLBottom, m_hitboxClr);
		break;
	}
	default:
		break;
	}
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
	case EntityData::tOffsetCircle:
		bResult = CollideWithOffsetCircle(other);
		break;
	case EntityData::tOffsetRect:
		bResult = CollideWithOffsetRectangle(other);
		break;
	default:
		break;
	}
	m_hitboxClr = (bResult ? LRgb::Red : LRgb::White);
	return bResult;
}

template <bool c_bThisOffset, bool c_bOtherOffset>
bool LCollideObject::CircleCollideWithCircle(const LCollideObject& other) const
{
	LAssert(EntityData::tCircle == m_entity.type);
	LAssert(EntityData::tCircle == other.m_entity.type);
	LAssert(((m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bThisOffset);
	LAssert(((other.m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bOtherOffset);

	Radian rad = m_phyData.radian + Radian90;
	Radian radOther = other.m_phyData.radian + Radian90;

	Vector2 vSelf2Other = other.position() - position();
	float radiusSum = other.radius + radius;

	float impossibleLen = radiusSum;
	if (c_bThisOffset)
		impossibleLen += center.manhattanLength();
	if (c_bOtherOffset)
		impossibleLen += other.center.manhattanLength();

	if (vSelf2Other.manhattanLength() >= impossibleLen)
		return false;

	if (c_bThisOffset && !center.isNull())
		vSelf2Other -= center.rotated(rad);
	if (c_bOtherOffset && !other.center.isNull())
		vSelf2Other += other.center.rotated(radOther);

	return (vSelf2Other.lengthSquared() < radiusSum * radiusSum);
}

template <bool c_bThisOffset, bool c_bOtherOffset>
bool LCollideObject::RectCollideWithCircle(const LCollideObject& other) const
{
	LAssert(EntityData::tRectangle == m_entity.type);
	LAssert(EntityData::tCircle == other.m_entity.type);
	LAssert(((m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bThisOffset);
	LAssert(((other.m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bOtherOffset);

	Radian rad = m_phyData.radian + Radian90;
	Radian radOther = other.m_phyData.radian + Radian90;

	Vector2 vSelf2Other = other.position() - position();
	float radiusSum = m_entity.halfWidth + m_entity.halfHeight + other.radius;

	if (vSelf2Other.manhattanLength() >= radiusSum)
		return false;

	if (c_bOtherOffset && !other.center.isNull())
		vSelf2Other += other.center.rotated(radOther);

	vSelf2Other.rotate(-rad);
	if (c_bThisOffset)
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

template <bool c_bThisOffset, bool c_bOtherOffset>
bool LCollideObject::RectCollideWithRect(const LCollideObject& other) const
{
	LAssert(EntityData::tRectangle == m_entity.type);
	LAssert(EntityData::tRectangle == other.m_entity.type);
	LAssert(((m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bThisOffset);
	LAssert(((other.m_entity.type & EntityData::OffsetMask) == EntityData::OffsetMask) == c_bOtherOffset);

	Radian rad = m_phyData.radian + Radian90;
	Radian radOther = other.m_phyData.radian + Radian90;

	LAssert(!"Not Impl");
	return false;
}

#undef center
#undef radius

bool LCollideObject::CollideWithCircle(const LCollideObject& other) const
{
	switch (m_entity.type)
	{
	case EntityData::tCircle:
		return CircleCollideWithCircle<false, false>(other);
	case EntityData::tRectangle:
		return RectCollideWithCircle<false, false>(other);
	case EntityData::tOffsetCircle:
		return CircleCollideWithCircle<true, false>(other);
	case EntityData::tOffsetRect:
		return RectCollideWithCircle<true, false>(other);
	default:
		LAssert(!"Not Impl");
		return false;
	}
}

bool LCollideObject::CollideWithRectangle(const LCollideObject& other) const
{
	switch (m_entity.type)
	{
	case EntityData::tCircle:
		return other.RectCollideWithCircle<false, false>(*this);
	case EntityData::tRectangle:
		return RectCollideWithRect<false, false>(other);
	case EntityData::tOffsetCircle:
		return other.RectCollideWithCircle<false, true>(*this);
	case EntityData::tOffsetRect:
		return RectCollideWithRect<true, false>(other);
	default:
		LAssert(!"Not Impl");
		return false;
	}
}

bool LCollideObject::CollideWithOffsetCircle(const LCollideObject& other) const
{
	switch (m_entity.type)
	{
	case EntityData::tCircle:
		return CircleCollideWithCircle<false, true>(other);
	case EntityData::tRectangle:
		return RectCollideWithCircle<false, true>(other);
	case EntityData::tOffsetCircle:
		return CircleCollideWithCircle<true, true>(other);
	case EntityData::tOffsetRect:
		return RectCollideWithCircle<true, true>(other);
	default:
		LAssert(!"Not Impl");
		return false;
	}
}

bool LCollideObject::CollideWithOffsetRectangle(const LCollideObject& other) const
{
	switch (m_entity.type)
	{
	case EntityData::tCircle:
		return other.RectCollideWithCircle<false, false>(*this);
	case EntityData::tRectangle:
		return RectCollideWithRect<false, true>(other);
	case EntityData::tOffsetCircle:
		return other.RectCollideWithCircle<false, true>(*this);
	case EntityData::tOffsetRect:
		return RectCollideWithRect<true, true>(other);
	default:
		LAssert(!"Not Impl");
		return false;
	}
}

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
