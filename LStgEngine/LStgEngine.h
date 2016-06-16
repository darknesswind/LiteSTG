#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include "LEngine.h"

#pragma region pre-define
class LBullets;
class LPlayers;
class LEnemys;
class Player;
class ComManager;
class LBulletStyles;
typedef ComManager LCharacters;
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
	virtual void Draw() override;
	virtual void BeforeEnd() override;

public:
	static LStgEngine* engine() { return static_cast<LStgEngine*>(s_pEngine); }
	static LBullets* bullets() { return engine()->GetBullets(); }
	static LBulletStyles* bulletStyles();

public:
	LBullets* GetBullets() { return m_spBullets.get(); }

public:
	Player* GetActivePlayer();

protected:
	std::unique_ptr<LBullets> m_spBullets;
	std::unique_ptr<LPlayers> m_spPlayers;
	std::unique_ptr<LEnemys> m_spEnemys;
	std::unique_ptr<ComManager> m_spComManage;
};

#endif