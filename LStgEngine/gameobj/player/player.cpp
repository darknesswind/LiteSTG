#include "stdafx.h"
#include "Player.h"
#include "move/LWalker.h"
#include "LHandle.h"
#include "LPlayerModel.h"

Player::Player(int x, int y)
	: LCollideObject()
{
	m_phyData.position.reset(x, y);
	m_spWalker = LWalker::CreateStableWalker();
	m_renderArg.uDepth = DepthBackground;
	m_pModel = &LEmptyPlayerMocel::s_instance;
}

Player::~Player(void)
{
}

void Player::setModel(LPlayerModel* pModel)
{
	if (pModel)
		m_pModel = pModel;
}

void Player::Update()
{
}

void Player::Draw( LPainter& painter )
{
}
