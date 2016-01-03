#include "stdafx.h"
#include "LEngine.h"
#include "LScreen.h"
#include "Input.h"
#include "painting/LRender.h"
#include "LAssets.h"
#include "ui/LUIObjBase.h"

#include <thread>
#include <atomic>

LEngine* LEngine::s_pEngine = nullptr;

LEngine::LEngine(void)
{
	LAssert(!s_pEngine);
	s_pEngine = this;

	m_spRender = std::make_unique<LRender>();
	m_spAssets = std::make_unique<LAssets>();
	m_spRootUI = std::make_unique<LUIRoot>();
}

LEngine::~LEngine(void)
{
	DxLib::DxLib_End();
}

void LEngine::PreLoad()
{
	Screen.setDrawScreen(DrawScreen::dsBack);
	m_centerTimer.start();

	m_spInput = std::make_unique<LInput>();
	m_spAssets->LoadTextureList(L"resource\\textures.json");
	m_spAssets->LoadSubGraphicsList(L"resource\\subgraphics.json");
}

void LEngine::innerInit()
{
	PreLoad();

	std::atomic_bool bReady(false);
	std::thread initThread([this, &bReady]()
	{
		OnLoading();
		bReady = true;
	});
	initThread.detach();

	uint minShowTime = 600;
	while (LoopCheck() && (!bReady || --minShowTime > 0))
	{
		Screen.clearDrawScreen();
		m_spRootUI->Update();
		m_spRootUI->commitRender();
		m_spRender->DoRender();
		Screen.screenFlip();
	}
}

void LEngine::OnLoading()
{
// 	m_spAssets->LoadSoundEffectList(L"resource\\data\\se.csv");
}

int LEngine::exec()
{
	BeforeDxInit();
	if (DxLib::DxLib_Init() == -1)
	{
		return -1;
	}
	innerInit();

	while (LoopCheck())
	{
		m_spInput->update();
#ifdef _DEBUG
		if (m_spInput->isKeyPress(Keys::F9))
			m_bDebugPause = !m_bDebugPause;
#endif
		Screen.clearDrawScreen();

		if (NeedUpdate())
			Update();

		Draw();

		m_spRender->DoRender();
		Screen.screenFlip();
	}

	BeforeEnd();
	return 0;
}

bool LEngine::LoopCheck()
{
	if (DxLib::ProcessMessage() < 0)
		return false;

	m_centerTimer.update();
	return !m_bEndFlag;
}

bool LEngine::NeedUpdate()
{
#ifdef _DEBUG
	if (m_bDebugPause)
	{
		if (m_spInput->isKeyPress(Keys::F10) || m_spInput->isKeyDown(Keys::F11))
			return true;
		else
			return false;
	}
#endif
	return true;
}

void LEngine::BeforeEnd()
{
	m_pathSet.clear();
	m_spRootUI->clearChildren();
}
