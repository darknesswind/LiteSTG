#include "stdafx.h"
#include "LSegShooter.h"

#include "Globle.h"
#include "Bullet/SegmentLaser.h"

#include "player/player.h"
#include "Factory/EntityFactory.h"
#include "Engine.h"

void LSegShooter::Update()
{
	m_spWalker->nextStep(m_phyData);
	if (++m_counter == m_frequency)
	{		
		m_counter = 0;
		if (m_bFollowPlayer)
			m_fireDegree = position().degreeBetween(Engine.GetActivePlayer()->position());
		m_fireDegree += m_angleSpeed;
		m_angleSpeed += m_angleAccel;

		Degree angle = m_fireDegree - ((m_fireRange - m_angleIncrease) / 2);
		for (int i=0; i<m_fireWays; ++i)
		{
			Bullet *pNewBullet = Engine.GetBullets()->AddSegmentLaser(this);
			pNewBullet->setPosition(position());
			pNewBullet->setData(m_bulletData);
			pNewBullet->setSpeed(m_bulletSpeed, angle);
			for each(auto j in bulletFunc)
			{
				pNewBullet->setAdvBulletFunc(j.funcType, j.startTime);
			}			
			angle += m_angleIncrease;
		}		
	}
	mytimer.update();
}
