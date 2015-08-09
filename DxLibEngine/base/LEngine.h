#ifndef __LENGINE_H__
#define __LENGINE_H__
#pragma once

#include "LUnifiedTimer.h"
#include "move/LPathSet.h"

class LRender;
class LEngine
{
public:
	LEngine(void);
	virtual ~LEngine(void);

	int exec();
	LUnifiedTimer& unifiedTimer() { return m_centerTimer; }
	LPathSet& pathSet() { return m_pathSet; }

public:
	virtual void BeforeDxInit() { }
	virtual void AfterDxInit() { }
	virtual bool LoopCheck();
	virtual bool NeedUpdate();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void BeforeEnd();

public:
	static LEngine* engine() { return s_pEngine; }
	static LRender* render() { return s_pEngine->m_spRender.get(); }

protected:
	static LEngine* s_pEngine;

protected:
	LUnifiedTimer m_centerTimer;
	LPathSet m_pathSet;
	bool m_bDebugPause;

	std::auto_ptr<LRender> m_spRender;
};

#endif
