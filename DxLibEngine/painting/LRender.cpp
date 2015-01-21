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
#ifndef __RenderQueueTest__
	for (RenderQueue::iterator iterChannel = m_renderQueue.begin();
		iterChannel != m_renderQueue.end(); ++iterChannel)
	{
		Painter.save();
		Painter.setPaintArgument(iterChannel->first.paintArg);

		RenderImages& imgs = iterChannel->second;
		for (RenderImages::iterator iterImg = imgs.begin();
			iterImg != imgs.end(); ++iterImg)
		{
			RenderItems& items = iterImg->second;
			for (RenderItems::iterator iterItem = items.begin();
				iterItem != items.end(); ++iterItem)
			{
				(*iterItem)->Draw();
			}
		}
		Painter.restore();
	}
#else
	for (RenderQueue2::iterator iterChannel = m_renderQueue.begin();
		iterChannel != m_renderQueue.end(); ++iterChannel)
	{

		RenderImages2& imgs = iterChannel->second;
		for (RenderImages2::iterator iterImg = imgs.begin();
			iterImg != imgs.end(); ++iterImg)
		{
			RenderItems& items = iterImg->second;
			for (RenderItems::iterator iterItem = items.begin();
				iterItem != items.end(); ++iterItem)
			{
				Painter.save();
				Painter.setPaintArgument((*iterItem)->GetRenderArgument().paintArg);

				(*iterItem)->Draw();

				Painter.restore();

			}
		}
	}
#endif
	DebugPat.Draw();
	m_renderQueue.clear();
}

void LRender::PushItem(IDrawableObj* pItem)
{
	const RenderArgument& arg = pItem->GetRenderArgument();
	const LGraphHandle hHandle = pItem->GetGraphHandle();
#ifndef __RenderQueueTest__
	m_renderQueue[arg][hHandle].push_back(pItem);
#else
	m_renderQueue[arg.uDepth][hHandle].push_back(pItem);
#endif
}
