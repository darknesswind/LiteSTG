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
	: m_normalSpeed(3.5)
	, m_focusSpeed(2)
{
}

void LControlledWalker::setSpeed(float fNormal, float fFocus)
{
	m_normalSpeed = fNormal;
	m_focusSpeed = fFocus;
}

void LControlledWalker::nextStep(PhysicData& data)
{
	int movetype = Stop;
	float detla = Input.isKeyDown(Keys::LShift) ? m_focusSpeed : m_normalSpeed;

	if (Input.isKeyDown(Keys::Up))		movetype |= MoveUp;
	if (Input.isKeyDown(Keys::Down))	movetype |= MoveDown;
	if (Input.isKeyDown(Keys::Left))	movetype |= MoveLeft;
	if (Input.isKeyDown(Keys::Right))	movetype |= MoveRight;

	switch (movetype)
	{
	case MoveUp:
	case MoveUpLRC:
		data.position.ry() -= detla;
		break;
	case MoveDown:
	case MoveDownLRC:
		data.position.ry() += detla;
		break;
	case MoveLeft:
	case MoveLeftUDC:
		data.position.rx() -= detla;
		break;
	case MoveRight:
	case MoveRightUDC:
		data.position.rx() += detla;
		break;
	case MoveLeftUp:
		data.position.rx() -= L_SQRT1_2 * detla;
		data.position.ry() -= L_SQRT1_2 * detla;
		break;
	case MoveRightUp:
		data.position.rx() += L_SQRT1_2 * detla;
		data.position.ry() -= L_SQRT1_2 * detla;
		break;
	case MoveLeftDown:
		data.position.rx() -= L_SQRT1_2 * detla;
		data.position.ry() += L_SQRT1_2 * detla;
		break;
	case MoveRightDown:
		data.position.rx() += L_SQRT1_2 * detla;
		data.position.ry() += L_SQRT1_2 * detla;
		break;
	default:
		break;
	}
}
