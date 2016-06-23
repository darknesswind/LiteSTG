#include "stdafx.h"
#include "LEnemyLayer.h"
#include "enemy/LEnemys.h"

LEnemyLayer::LEnemyLayer()
{
}


LEnemyLayer::~LEnemyLayer()
{
}

void LEnemyLayer::draw(LPainter& painter)
{
	LEnemys* pEnemys = LStgEngine::enemys();
	LRenderLayer::autoDraw(painter, pEnemys->begin(), pEnemys->end());
}
