#include "stdafx.h"
#include "LUIImage.h"

LUIImage::LUIImage(LGraphHandle hGraph)
	: LUIObjBase(nullptr)
	, m_hGraph(hGraph)
{
	m_hGraph.getSize(&m_rect.rwidth(), &m_rect.rheight());
}

void LUIImage::Update()
{
	LUIObjBase::Update();
	m_anime.update();
}

void LUIImage::draw(LPainter& painter)
{
	if (m_anime.size() > 0)
	{
		painter.save();
		painter.setPaintArgument(m_renderArg.paintArg);
		painter.drawGraph(m_rect.pos(), m_hGraph, true);
		painter.restore();
	}
	else
	{
		painter.drawGraph(m_rect.pos(), m_hGraph, true);
	}
}

void LUIImage::setFlash(uint interval)
{
	if (interval)
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::Alpha;
		m_anime.addChild(new LUICosineTransfer<int>(&m_renderArg.paintArg.blendParam, interval, 0xFF));
	}
	else
	{
		m_renderArg.paintArg.blendMode = DxBlendMode::NoBlend;
		m_renderArg.paintArg.blendParam = 0;
	}
}
