#include "stdafx.h"
#include "LSegShooter.h"

#include "bullet/LBullets.h"
#include "Bullet/SegmentLaser.h"

#include "player/player.h"

void LSegShooter::Update()
{
	m_spWalker->nextStep(m_phyData);
	if (++m_counter == m_frequency)
	{		
		m_counter = 0;
		if (m_bFollowPlayer)
			m_fireDegree = position().degreeBetween(LStgEngine::engine()->GetActivePlayer()->position());
		m_fireDegree += m_angleSpeed;
		m_angleSpeed += m_angleAccel;

		Degree angle = m_fireDegree - ((m_fireRange - m_angleIncrease) / 2);
		for (int i=0; i<m_fireWays; ++i)
		{
			Bullet *pNewBullet = LStgEngine::bullets()->AddSegmentLaser(this);
			pNewBullet->setPosition(position());
			pNewBullet->setData(m_bulletData);
			pNewBullet->setSpeed(m_bulletSpeed, angle);
			angle += m_angleIncrease;
		}		
	}
}
