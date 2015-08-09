#include "stdafx.h"
#include "baseFrame.h"
#include "resource.h"
#include "LPainter.h"


BaseFrame::BaseFrame()
{
	using namespace NS_Resource;

	m_leftFrame = Resource::frameBG(BG_Left);
	m_topFrame = Resource::frameBG(BG_Top);
	m_rightFrame = Resource::frameBG(BG_Right);
	m_bottomFrame = Resource::frameBG(BG_Bottom);
}

void BaseFrame::Update()
{

}

void BaseFrame::Draw( LPainter& painter )
{
	painter.drawGraph(0, 0, m_leftFrame, false);
	painter.drawGraph(32, 0, m_topFrame, false);
	painter.drawGraph(416, 0, m_rightFrame, false);
	painter.drawGraph(32, 464, m_bottomFrame, false);
}