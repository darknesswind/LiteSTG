#include "stdafx.h"
#include "Player.h"
#include "move/LWalker.h"
#include "LHandle.h"

Player::Player(int x, int y)
	: LCollideObject()
{
	m_phyData.position.reset(x, y);
	m_spWalker = LWalker::CreateStableWalker();
	m_renderArg.uDepth = DepthBackground;
}

Player::~Player(void)
{
}

void Player::Update()
{
}

void Player::Draw( LPainter& painter )
{
}
