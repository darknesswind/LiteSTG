#include "stdafx.h"
#include "LPlayer.h"
#include "move/LWalker.h"
#include "LHandle.h"
#include "LPlayerModel.h"

LPlayer::LPlayer(int x, int y)
	: LCollideObject()
{
	m_phyData.position.reset(x, y);
	m_spWalker = LWalker::CreateStableWalker();
	m_renderArg.uDepth = DepthBackground;
	m_pModel = &LEmptyPlayerMocel::s_instance;
}

LPlayer::~LPlayer(void)
{
}

void LPlayer::setModel(LPlayerModel* pModel)
{
	if (pModel)
		m_pModel = pModel;
}

void LPlayer::Update()
{
}

void LPlayer::draw( LPainter& painter )
{
}
