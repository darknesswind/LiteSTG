#include "stdafx.h"
#include "LWindow.h"
#include "LPoint.h"

LWindow LWindow::Instance;

LWindow::LWindow()
	: UserWinProc(nullptr)
{
	CheckRes(DxLib::SetHookWinProc(InnerinProc));
}

LWindow::~LWindow()
{
}

void LWindow::setIsWindowMode(bool bUseWindowMode)
{
	CheckRes(DxLib::ChangeWindowMode(bUseWindowMode));
}

bool LWindow::getIsWindowMode()
{
	return DxLib::GetWindowModeFlag();
}

void LWindow::setWindowText(const QString& sWindowText)
{
	CheckRes(DxLib::SetMainWindowText(sWindowText.utf16w()));
}

void LWindow::setActiveStateChangeCallBack(OnActiveStateChange pCallBack, void* pUserData)
{
	CheckRes(DxLib::SetActiveStateChangeCallBackFunction(pCallBack, pUserData));
}

void LWindow::setRunWhenDeactivate(bool bAlwaysRun)
{
	CheckRes(DxLib::SetAlwaysRunFlag(bAlwaysRun));
}

bool LWindow::getRunWhenDeactivate()
{
	return DxLib::GetAlwaysRunFlag();
}

LRESULT CALLBACK InnerinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = S_OK;
	if (AppWindow.UserWinProc)
		result = AppWindow.UserWinProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		if (VK_F10 == wParam)
		{
			CheckRes(DxLib::SetUseHookWinProcReturnValue(true));
		}
		break;
	default:
		break;
	}
	return result;
}