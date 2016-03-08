#pragma once
#include "LUIObjBase.h"
#include "LHandle.h"
#include "LUITransfer.h"

class LUIImage : public LUIObjBase
{
public:
	LUIImage(LGraphHandle hGraph);
	~LUIImage() override = default;

public:
	virtual uint GetSortKey() const override;
	virtual void Update() override;
	virtual void Draw(LPainter&) override;

public:
	void setFlash(uint interval);
	int width() const { return m_rect.width(); }
	int height() const { return m_rect.height(); }

protected:
	LGraphHandle m_hGraph;
	LUITransfer m_anime;
};
