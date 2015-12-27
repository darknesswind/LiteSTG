#include "stdafx.h"
#include "Engine.h"

#include "Globle.h"
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
{
}

Engine::~Engine()
{
}

void Engine::AfterDxInit()
{
	LStgEngine::AfterDxInit();

	m_spGameMenu = std::make_unique<GameMenu>();
	m_spComManage->push_back(m_spGameMenu.get());

}

void Engine::Update()
{
	LStgEngine::Update();

	debugInfo.Update();

	if (isStateChange)
		checkState();
}

void Engine::Draw()
{
	LStgEngine::Draw();
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
			pEnemy->position().Init(100 + 20 * i, 100);
			ShooterFactory::createNWaysFlower(pEnemy);
		}
		break;
	}

	isStateChange = false;
}
