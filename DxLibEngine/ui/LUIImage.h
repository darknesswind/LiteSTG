#pragma once
#include "LUIObjBase.h"
#include "LHandle.h"

class LUIImage : public LUIObjBase
{
public:
	LUIImage(LGraphHandle hGraph, LUIObjBase* parent, bool bAutoDel = false);
	~LUIImage() override = default;

public:
	virtual uint GetSortKey() const override;
	virtual void Draw(LPainter&) override;

protected:
	LGraphHandle m_hGraph;
};

class LUIFlashImage : public LUIImage
{
public:
	LUIFlashImage(LGraphHandle hGraph, LUIObjBase* parent, bool bAutoDel = false);
	~LUIFlashImage() override = default;

public:
	virtual void Update() override;

public:
	void setFlash(uint interval);

private:
	const static int s_maxOpaque = 0xFF;

	Radian m_ratio;
	float m_step;
	uint m_interval;	// 一个周期的间隔
};
