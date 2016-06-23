#pragma once
#include "render/LRenderLayer.h"

class LBulletLayer : public LRenderLayer
{
public:
	LBulletLayer();
	~LBulletLayer() override;

	virtual void draw(LPainter& painter) override;
};

