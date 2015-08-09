#include "stdafx.h"
#include "LEngine.h"
#include "LScreen.h"
#include "Input.h"
#include "painting/LRender.h"

LEngine* LEngine::s_pEngine = nullptr;

LEngine::LEngine(void)
	: m_bDebugPause(false)
{
	LAssert(!s_pEngine);
	s_pEngine = this;

	m_spRender.reset(new LRender());
}

LEngine::~LEngine(void)
{
	DxLib::DxLib_End();
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
	if (!m_bDebugPause)
		return true;

	if (Input.isKeyPress(Keys::F10) || Input.isKeyDown(Keys::F11))
		return true;
#endif
	return false;
}

void LEngine::BeforeEnd()
{
	m_pathSet.clear();
}
