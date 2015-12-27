#include "stdafx.h"
#include "LWindow.h"
#include "LScreen.h"
#include "LPainter.h"
#include "Input.h"

#include "ui/menu/GameMenu.h"
#include "ui/stage/baseFrame.h"

#include "bullet/LBullets.h"
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#include "Manager/ComManage.h"

// DEBUG
#include "enemy/LEnemy.h"
#include "Factory/ShooterFactory.h"
#include "DebugInfo.h"
DebugInfo debugInfo;
// _DEBUG


LStgEngine::LStgEngine(void)
	: LEngine()
{
}

LStgEngine::~LStgEngine(void)
{
}

void LStgEngine::BeforeDxInit()
{
	Base::BeforeDxInit();

	AppWindow.setIsWindowMode(true);
	Screen.setGraphMode(640, 480, 32);
	Screen.setWaitVSync(false);
	AppWindow.setRunWhenDeactivate(true);
}

void LStgEngine::AfterDxInit()
{
	Base::AfterDxInit();

	m_pathSet.load(L".\\resource\\data\\PathSet.xml");
	Resource::loadPrimaryGameResource();
	Resource::loadPlayerResource(NS_Resource::Reimu);

	m_spBullets = std::make_unique<LBullets>();
	m_spPlayers = std::make_unique<LPlayers>();
	m_spEnemys = std::make_unique<LEnemys>();

	m_spComManage = std::make_unique<ComManager>();

	m_spGameMenu = std::make_unique<GameMenu>();

	m_bDebugPause = false;

	m_spComManage->push_back(m_spGameMenu.get());
}

bool LStgEngine::LoopCheck()
{
	if (!Base::LoopCheck())
		return false;

	if (!Input.update())
		return false;

	return true;
}

void LStgEngine::Update()
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

void LStgEngine::Draw()
{
	m_spEnemys->CommitRender();
	m_spBullets->CommitRender();
	m_spPlayers->CommitRender();
	m_spComManage->Draw();

	debugInfo.Draw(LStgEngine::render()->GetPainter());
}

void LStgEngine::checkState()
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

void LStgEngine::BeforeEnd()
{
	m_spEnemys->Clear();
	m_spPlayers->Clear();
	m_spBullets->Clear();

	Base::BeforeEnd();
}

Player* LStgEngine::GetActivePlayer()
{
	return m_spPlayers->GetActiveItem();
}
