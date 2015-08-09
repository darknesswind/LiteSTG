#include "stdafx.h"

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
#include "enemy/LEnemys.h"

// DEBUG
#include "enemy/LEnemy.h"
#include "Factory/ShooterFactory.h"
#include "DebugInfo.h"
DebugInfo debugInfo;
// _DEBUG


StgEngine::StgEngine(void)
	: LEngine()
{
}

StgEngine::~StgEngine(void)
{
}

void StgEngine::BeforeDxInit()
{
	Base::BeforeDxInit();

	AppWindow.setIsWindowMode(true);
	Screen.setGraphMode(640, 480, 32);
	Screen.setWaitVSync(false);
	AppWindow.setRunWhenDeactivate(true);
}

void StgEngine::AfterDxInit()
{
	Base::AfterDxInit();

	m_pathSet.load(L".\\resource\\data\\PathSet.xml");
	Resource::loadPrimaryGameResource();
	Resource::loadPlayerResource(NS_Resource::Reimu);

	m_spBullets.reset(new LBullets);
	m_spPlayers.reset(new LPlayers);
	m_spEnemys.reset(new LEnemys);

	m_spComManage.reset(new ComManager);

	m_spGameMenu.reset(new GameMenu);

	m_bDebugPause = false;

	m_spComManage->push_back(m_spGameMenu.get());
}

bool StgEngine::LoopCheck()
{
	if (!Base::LoopCheck())
		return false;

	if (!Input.update())
		return false;

	return !endflag;
}

void StgEngine::Update()
{
	//timeCount = GetNowCount();

	m_spEnemys->Update();
	m_spPlayers->Update();
	m_spBullets->Update();
	m_spComManage->Update();
	debugInfo.Update();

	if (isStateChange)
		checkState();
}

void StgEngine::Draw()
{
	m_spEnemys->CommitRender();
	m_spBullets->CommitRender();
	m_spPlayers->CommitRender();
	m_spComManage->Draw();

	debugInfo.Draw(StgEngine::render()->GetPainter());
}

void StgEngine::checkState()
{
	static 	BaseFrame baseFrame;
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

void StgEngine::BeforeEnd()
{
	m_spEnemys->Clear();
	m_spPlayers->Clear();
	m_spBullets->Clear();

	Base::BeforeEnd();
}

Player* StgEngine::GetActivePlayer()
{
	return m_spPlayers->GetActiveItem();
}
