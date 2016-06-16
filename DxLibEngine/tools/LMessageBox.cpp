#include "stdafx.h"
#include "LMessageBox.h"


LMessageBox::LMessageBox()
{
}


LMessageBox::~LMessageBox()
{
}

void LMessageBox::message(LPCWSTR lpMsg, LPCWSTR lpTitle)
{
	MessageBoxW(NULL, lpMsg, lpTitle, MB_OK | MB_ICONWARNING);
}
