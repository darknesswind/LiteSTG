#include "stdafx.h"
#include "LEngine.h"
#include "LScreen.h"
#include "Input.h"
#include "painting/LRender.h"

LEngine::LEngine(void)
{
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
		m_centerTimer.update();
		if (!MainLoop())
			break;

		Render.DoRender();
		Screen.screenFlip();
	}

	return BeforeEnd();
}

bool LEngine::LoopCheck()
{
	Screen.clearDrawScreen();
	return (0 == DxLib::ProcessMessage());
}
