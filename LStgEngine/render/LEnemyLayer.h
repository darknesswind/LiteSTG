#pragma once
#include "render/LRenderLayer.h"

class LEnemyLayer : public LRenderLayer
{
public:
	LEnemyLayer();
	~LEnemyLayer();

	void draw(LPainter& painter) override;
};

