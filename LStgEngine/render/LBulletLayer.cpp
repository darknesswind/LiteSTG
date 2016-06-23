#include "stdafx.h"
#include "LBulletLayer.h"
#include "bullet/LBullets.h"

LBulletLayer::LBulletLayer()
{
}


LBulletLayer::~LBulletLayer()
{
}

void LBulletLayer::draw(LPainter& painter)
{
	LBullets* pBullets = LStgEngine::bullets();
	LRenderLayer::autoDraw(painter, pBullets->begin(), pBullets->end());
}
