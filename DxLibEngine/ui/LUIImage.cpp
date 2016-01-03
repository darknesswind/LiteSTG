#include "stdafx.h"
#include "LUIImage.h"

LUIImage::LUIImage(LGraphHandle hGraph, LUIObjBase* parent, bool bAutoDel /*= false*/)
	: LUIObjBase(parent, bAutoDel)
	, m_hGraph(hGraph)
{
	m_hGraph.getSize(&m_rect.rwidth(), &m_rect.rheight());
}

uint LUIImage::GetSortKey() const
{
	return m_hGraph;
}

void LUIImage::Draw(LPainter& painter)
{
	painter.drawGraph(m_rect.pos(), m_hGraph, true);
}

//////////////////////////////////////////////////////////////////////////
LUIFlashImage::LUIFlashImage(LGraphHandle hGraph, LUIObjBase* parent, bool bAutoDel /*= false*/)
	: LUIImage(hGraph, parent, bAutoDel)
	, m_interval(0)
	, m_step(0)
{

}

void LUIFlashImage::Update()
{
	if (m_interval)
	{
		m_ratio += m_step;
		m_renderArg.paintArg.blendParam = s_maxOpaque * (1 + m_ratio.cos()) / 2;
	}
}

void LUIFlashImage::setFlash(uint interval)
{
	m_interval = interval;
	if (m_interval)
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::Alpha;
		m_renderArg.paintArg.blendParam = s_maxOpaque;

		m_step = L_PI2 / m_interval;
	}
	else
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::NoBlend;
		m_renderArg.paintArg.blendParam = 0;
	}
}
