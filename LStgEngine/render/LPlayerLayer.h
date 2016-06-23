#pragma once
#include "render\LRenderLayer.h"

class LPlayerLayer : public LRenderLayer
{
public:
	LPlayerLayer();
	~LPlayerLayer();

	void draw(LPainter& painter) override;
};

