#include "stdafx.h"
#include "GameMenu.h"
#include "Globle.h"
#include "resource.h"
#include "Input.h"
#include "LPainter.h"
#include "LImage.h"

GameMenu::GameMenu(void)
{
	menuSelect = 0;
	timeCount = 0;
	
// 	MenuClass = NULL;
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::Draw( LPainter& painter )
{
	using namespace NS_Resource;

	painter.drawGraph(0, 0, LImage(Resource::title(Title_BG)), false);
	painter.drawBox(410, 50 + 32 * menuSelect, 602, 82 + 32 * menuSelect, 0xffff, true);
	for (int i = 0; i < MENU_SELECT_NUM; ++i)
	{
		painter.drawGraph(410, 50 + 32 * i, LImage(Resource::TitleSelection(i)), true);
	}	
}

void GameMenu::Update()
{	
	if (Input.isKeyDown(Keys::Z))
	{
		switch (menuSelect)
		{
		case MENU_GAME_START:
			gameState = 1;
			isStateChange = true;
			break;
		case MENU_QUIT:
			endflag = true;
			break;
		default: break;
		}
	}
	if (Input.isKeyDown(Keys::X))
	{
		menuSelect = MENU_SELECT_NUM - 1;
		canMove = false;
	}
	if (!canMove) // ËÙ¶È¿ØÖÆ
	{		
		if (timeCount++ > 8)
		{
			timeCount = 0;
			canMove = true;
		}
		return;
	}
	if (Input.isKeyDown(Keys::Down) || Input.isKeyDown(Keys::Up))
	{
		menuSelect = (menuSelect + Input.isKeyDown(Keys::Down)) % MENU_SELECT_NUM;
		menuSelect = (menuSelect + Input.isKeyDown(Keys::Up) * (MENU_SELECT_NUM - 1)) % MENU_SELECT_NUM;
		canMove = false;
	}		
	return;
}