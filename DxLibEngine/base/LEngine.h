#ifndef __LENGINE_H__
#define __LENGINE_H__
#pragma once

#include "LUnifiedTimer.h"
#include "move/LPathSet.h"

namespace GameState
{
	enum BaseState
	{
		None,
		Loading,
		Menu,
		Test,
	};
}

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
	LUnifiedTimer& unifiedTimer() { return m_centerTimer; }
	LPathSet& pathSet() { return m_pathSet; }

public:
	int exec();
	void setEndFlag(bool bEnd) { m_bEndFlag = bEnd; }
	bool ChangeState(uint nextState);

protected:
	virtual void BeforeDxInit() { }
	virtual void PreLoad();
	virtual void OnAsyncLoading();
	virtual bool LoopCheck();
	virtual bool NeedUpdate();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void BeforeEnd();

	virtual void OnEnterState(uint state) = 0;
	virtual void OnExecState(uint state) = 0;
	virtual bool OnExitState(uint state) = 0;
private:
	void BeginLoading();

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
	bool m_bLoadReady = true;

	uint m_curState;

	LUnifiedTimer m_centerTimer;
	LPathSet m_pathSet;

	std::unique_ptr<LRender> m_spRender;
	std::unique_ptr<LAssets> m_spAssets;
	std::unique_ptr<LInput> m_spInput;
	std::unique_ptr<LUIRoot> m_spRootUI;
};

#endif
