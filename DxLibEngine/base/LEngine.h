#ifndef __LENGINE_H__
#define __LENGINE_H__
#pragma once

#include "LUnifiedTimer.h"

class LEngine
{
public:
	LEngine(void);
	virtual ~LEngine(void);

	int exec();
	LUnifiedTimer& unifiedTimer() { return m_centerTimer; }

public:
	virtual bool BeforeDxInit() { return true; }
	virtual bool AfterDxInit() { return true; }
	virtual bool LoopCheck();
	virtual bool MainLoop() = 0;
	virtual bool BeforeEnd() { return true; }

protected:
	LUnifiedTimer m_centerTimer;
};

#endif
