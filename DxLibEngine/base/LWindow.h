#ifndef __LWINDOW_H__
#define __LWINDOW_H__
#pragma once
#include "typedef.h"
#include <windows.h>
#define AppWindow LWindow::Instance

#pragma region pre-define
class QString;
typedef int(*OnActiveStateChange)(int ActiveState, void *pUserData);

#pragma endregion

class LWindow
{
public:
	static LWindow Instance;
	~LWindow();

public: // get set
	void	setIsWindowMode(bool bUseWindowMode);
	bool	getIsWindowMode();
	void	setRunWhenDeactivate(bool bAlwaysRun);
	bool	getRunWhenDeactivate();

public: // set only
	void setWindowText(const QString& sWindowText);
	void setActiveStateChangeCallBack(OnActiveStateChange pCallBack, void* pUserData);
	void setHookWinProc(WNDPROC WinProc) { UserWinProc = WinProc; }

private:
	LWindow();
	friend LRESULT CALLBACK InnerinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	LWindow(const LWindow&) = delete;
	void operator=(const LWindow&) = delete;

private:
	WNDPROC UserWinProc;
};

#endif // !__LWINDOW_H__
