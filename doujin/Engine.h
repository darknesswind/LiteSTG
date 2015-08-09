#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include "LEngine.h"

#pragma region pre-define
class LBullets;
class LPlayers;
class LEnemys;
class Player;
class GameMenu;
class ComManager;
typedef ComManager LCharacters;
#pragma endregion

class StgEngine : public LEngine
{
public:
	typedef LEngine Base;
	StgEngine(void);
	~StgEngine(void);

public:
	virtual void BeforeDxInit() override;
	virtual void AfterDxInit() override;
	virtual bool LoopCheck() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void BeforeEnd() override;

public:
	static StgEngine* engine() { return static_cast<StgEngine*>(s_pEngine); }
	static LBullets* bullets() { return engine()->GetBullets(); }

public:
	LBullets* GetBullets() { return m_spBullets.get(); }

public:
	Player* GetActivePlayer();

private:
	void checkState();

protected:
	std::auto_ptr<LBullets> m_spBullets;
	std::auto_ptr<LPlayers> m_spPlayers;
	std::auto_ptr<LEnemys> m_spEnemys;
	std::auto_ptr<ComManager> m_spComManage;

private:
	std::auto_ptr<GameMenu> m_spGameMenu;

};

#endif