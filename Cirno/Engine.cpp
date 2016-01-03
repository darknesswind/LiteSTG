#include "stdafx.h"
#include "Engine.h"

#include "Globle.h"

#include "ui/loading/LoadingUI.h"
#include "ui/menu/GameMenu.h"
#include "ui/stage/baseFrame.h"
#include "Manager/ComManage.h"

// DEBUG
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#include "Factory/ShooterFactory.h"
#include "DebugInfo.h"
DebugInfo debugInfo;
// _DEBUG

Engine::Engine()
	: LStgEngine()
{

}

Engine::~Engine()
{
}

void Engine::BeforeDxInit()
{
	Base::BeforeDxInit();
}

void Engine::PreLoad()
{
	Base::PreLoad();
	m_spRootUI->addChild(new LoadingUI(nullptr, true));
}

void Engine::OnLoading()
{
	Base::OnLoading();

	m_spGameMenu = std::make_unique<GameMenu>();
	m_spComManage->push_back(m_spGameMenu.get());
}

void Engine::Update()
{
	Base::Update();

	debugInfo.Update();

	if (isStateChange)
		checkState();
}

void Engine::Draw()
{
	Base::Draw();
	debugInfo.Draw(LStgEngine::render()->GetPainter());
}

void Engine::checkState()
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
			pEnemy->position().reset(100 + 20 * i, 100);
			ShooterFactory::createNWaysFlower(pEnemy);
		}
		break;
	}

	isStateChange = false;
}
