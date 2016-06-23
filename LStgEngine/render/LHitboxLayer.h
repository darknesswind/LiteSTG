#pragma once
#include "render\LRenderLayer.h"
class LHitboxLayer : public LRenderLayer
{
public:
	LHitboxLayer();
	~LHitboxLayer();

	void draw(LPainter& painter) override;
};

