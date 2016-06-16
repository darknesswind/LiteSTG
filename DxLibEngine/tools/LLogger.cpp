#include "stdafx.h"
#include "LLogger.h"
#include "LMessageBox.h"

LLogger::LLogger()
{

}

LLogger::~LLogger()
{

}

void LLogger::Print(LogLevel level, LPCWSTR msg)
{
	if (lvError == level)
	{
		LMessageBox::message(msg, _T("Error"));
		if (IsDebuggerPresent())
			__asm { int 3 }
	}
}
