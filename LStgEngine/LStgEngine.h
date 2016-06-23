#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include "LEngine.h"

#pragma region pre-define
class LBullets;
class LPlayers;
class LEnemys;
class LPlayer;
class LBulletStyles;
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
	static LBullets* bullets() { return engine()->getBullets(); }
	static LEnemys* enemys() { return engine()->getEnemys(); }
	static LBulletStyles* bulletStyles();

public:
	LBullets* getBullets() { return m_spBullets.get(); }
	LEnemys* getEnemys() { return m_spEnemys.get(); }

public:
	LPlayer* getActivePlayer();

protected:
	std::unique_ptr<LBullets> m_spBullets;
	std::unique_ptr<LPlayers> m_spPlayers;
	std::unique_ptr<LEnemys> m_spEnemys;
};

#endif