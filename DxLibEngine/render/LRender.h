#ifndef __LRENDER_H__
#define __LRENDER_H__
#pragma once
#include "LPainter.h"
#include "base/LHandle.h"

class LRenderLayer;
class LRender
{
public:
	LRender(void);
	~LRender();

public:
	void DoRender();
	// void PushItem(IDrawableObj* pItem);
	LPainter& GetPainter() { return m_painter; }

	LRenderLayer* addLayer(uint key, std::unique_ptr<LRenderLayer> layer);

private:
	LRender(const LRender& other) = delete;
	void operator=(const LRender& other) = delete;

private:
	std::map<uint, std::unique_ptr<LRenderLayer>> m_layers;

// 	typedef std::vector<IDrawableObj*> RenderItems;
// 	typedef std::map<RenderArgument, RenderItems> RenderQueue;
// 
// 	RenderQueue m_renderQueue;
	LPainter m_painter;
};

#endif // !__LRENDER_H__