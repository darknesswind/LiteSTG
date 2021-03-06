#include "stdafx.h"
#include "LWindow.h"
#include "LScreen.h"
#include "Input.h"
#include "render/LBulletLayer.h"
#include "render/LEnemyLayer.h"
#include "render/LPlayerLayer.h"
#include "render/LHitboxLayer.h"
#include "render/LUILayer.h"

#include "bullet/LBullets.h"
#include "bullet/LBulletStyles.h"
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#include "ui/LUIObjBase.h"
#include "move/LPathSet.h"
#include "stage/LStage.h"

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

	m_spStyles = std::make_unique<LBulletStyles>();
	m_spStage = std::make_unique<LStage>();
	m_spPathSet = std::make_unique<LPathSet>();
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

	m_spPathSet->load(L".\\resource\\PathSet.pb");
	m_spStyles->LoadAssets(L"resource\\bulletstyles.pb");
	LPlayers::LoadAssets(L"resource\\player.pb.json", false);

	m_spRender->addLayer(tEnemyLayer, std::make_unique<LEnemyLayer>());
	m_spRender->addLayer(tPlayerLayer, std::make_unique<LPlayerLayer>());
	m_spRender->addLayer(tBulletLayer, std::make_unique<LBulletLayer>());
	m_spRender->addLayer(tHitboxLayer, std::make_unique<LHitboxLayer>());
	m_spRender->addLayer(tUILayer, std::make_unique<LUILayer>());
}

void LStgEngine::Update()
{
	m_spStage->Update();
	m_spRootUI->Update();
}

void LStgEngine::BeforeEnd()
{
	m_spPathSet->clear();

	Base::BeforeEnd();
}

LPlayer* LStgEngine::getActivePlayer()
{
	return m_spStage->players()->GetActiveItem();
}
