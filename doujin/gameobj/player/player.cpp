#include "stdafx.h"
#include "Player.h"
#include "Factory/EntityFactory.h"
#include "move/LWalker.h"
#include "LHandle.h"

Player::Player(int x, int y)
	: LGameObject()
{
	m_phyData.position.Init(x, y);
	m_spWalker = LWalker::CreateStableWalker();
	m_entity = EntityFactory::getPlayerEntity(0);
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
