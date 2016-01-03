#ifndef __LENGINE_H__
#define __LENGINE_H__
#pragma once

#include "LUnifiedTimer.h"
#include "move/LPathSet.h"

class LRender;
class LAssets;
class LInput;
class LUIRoot;
class LEngine
{
public:
	LEngine(void);
	virtual ~LEngine(void);

public:
	int exec();
	LUnifiedTimer& unifiedTimer() { return m_centerTimer; }
	LPathSet& pathSet() { return m_pathSet; }

public:
	void setEndFlag(bool bEnd) { m_bEndFlag = bEnd; }

protected:
	virtual void BeforeDxInit() { }
	virtual void PreLoad();
	virtual void OnLoading();
	virtual bool LoopCheck();
	virtual bool NeedUpdate();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void BeforeEnd();

private:
	void innerInit();

public:
	static LEngine* engine() { return s_pEngine; }
	static LRender* render() { return s_pEngine->m_spRender.get(); }
	static LAssets* assets() { return s_pEngine->m_spAssets.get(); }
	static LInput* input() { return s_pEngine->m_spInput.get(); }
	static LUIRoot* rootUI() { return s_pEngine->m_spRootUI.get(); }

protected:
	static LEngine* s_pEngine;

protected:
	bool m_bDebugPause = false;
	bool m_bEndFlag = false;

	LUnifiedTimer m_centerTimer;
	LPathSet m_pathSet;

	std::unique_ptr<LRender> m_spRender;
	std::unique_ptr<LAssets> m_spAssets;
	std::unique_ptr<LInput> m_spInput;
	std::unique_ptr<LUIRoot> m_spRootUI;
};

#endif
