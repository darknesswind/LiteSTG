#include "stdafx.h"
#include "LRender.h"
#include "LRenderLayer.h"

LRender::LRender(void)
{

}

LRender::~LRender()
{
	m_layers.clear();
}

void LRender::DoRender()
{
	for (auto iter = m_layers.begin(); iter != m_layers.end(); ++iter)
	{
		m_painter.save();
		iter->second->draw(m_painter);
		m_painter.restore();
	}
/*
	for (RenderQueue::iterator iterChannel = m_renderQueue.begin();
		iterChannel != m_renderQueue.end(); ++iterChannel)
	{
		m_painter.save();
		m_painter.setPaintArgument(iterChannel->first.paintArg);


		RenderItems& items = iterChannel->second;
		for (RenderItems::iterator iterItem = items.begin();
		iterItem != items.end(); ++iterItem)
		{
			(*iterItem)->Draw(m_painter);
		}
		m_painter.restore();
	}

	DebugPat.Draw();
	m_renderQueue.clear();
*/
}

LRenderLayer* LRender::addLayer(uint key, std::unique_ptr<LRenderLayer> layer)
{
	LAssert(m_layers.find(key) == m_layers.end());
	LRenderLayer* pLayer = layer.get();
	m_layers[key].swap(layer);
	return pLayer;
}
