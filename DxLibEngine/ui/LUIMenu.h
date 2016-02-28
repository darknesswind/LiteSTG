#pragma once
#include "LUIObjBase.h"

class LUIMenuItem;
class LUIMenu : public LUIObjBase
{
public:
	LUIMenu();
	~LUIMenu();

	LUIMenuItem* addMenuItem(LGraphHandle hActive, LGraphHandle hDeactive);

public:
	void Update() override;
	void Draw(LPainter& painter) override;

	virtual void OnOk() {}
	virtual void OnCancel() {}

protected:
	std::vector<LUIMenuItem*> m_items;
	bool m_bEnable;
	bool m_bCanMove;
	int m_activeIdx;
	int m_timeCount;
};

class LUIMenuItem
{
public:
	LUIMenuItem(LGraphHandle hActive, LGraphHandle hDeactive);
	virtual ~LUIMenuItem() {}

public:
	const LSize& size() { return m_size; }
	LGraphHandle activeImg() { return m_hActive; }
	LGraphHandle deactiveImg() { return m_hDeactive; }

protected:
	LGraphHandle m_hActive;
	LGraphHandle m_hDeactive;
	LSize m_size;
};
