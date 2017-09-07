#include "stdafx.h"
#include "CirnoEngine.h"

#include "ui/stage/baseFrame.h"
#include "ui/loading/LoadingUI.h"
#include "ui/menu/GameMenu.h"

// DEBUG
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#include "Factory/ShooterFactory.h"
#include "DebugInfo.h"
DebugInfo debugInfo;
// _DEBUG

CirnoEngine::CirnoEngine()
	: LStgEngine()
{

}

CirnoEngine::~CirnoEngine()
{
}

bool CirnoEngine::Init()
{
	return Base::Init();
// 	m_spRootUI->addChild(new LoadingUI(nullptr, true));
}

void CirnoEngine::OnAsyncLoading()
{
	Base::OnAsyncLoading();
}

void CirnoEngine::Update()
{
	Base::Update();

	debugInfo.Update();

	OnExecState(m_curState);

// 	debugInfo.Draw(LStgEngine::render()->GetPainter());
}

void CirnoEngine::OnEnterState(uint state)
{
	switch (state)
	{
	case GameState::Loading:
		m_spRootUI->pushChild(new LoadingUI(), true);
		break;
	case GameState::Menu:
		if (!m_spMainMenu)
			m_spMainMenu = std::make_unique<GameMenu>();
		m_spRootUI->pushChild(m_spMainMenu.get());
		break;
	case GameState::Test:
		{
			if (!m_spPane)
				m_spPane = std::make_unique<BaseFrame>();
			m_spRootUI->pushChild(m_spPane.get());

			m_spPlayers->Add(0, LPlayer::UserInput);
			for (int i = 0; i < 1; ++i)
			{
				LEnemy* pEnemy = m_spEnemys->Add();
				pEnemy->position().reset(100 + 20 * i, 100);
				ShooterFactory::createNWaysFlower(pEnemy);
			}
		}
		break;
	default:
		break;
	}
}

void CirnoEngine::OnExecState(uint state)
{
	switch (state)
	{
	case GameState::Loading:
		if (m_bLoadReady)
			changeState(GameState::Menu);
		break;
	default:
		break;
	}
}

bool CirnoEngine::OnExitState(uint state)
{
	switch (state)
	{
	case GameState::Loading:
		m_spRootUI->popChild();
		break;
	case GameState::Menu:
		m_spRootUI->popChild();
		break;
	case GameState::Test:
		break;
	default:
		break;
	}
	return true;
}
