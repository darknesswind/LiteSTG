#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#pragma once
// Ö÷²Ëµ¥
class GameMenu : public IComponent
{
public:
	GameMenu(void);
	~GameMenu(void);
	virtual void Draw(LPainter& painter);
	virtual void Update();

private:
	// 	void *MenuClass;
	bool m_canMove;
	int m_menuSelect;
	int m_timeCount;
	LGraphHandle m_title;
	const LGraphHandles* m_pSelections;
	LInput* m_pInput;
};
#endif