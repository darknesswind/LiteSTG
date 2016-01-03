#include "stdafx.h"
#include "GameMenu.h"
#include "Globle.h"
#include "Input.h"
#include "LPainter.h"
#include "LAssets.h"

enum
{
	MENU_GAME_START,
	MENU_EXTRA_START,
	MENU_PRACTICE_START,
	MENU_SPELL_PRACTICE,
	MENU_REPLAY,
	MENU_PLAYER_DATA,
	MENU_MUSIC_ROOM,
	MENU_OPTION,
	MENU_QUIT,
	MENU_SELECT_NUM
};

GameMenu::GameMenu(void)
	: m_pSelections(nullptr)
{
	m_pInput = LEngine::input();
	m_menuSelect = 0;
	m_timeCount = 0;
	m_title = LEngine::assets()->GetTexture(_T("select00"));
	m_pSelections = &LEngine::assets()->GetSubGraphGroup(_T("标题选项"));
	// 	MenuClass = NULL;
}

GameMenu::~GameMenu(void)
{
}

void GameMenu::Draw(LPainter& painter)
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
	if (m_pInput->isLogicKeyDown(StgKey::Ok))
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
	if (m_pInput->isLogicKeyDown(StgKey::Cancel))
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
	if (m_pInput->isLogicKeyDown(StgKey::Down) || m_pInput->isLogicKeyDown(StgKey::Up))
	{
		m_menuSelect = (m_menuSelect + m_pInput->isLogicKeyDown(StgKey::Down)) % MENU_SELECT_NUM;
		m_menuSelect = (m_menuSelect + m_pInput->isLogicKeyDown(StgKey::Up) * (MENU_SELECT_NUM - 1)) % MENU_SELECT_NUM;
		m_canMove = false;
	}
	return;
}