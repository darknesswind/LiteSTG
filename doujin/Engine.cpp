#include "stdafx.h"
#include "Engine.h"
#include "DxLib.h"
// NewEngineinc
#include "LWindow.h"
#include "LScreen.h"
#include "LPainter.h"
// NewEngineinc

#include "Globle.h"
#include "Input.h"
#include "resource.h"
#include "ui/menu/GameMenu.h"
#include "ui/stage/baseFrame.h"
#include "bullet/LBullets.h"
#include "player/LPlayers.h"

#include "player/player.h"

#include "bullet/Bullet.h"
// DEBUG
#include "enemy/LEnemy.h"
#include "Factory/ShooterFactory.h"
#include "DebugInfo.h"
DebugInfo debugInfo;
// _DEBUG

BaseFrame baseFrame;
StgEngine StgEngine::Instance;

StgEngine::StgEngine(void)
	: pGameMenu(nullptr)
	, m_bDebugPause(false)
{
}

StgEngine::~StgEngine(void)
{
}

bool StgEngine::BeforeDxInit()
{
	Base::BeforeDxInit();

	AppWindow.setIsWindowMode(true);
	Screen.setGraphMode(640, 480, 32);
	Screen.setWaitVSync(false);
	AppWindow.setRunWhenDeactivate(true);
	return true;
}

bool StgEngine::AfterDxInit()
{
	Base::AfterDxInit();

	m_pathSet.load(L".\\resource\\data\\PathSet.xml");
	Resource::loadPrimaryGameResource();
	Resource::loadPlayerResource(NS_Resource::Reimu);

	m_spBullets.reset(new LBullets);
	m_spPlayers.reset(new LPlayers);
	m_spEnemys.reset(new LEnemys);

	m_spComManage.reset(new ComManager);

	pGameMenu = new GameMenu;

	m_bDebugPause = false;

	m_spComManage->push_back(pGameMenu);

	return true;
}

bool StgEngine::LoopCheck()
{
	return Base::LoopCheck() &&
		Input.update() &&
		!endflag;
}

bool StgEngine::MainLoop()
{
	//timeCount = GetNowCount();
#ifdef _DEBUG
	if (Input.isKeyPress(Keys::F9))
		m_bDebugPause = !m_bDebugPause;
	if (!m_bDebugPause || (Input.isKeyPress(Keys::F10) || Input.isKeyDown(Keys::F11)))
#endif
	{
		m_spEnemys->Update();
		m_spPlayers->Update();
		m_spBullets->Update();
		m_spComManage->Update();
		debugInfo.Update();
	}

	m_spEnemys->CommitRender();
	m_spBullets->CommitRender();
	m_spPlayers->CommitRender();
	m_spComManage->Draw();

	debugInfo.Draw();

	if (isStateChange) checkState();
	return true;
}

void StgEngine::checkState()
{
	switch (gameState)
	{
	case GAMESTATE_START:
		m_spComManage->clear();
		m_spComManage->push_back(&baseFrame);

		m_spPlayers->Add(PlayerType::Controlled);
		for (int i = 0; i < 1; ++i)
		{
			LEnemy* pEnemy = m_spEnemys->Add();
			pEnemy->position().Init(100 + 20 * i, 100);
			ShooterFactory::createNWaysFlower(pEnemy);
		}
		break;
	}

	isStateChange = false;
}

bool StgEngine::BeforeEnd()
{
	Base::BeforeEnd();

	m_spEnemys->Clear();
	m_spPlayers->Clear();
	m_spBullets->Clear();
	return true;
}

Player* StgEngine::GetActivePlayer()
{
	return m_spPlayers->GetActiveItem();
}
