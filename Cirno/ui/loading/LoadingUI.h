#pragma once
#include "ui/LUIObjBase.h"

class LoadingUI : public LUIObjBase
{
public:
	LoadingUI(LUIObjBase* parent = nullptr);
	~LoadingUI();

public:
	virtual void Draw(LPainter& painter) override;

private:
	LGraphHandle m_snow;
};

