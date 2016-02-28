#pragma once
#include "LUIObjBase.h"
#include "LHandle.h"
#include "LUIAnime.h"

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

protected:
	LGraphHandle m_hGraph;
	LUIAnimation m_anime;
};
