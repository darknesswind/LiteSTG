#include "stdafx.h"
#include "GameMenu.h"
#include "Globle.h"
#include "Input.h"
#include "LPainter.h"
#include "LImage.h"
#include "LAssets.h"

GameMenu::GameMenu(void)
	: m_pSelections(nullptr)
{
	m_menuSelect = 0;
	m_timeCount = 0;
	m_title = LEngine::assets()->GetTexture(_T("title"));
	m_pSelections = &LEngine::assets()->GetSubGraphGroup(_T("标题选项"));
// 	MenuClass = NULL;
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::Draw( LPainter& painter )
{
	painter.drawGraph(0, 0, m_title, false);
	painter.drawBox(410, 50 + 32 * m_menuSelect, 602, 82 + 32 * m_menuSelect, 0xffff, true);
	for (int i = 0; i < MENU_SELECT_NUM; ++i)
	{
		painter.drawGraph(410, 50 + 32 * i, m_pSelections->at(i), true);
	}	
}

void GameMenu::Update()
{	
	if (Input.isKeyDown(Keys::Z))
	{
		switch (m_menuSelect)
		{
		case MENU_GAME_START:
			gameState = 1;
			isStateChange = true;
			break;
		case MENU_QUIT:
			Engine::engine()->setEndFlag(true);
			break;
		default: break;
		}
	}
	if (Input.isKeyDown(Keys::X))
	{
		m_menuSelect = MENU_SELECT_NUM - 1;
		m_canMove = false;
	}
	if (!m_canMove) // 速度控制
	{		
		if (m_timeCount++ > 8)
		{
			m_timeCount = 0;
			m_canMove = true;
		}
		return;
	}
	if (Input.isKeyDown(Keys::Down) || Input.isKeyDown(Keys::Up))
	{
		m_menuSelect = (m_menuSelect + Input.isKeyDown(Keys::Down)) % MENU_SELECT_NUM;
		m_menuSelect = (m_menuSelect + Input.isKeyDown(Keys::Up) * (MENU_SELECT_NUM - 1)) % MENU_SELECT_NUM;
		m_canMove = false;
	}		
	return;
}