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
	MessageBox(NULL, lpMsg, lpTitle, MB_OK | MB_ICONWARNING);
}

void LMessageBox::message(const QString& sMsg, const QString& sTitle)
{
	message(QWSTR(sMsg), QWSTR(sTitle));
}
