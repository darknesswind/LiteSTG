#include "stdafx.h"
#include "LShooter.h"
#include "move/LFollowWalker.h"
#include "player/LPlayer.h"
#include "bullet/LBullets.h"
#include "bullet/LBulletStyles.h"
#include "stage/LStage.h"

LShooter::LShooter(IGameObject* pParent /*= nullptr*/)
	: LGameObject(pParent)
	, m_pBulletStyle(nullptr)
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

	m_spWalker = LWalker::CreateFollowWalker(m_pParent);
	m_pBulletStyle = global::bulletStyles()->getDefaultStyle(BulletType::Generic);
	m_pBullets = global::stage()->bullets();
}

void LShooter::Update()
{
	m_spWalker->nextStep(m_phyData);
	if (++m_counter == m_frequency)
	{
		m_counter = 0;
		if (m_bFollowPlayer)
			m_fireDegree = position().degreeBetween(global::engine()->getActivePlayer()->position());

		m_fireDegree += m_angleSpeed;
		m_angleSpeed += m_angleAccel;
		m_bulletData.position = position();

		Degree angle;
		angle = m_fireDegree - ((m_fireRange - m_angleIncrease) / 2);
		for (int i = 0; i < m_fireWays; ++i)
		{
			Bullet *pBullet = m_pBullets->AddGenericBullet(this);
			pBullet->setStyle(m_pBulletStyle, 0);
			pBullet->setData(m_bulletData);
			pBullet->setSpeed(m_bulletSpeed, angle);

			angle += m_angleIncrease;
		}
	}
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
