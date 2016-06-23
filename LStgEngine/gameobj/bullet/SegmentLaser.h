#pragma once
#include "bullet.h"

class SegmentLaser : public Bullet
{
public:
	SegmentLaser(IGameObject* pParent)
		: Bullet(pParent)
	{
		m_curScale = 0;
		m_maxScale = 10;
		m_originHalfHeight = m_entity.halfHeight;
	}
	virtual ~SegmentLaser() override {}
	virtual void Update() override;
	virtual void draw(LPainter& painter) override;
	virtual BulletType GetType() const override { return BulletType::SegmentLaser; }

	SegmentLaser& setLength(float length);

private:
	float m_curScale;
	float m_maxScale;
	float m_originHalfHeight;
};

