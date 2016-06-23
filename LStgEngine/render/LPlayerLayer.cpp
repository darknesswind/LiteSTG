#include "stdafx.h"
#include "LPlayerLayer.h"
#include "player/LPlayers.h"

LPlayerLayer::LPlayerLayer()
{
}


LPlayerLayer::~LPlayerLayer()
{
}

void LPlayerLayer::draw(LPainter& painter)
{
	LPlayer* pPlayer = LStgEngine::engine()->getActivePlayer();
	if (pPlayer)
		pPlayer->draw(painter);
}
