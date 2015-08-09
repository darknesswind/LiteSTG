#pragma once
#include "bullet.h"
#include "CollideEntity/RectEntity.h"
#include "Factory/EnemyFactory.h"
class SegmentLaser :
	public Bullet
{
public:
	SegmentLaser(IGameObject* pParent)
		: Bullet(pParent)
	{
		m_curScale = 0;
		m_maxScale = 10;
		m_pOriginEntity = EntityFactory::getLaserEntity(0);
		m_pMutableEntity = new RectEntity(*m_pOriginEntity);
		m_pEntity = m_pMutableEntity;
	}
	virtual ~SegmentLaser(){delete m_pMutableEntity;}
	virtual void Update();
	virtual void Draw(LPainter& painter);
	virtual BulletType GetType() const { return BulletType::SegmentLaser; }

	SegmentLaser& setLength(float length);

private:
	float m_curScale;
	float m_maxScale;
	RectEntity *m_pMutableEntity;
	const RectEntity *m_pOriginEntity;
};

