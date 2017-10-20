#include "stdafx.h"
#include "LEnemyLayer.h"
#include "stage/LStage.h"
#include "enemy/LEnemys.h"

LEnemyLayer::LEnemyLayer()
{
}


LEnemyLayer::~LEnemyLayer()
{
}

void LEnemyLayer::draw(LPainter& painter)
{
	LEnemys* pEnemys = global::stage()->enemys();
	LRenderLayer::autoDraw(painter, pEnemys->begin(), pEnemys->end());
}
