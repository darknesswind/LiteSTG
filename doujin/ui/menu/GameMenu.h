#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#pragma once
#include "interfaceDef.h"
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
	bool canMove;
	int menuSelect;
	int timeCount;
};
#endif