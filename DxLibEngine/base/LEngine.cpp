#include "stdafx.h"
#include "LEngine.h"
#include "LScreen.h"
#include "Input.h"
#include "painting/LRender.h"
#include "LAssets.h"

LEngine* LEngine::s_pEngine = nullptr;

LEngine::LEngine(void)
	: m_bDebugPause(false)
{
	LAssert(!s_pEngine);
	s_pEngine = this;

	m_spRender = std::make_unique<LRender>();
	m_spAssets = std::make_unique<LAssets>();
}

LEngine::~LEngine(void)
{
	DxLib::DxLib_End();
}

void LEngine::AfterDxInit()
{
	m_spAssets->LoadTextureList(L"resource\\data\\texture.csv");
	m_spAssets->LoadSoundEffectList(L"resource\\data\\se.csv");
	m_spAssets->LoadSubGraphicsList(L"resource\\data\\subgraph.csv");
}

int LEngine::exec()
{
	BeforeDxInit();
	if (DxLib::DxLib_Init() == -1)
	{
		return -1;
	}
	Screen.setDrawScreen(DrawScreen::dsBack);
	Input.init();
	AfterDxInit();

	m_centerTimer.start();
	while (LoopCheck())
	{
#ifdef _DEBUG
		if (Input.isKeyPress(Keys::F9))
			m_bDebugPause = !m_bDebugPause;
#endif
		m_centerTimer.update();
		if (NeedUpdate())
			Update();

		Draw();

		render()->DoRender();
		Screen.screenFlip();
	}

	BeforeEnd();
	return 0;
}

bool LEngine::LoopCheck()
{
	Screen.clearDrawScreen();
	return (0 == DxLib::ProcessMessage());
}

bool LEngine::NeedUpdate()
{
#ifdef _DEBUG
	if (m_bDebugPause)
	{
		if (Input.isKeyPress(Keys::F10) || Input.isKeyDown(Keys::F11))
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
}
