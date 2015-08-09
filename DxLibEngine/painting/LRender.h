#ifndef __LRENDER_H__
#define __LRENDER_H__
#pragma once
#include "LPainter.h"
#include "LHandle.h"
#include <unordered_map>

// #define __RenderQueueTest__

class LRender
{
public:
	LRender(void);
	~LRender();

public:
	void DoRender();
	void PushItem(IDrawableObj* pItem);
	LPainter& GetPainter() { return m_painter; }

private:
	LRender(const LRender& other) = delete;
	void operator=(const LRender& other) = delete;

private:
	typedef std::vector<IDrawableObj*> RenderItems;
	typedef std::map<LGraphHandle, RenderItems> RenderImages;
	typedef std::map<RenderArgument, RenderImages> RenderQueue;

	typedef std::unordered_map<int, RenderItems> RenderImages2;
	typedef std::map<uint, RenderImages2> RenderQueue2;
#ifndef __RenderQueueTest__
	RenderQueue m_renderQueue;
#else
	RenderQueue2 m_renderQueue;
#endif

	LPainter m_painter;
};

#endif // !__LRENDER_H__