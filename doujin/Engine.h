#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include "LEngine.h"
#include "bullet/LBullets.h"
#include "player/LPlayers.h"
#include "enemy/LEnemys.h"
#define Engine StgEngine::Instance

#pragma region pre-define
class GameMenu;
class ComManager;
typedef ComManager LCharacters;
#pragma endregion

class StgEngine : public LEngine
{
public:
	typedef LEngine Base;
	~StgEngine(void);

public:
	virtual bool BeforeDxInit();
	virtual bool AfterDxInit();
	virtual bool LoopCheck();
	virtual bool MainLoop();
	virtual bool BeforeEnd();

public:
	LBullets* GetBullets() { return m_spBullets.get(); }

public:
	Player* GetActivePlayer();

public:
	static StgEngine Instance;

protected:
	std::auto_ptr<LBullets> m_spBullets;
	std::auto_ptr<LPlayers> m_spPlayers;
	std::auto_ptr<LEnemys> m_spEnemys;
	std::auto_ptr<ComManager> m_spComManage;

private:
	StgEngine(void);
	void checkState();

	GameMenu *pGameMenu;
	bool m_bDebugPause;
};

#endif