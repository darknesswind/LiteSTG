#include "stdafx.h"
#include "baseFrame.h"
#include "Globle.h"
#include "resource.h"
#include "LPainter.h"
#include "LImage.h"

void BaseFrame::Update()
{

}

void BaseFrame::Draw()
{
	using namespace NS_Resource;
	Painter.drawGraph(0, 0, LImage(Resource::frameBG(BG_Left)), false);
	Painter.drawGraph(32, 0, LImage(Resource::frameBG(BG_Top)), false);
	Painter.drawGraph(416, 0, LImage(Resource::frameBG(BG_Right)), false);
	Painter.drawGraph(32, 464, LImage(Resource::frameBG(BG_Bottom)), false);
}