#pragma once
#include "LRenderLayer.h"
class LUILayer : public LRenderLayer
{
public:
	LUILayer();
	~LUILayer();

	void draw(LPainter& painter) override;
};

