#include "stdafx.h"
#include <Windows.h>
#include "CirnoEngine.h"
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
	)
{
	CirnoEngine engine;
	return engine.exec();
}