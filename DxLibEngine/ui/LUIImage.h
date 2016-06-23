#pragma once
#include "LUIObjBase.h"
#include "base/LHandle.h"
#include "LUITransfer.h"

class LUIImage : public LUIObjBase
{
public:
	LUIImage(LGraphHandle hGraph);
	~LUIImage() override = default;

public:
	virtual void Update() override;
	virtual void draw(LPainter&) override;

public:
	void setFlash(uint interval);
	int width() const { return m_rect.width(); }
	int height() const { return m_rect.height(); }

protected:
	LGraphHandle m_hGraph;
	LUITransferSet m_anime;
};
