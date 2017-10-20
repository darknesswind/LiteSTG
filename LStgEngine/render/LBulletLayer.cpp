#include "stdafx.h"
#include "LBulletLayer.h"
#include "bullet/LBullets.h"
#include "stage/LStage.h"

LBulletLayer::LBulletLayer()
{
}


LBulletLayer::~LBulletLayer()
{
}

void LBulletLayer::draw(LPainter& painter)
{
	LBullets* pBullets = global::stage()->bullets();
	LRenderLayer::autoDraw(painter, pBullets->begin(), pBullets->end());
}
