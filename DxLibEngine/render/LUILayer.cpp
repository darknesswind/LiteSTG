#include "stdafx.h"
#include "LUILayer.h"
#include "ui/LUIObjBase.h"

LUILayer::LUILayer()
{
}


LUILayer::~LUILayer()
{
}

void LUILayer::draw(LPainter& painter)
{
	LEngine::rootUI()->draw(painter);
}
