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


	m_spBullets = std::make_unique<LBullets>();
	m_spPlayers = std::make_unique<LPlayers>();
	m_spEnemys = std::make_unique<LEnemys>();

	m_spComManage = std::make_unique<ComManager>();

	m_pathSet.load(L".\\resource\\data\\PathSet.xml");
	m_spBullets->styles()->LoadBulletStyles(_T("resource\\bulletstyles.json"));
	m_bDebugPause = false;
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
	m_spEnemys->Update();
	m_spPlayers->Update();
	m_spBullets->Update();
	m_spComManage->Update();
}

void LStgEngine::Draw()
{
	m_spEnemys->CommitRender();
	m_spBullets->CommitRender();
	m_spPlayers->CommitRender();
	m_spComManage->Draw();
}

void LStgEngine::BeforeEnd()
{
	m_spEnemys->Clear();
	m_spPlayers->Clear();
	m_spBullets->Clear();

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
