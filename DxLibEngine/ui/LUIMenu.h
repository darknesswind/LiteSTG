#pragma once
#include "LUIObjBase.h"

class LUIMenuItem;
class LUIMenu : public LUIObjBase
{
public:
	LUIMenu();
	~LUIMenu();

	LUIMenuItem* addMenuItem(LGraphHandle hActive, LGraphHandle hDeactive);

	int currentIndex() const { return m_activeIdx; }
	void setCurrentIndex(int idx);

public:
	void Update() override;
	void Draw(LPainter& painter) override;

	virtual void OnOk() {}
	virtual void OnCancel() {}
	virtual void OnIndexChanged(int prev, int cur) {}

protected:
	std::vector<LUIMenuItem*> m_items;
	bool m_bEnable;

private:
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
