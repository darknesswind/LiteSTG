#include "stdafx.h"
#include "LWindow.h"
#include "LScreen.h"
#include "LPainter.h"
#include "Input.h"

#include "bullet/LBullets.h"
#include "bullet/LBulletStyles.h"
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#include "Manager/ComManage.h"
#include "ui/LUIObjBase.h"

LStgEngine::LStgEngine(void)
	: LEngine()
{
}

LStgEngine::~LStgEngine(void)
{
}

bool LStgEngine::Init()
{
	AppWindow.setIsWindowMode(true);
	Screen.setGraphMode(640, 480, 32);
	Screen.setWaitVSync(false);
	AppWindow.setRunWhenDeactivate(true);
	
	bool bSucceed = Base::Init();

	m_spBullets = std::make_unique<LBullets>();
	m_spPlayers = std::make_unique<LPlayers>();
	m_spEnemys = std::make_unique<LEnemys>();
	m_spComManage = std::make_unique<ComManager>();

	return bSucceed;
}

void LStgEngine::OnAsyncLoading()
{
	Base::OnAsyncLoading();
	m_spInput->registerKey(StgKey::Left, Keys::Left);
	m_spInput->registerKey(StgKey::Right, Keys::Right);
	m_spInput->registerKey(StgKey::Up, Keys::Up);
	m_spInput->registerKey(StgKey::Down, Keys::Down);
	m_spInput->registerKey(StgKey::Shot, Keys::Z);
	m_spInput->registerKey(StgKey::Bomb, Keys::X);
	m_spInput->registerKey(StgKey::Slow, Keys::LShift);

	m_pathSet.load(L".\\resource\\PathSet.pb");
	m_spBullets->styles()->LoadBulletStyles(L"resource\\bulletstyles.pb");
}

void LStgEngine::Update()
{
	m_spEnemys->Update();
	m_spPlayers->Update();
	m_spBullets->Update();
	m_spComManage->Update();
	m_spRootUI->Update();
}

void LStgEngine::Draw()
{
	m_spEnemys->CommitRender();
	m_spBullets->CommitRender();
	m_spPlayers->CommitRender();
	m_spRootUI->CommitRender();
	m_spComManage->Draw();
}

void LStgEngine::BeforeEnd()
{
	m_spEnemys->Clear();
	m_spPlayers->Clear();
	m_spBullets->Clear();
	m_spComManage->clear();

	Base::BeforeEnd();
}

LBulletStyles* LStgEngine::bulletStyles()
{
	return engine()->bullets()->styles();
}

Player* LStgEngine::GetActivePlayer()
{
	return m_spPlayers->GetActiveItem();
}
