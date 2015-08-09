#include "stdafx.h"
#include "LRayShooter.h"
#include "Globle.h"
#include "painting/LPainter.h"
#include "player/player.h"
#include "bullet/LBullets.h"
#include "Bullet/RayLaser.h"
#include "Engine.h"

LRayShooter::LRayShooter(IGameObject* pParent)
	: LShooter(pParent)
{	
	m_warningTime = 60;	// 预警时间
	m_durationTime = 60;// 持续时间
	m_widthExt = 1;		// 宽度
	m_lengthExt = 70;
	m_counter = 0;
	m_bTurnFlag = false;
	bulletStyle().color = 1;
	bulletStyle().type = BulletClass::激光;
	m_warningLine.InitFromPolar(600, m_fireDegree);
	ChangeState(Warning);
}

LRayShooter::~LRayShooter(void)
{
}

void LRayShooter::Update()
{
	m_spWalker->nextStep(m_phyData);
	switch (m_currState)
	{
	case LRayShooter::Warning:
		ExecWarning();
		break;
	case LRayShooter::Shooting:
		ExecShooting();
		break;
	default:
		break;
	}
}

void LRayShooter::Draw( LPainter& painter )
{
	switch (m_currState)
	{
	case LRayShooter::None:
		break;
	case LRayShooter::Warning:
		// 	DrawExtRotaGraph(Pos(), 0.1f, 70, (lineDir).direction() + L_PID2, Resource::bullet(bulletType, bulletColor));
		painter.drawLine(position(), position() + m_warningLine, LRgb::White);
		break;
	case LRayShooter::Shooting:
		break;
	default:
		break;
	}
}

void LRayShooter::ChangeState(State targetState)
{
	m_currState = targetState;
	switch (targetState)
	{
	case LRayShooter::Warning:
		EntryWarningState();
		break;
	case LRayShooter::Shooting:
		EntryShootingState();
		break;
	default:
		break;
	}
}

void LRayShooter::EntryShootingState()
{
	m_counter = m_durationTime;

	Degree angle = m_fireDegree - ((m_fireRange - m_angleIncrease) / 2);
	for (int i = 0; i < m_fireWays; ++i)
	{
		RayLaser* pLaser = StgEngine::bullets()->AddRayLaser(this);
		pLaser->SetLife(m_durationTime);
		pLaser->setPosition(position());
		pLaser->setStyle(bulletStyle());
		pLaser->setSpeed(0, angle);

		pLaser->setWidthExtRange(m_widthExt);
		pLaser->setLengthExtRange(m_lengthExt);
		pLaser->setTurnFlag(m_bTurnFlag);
		for each(auto x in bulletFunc)
		{
			pLaser->setAdvBulletFunc(x.funcType, x.startTime);
		}
		angle += m_angleIncrease;
	}
}

void LRayShooter::EntryWarningState()
{
	m_counter = m_warningTime;
}

void LRayShooter::ExecShooting()
{
	if (--m_counter == 0)
	{
		if (m_bLoop)
			ChangeState(Warning);
		else
			ChangeState(None);
	}
}

void LRayShooter::ExecWarning()
{
	if (m_bFollowPlayer)
	{
		Radian rad = position().radianBetween(StgEngine::engine()->GetActivePlayer()->position());
		m_warningLine.InitFromPolar(600, rad);
	}

	if (--m_counter == 0)
	{
		m_fireDegree = m_warningLine.degree();
		ChangeState(Shooting);
	}
}
