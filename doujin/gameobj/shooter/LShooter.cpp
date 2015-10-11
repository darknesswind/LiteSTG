#include "stdafx.h"
#include "LShooter.h"
#include "Globle.h"
#include "Engine.h"
#include "move/LFollowWalker.h"
#include "player/player.h"
#include "bullet/LBullets.h"

LShooter::LShooter(IGameObject* pParent /*= nullptr*/)
	: LGameObject(pParent)
{
	baseInit();
}

void LShooter::baseInit()
{
	m_counter = 0;
	m_frequency = 16;
	m_fireWays = 1;
	m_fireRange.setDegree(360);
	m_angleSpeed.setDegree(0);
	m_angleAccel.setDegree(0);
	m_bFollowPlayer = false;
	m_angleIncrease = m_fireRange / m_fireWays;
	setFireSpeed(Vector2(0, 1));

	m_spWalker.reset(LWalker::CreateFollowWalker(m_pParent));

#if USE_FASTFUNC
	funcList[0] = timerFunc(this, &LShooter::Fun_test);
#endif
}

void LShooter::Update()
{
	m_spWalker->nextStep(m_phyData);
	if (++m_counter == m_frequency)
	{
		m_counter = 0;
		if (m_bFollowPlayer)
			m_fireDegree = position().degreeBetween(StgEngine::engine()->GetActivePlayer()->position());

		m_fireDegree += m_angleSpeed;
		m_angleSpeed += m_angleAccel;
		m_bulletData.position = position();

		Degree angle;
		angle = m_fireDegree - ((m_fireRange - m_angleIncrease) / 2);
		for (int i = 0; i < m_fireWays; ++i)
		{
			Bullet *pBullet = StgEngine::bullets()->AddGenericBullet(this);
			pBullet->setStyle(m_bulletStyle);
			pBullet->setData(m_bulletData);
			pBullet->setSpeed(m_bulletSpeed, angle);
			for each(auto j in bulletFunc)
			{
				pBullet->setAdvBulletFunc(j.funcType, j.startTime);
			}			
			angle += m_angleIncrease;
		}
	}
	mytimer.update();
}

void LShooter::Fun_test(int &_counter)
{
	m_fireWays %= 10;
	setFireWays(m_fireWays + 1);
	_counter = m_frequency;
}

void LShooter::setFireSpeed(Vector2 speed)
{
	m_bulletData.speed = speed;
	m_bulletSpeed = speed.length();
	m_fireDegree = speed.degree();
}

void LShooter::setBulletData(const PhysicData& bulletData)
{
	m_bulletData = bulletData;
	setFireSpeed(bulletData.speed);
}
