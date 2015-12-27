#include "stdafx.h"
#include "baseFrame.h"
#include "resource.h"
#include "LPainter.h"
#include "LAssets.h"

BaseFrame::BaseFrame()
{
	LAssets* pAssets = StgEngine::assets();
	m_leftFrame		= pAssets->GetTexture(_T("bg_left"));
	m_topFrame		= pAssets->GetTexture(_T("bg_top"));
	m_rightFrame	= pAssets->GetTexture(_T("bg_right"));
	m_bottomFrame	= pAssets->GetTexture(_T("bg_bottom"));
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