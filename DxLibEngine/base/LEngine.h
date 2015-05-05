#ifndef __LENGINE_H__
#define __LENGINE_H__
#pragma once

#include "LUnifiedTimer.h"
#include "move/LPathSet.h"
#define EngineBase LEngine::s_pEngine

class LEngine
{
public:
	LEngine(void);
	virtual ~LEngine(void);

	int exec();
	LUnifiedTimer& unifiedTimer() { return m_centerTimer; }
	LPathSet& pathSet() { return m_pathSet; }

public:
	virtual bool BeforeDxInit() { return true; }
	virtual bool AfterDxInit() { return true; }
	virtual bool LoopCheck();
	virtual bool MainLoop() = 0;
	virtual bool BeforeEnd();

public:
	static LEngine* s_pEngine;

protected:
	LUnifiedTimer m_centerTimer;
	LPathSet m_pathSet;

};

#endif
