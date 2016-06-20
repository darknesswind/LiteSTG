#include "stdafx.h"
#include "LRender.h"
#include "DxGraphics.h"

LRender::LRender(void)
{

}

LRender::~LRender()
{

}

void LRender::DoRender()
{
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
}

void LRender::PushItem(IDrawableObj* pItem)
{
	const RenderArgument& arg = pItem->GetRenderArgument();
	m_renderQueue[arg].push_back(pItem);
}
