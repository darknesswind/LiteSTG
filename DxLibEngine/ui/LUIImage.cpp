#include "stdafx.h"
#include "LUIImage.h"

LUIImage::LUIImage(LGraphHandle hGraph)
	: LUIObjBase(nullptr)
	, m_hGraph(hGraph)
{
	m_hGraph.getSize(&m_rect.rwidth(), &m_rect.rheight());
}

uint LUIImage::GetSortKey() const
{
	return m_hGraph;
}

void LUIImage::Update()
{
	LUIObjBase::Update();
	m_anime.Update();
}

void LUIImage::Draw(LPainter& painter)
{
	painter.drawGraph(m_rect.pos(), m_hGraph, true);
}

void LUIImage::setFlash(uint interval)
{
	if (interval)
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::Alpha;
		m_anime.AddChild(new LUICosineTransfer<int>(&m_renderArg.paintArg.blendParam, interval, 0xFF));
	}
	else
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::NoBlend;
		m_renderArg.paintArg.blendParam = 0;
	}
}
