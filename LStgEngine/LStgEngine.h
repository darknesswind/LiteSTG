#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include "LEngine.h"

#pragma region pre-define
class LPlayer;
class LBulletStyles;
class LPathSet;
class LStage;
#pragma endregion

class LStgEngine : public LEngine
{
public:
	typedef LEngine Base;
	LStgEngine(void);
	~LStgEngine(void);

protected:
	virtual bool Init() override;
	virtual void OnAsyncLoading() override;
	virtual void Update() override;
	virtual void BeforeEnd() override;

public:
	static LStgEngine* engine() { return static_cast<LStgEngine*>(s_pEngine); }

public:
	LPathSet* pathSet() { return m_spPathSet.get(); }
	LBulletStyles* bulletStyles() { return m_spStyles.get(); }
	LStage* stage() { return m_spStage.get(); }

public:
	LPlayer* getActivePlayer();

protected:
	std::unique_ptr<LPathSet> m_spPathSet;
	std::unique_ptr<LStage> m_spStage;
	std::unique_ptr<LBulletStyles> m_spStyles;
};

namespace global
{
	inline LStgEngine* engine() { return LStgEngine::engine(); }
	inline LBulletStyles* bulletStyles() { return engine()->bulletStyles(); }
	inline LStage* stage() { return engine()->stage(); }
}

#endif