#include "stdafx.h"
#include "LControlledWalker.h"
#include "Input.h"

enum DirectionFlag
{
	Stop			= 0,					// 0
	MoveUp			= 0x0001,				// 1
	MoveDown		= 0x0010,				// 2
	MoveLeft		= 0x0100,				// 4
	MoveRight		= 0x1000,				// 8
	StopUDC			= MoveUp | MoveDown,	// 0x0011 3
	MoveLeftUp		= MoveLeft | MoveUp,	// 0x0101 5
	MoveLeftDown	= MoveLeft | MoveDown,	// 0x0110 6
	MoveLeftUDC		= MoveLeft | StopUDC,	// 0x0111 7
	MoveRightUp		= MoveRight | MoveUp,	// 0x1001 9
	MoveRightDown	= MoveRight | MoveDown,	// 0x1010 10
	MoveRightUDC	= MoveRight | StopUDC,	// 0x1011 11
	StopLRC			= MoveLeft | MoveRight,	// 0x1100 12
	MoveUpLRC		= MoveUp | StopLRC,		// 0x1101 13
	MoveDownLRC		= MoveDown | StopLRC,	// 0x1110 14
	StopAll			= StopLRC | StopUDC,	// 0x1111 15
};

LControlledWalker::LControlledWalker()
	: m_speeds{ 3.5 ,2 }
{
	m_pInput = LEngine::input();
	m_speeds[sDiagNormal] = L_SQRT1_2 * m_speeds[sNormal];
	m_speeds[sDiagFocus] = L_SQRT1_2 * m_speeds[sFocus];
}

void LControlledWalker::setSpeed(float fNormal, float fFocus)
{
	m_speeds[sNormal] = fNormal;
	m_speeds[sFocus] = fFocus;
	m_speeds[sDiagNormal] = L_SQRT1_2 * fNormal;
	m_speeds[sDiagFocus] = L_SQRT1_2 * fFocus;
}

void LControlledWalker::nextStep(PhysicData& data)
{
	int movetype = Stop;
	int detlaIdx = m_pInput->isLogicKeyDown(StgKey::Slow) ? sFocus : sNormal;
	float speed = m_speeds[detlaIdx];
	float diagSpeed = m_speeds[detlaIdx | sDiagFlag];

	if (m_pInput->isLogicKeyDown(StgKey::Up))	movetype |= MoveUp;
	if (m_pInput->isLogicKeyDown(StgKey::Down))	movetype |= MoveDown;
	if (m_pInput->isLogicKeyDown(StgKey::Left))	movetype |= MoveLeft;
	if (m_pInput->isLogicKeyDown(StgKey::Right))	movetype |= MoveRight;

	switch (movetype)
	{
	case MoveUp:
	case MoveUpLRC:
		data.position.ry() -= speed;
		break;
	case MoveDown:
	case MoveDownLRC:
		data.position.ry() += speed;
		break;
	case MoveLeft:
	case MoveLeftUDC:
		data.position.rx() -= speed;
		break;
	case MoveRight:
	case MoveRightUDC:
		data.position.rx() += speed;
		break;
	case MoveLeftUp:
		data.position.rx() -= diagSpeed;
		data.position.ry() -= diagSpeed;
		break;
	case MoveRightUp:
		data.position.rx() += diagSpeed;
		data.position.ry() -= diagSpeed;
		break;
	case MoveLeftDown:
		data.position.rx() -= diagSpeed;
		data.position.ry() += diagSpeed;
		break;
	case MoveRightDown:
		data.position.rx() += diagSpeed;
		data.position.ry() += diagSpeed;
		break;
	default:
		break;
	}
}
