#include "stdafx.h"
#include "CirnoEngine.h"

#include "Manager/ComManage.h"

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

void CirnoEngine::BeforeDxInit()
{
	Base::BeforeDxInit();
}

void CirnoEngine::PreLoad()
{
	Base::PreLoad();
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
}

void CirnoEngine::Draw()
{
	Base::Draw();
	debugInfo.Draw(LStgEngine::render()->GetPainter());
}

void CirnoEngine::OnEnterState(uint state)
{
	switch (state)
	{
	case GameState::Loading:
		m_spRootUI->pushChild(new LoadingUI(), true);
		break;
	case GameState::Menu:
		m_spRootUI->pushChild(new GameMenu(), true);
		break;
	case GameState::Test:
		{
			static 	BaseFrame baseFrame;
			m_spComManage->clear();
			m_spComManage->push_back(&baseFrame);

			m_spPlayers->Add(PlayerType::Controlled);
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
			ChangeState(GameState::Menu);
		break;
	case GameState::Menu:
		break;
	case GameState::Test:
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
		break;
	case GameState::Test:
		break;
	default:
		break;
	}
	return true;
}
