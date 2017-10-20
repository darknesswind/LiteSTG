#ifndef __LSTAGE_H__
#define __LSTAGE_H__
#pragma once
#include "LGameObject.h"

struct timeLineItem
{
	int startTime;
	int actionType;
};

class LEnemys;
class LBullets;
class LPlayers;
class LStage : public LCollideObject
{
public:
	LStage();
	virtual ~LStage();

	LEnemys* enemys() const { return m_spEnemys.get(); }
	LBullets* bullets() const { return m_spBullets.get(); }
	LPlayers* players() const { return m_spPlayers.get(); }

public: // IGameObject
	virtual void Update();
	virtual void draw(LPainter&){}

public:
	void start() { m_bRunning = true; }
	void pause() { m_bRunning = false; }
	void loadStage();

private:
	bool m_bRunning{ false };
	int m_timeCount;
	std::deque<timeLineItem> m_timeLine;

	std::unique_ptr<LEnemys> m_spEnemys;
	std::unique_ptr<LBullets> m_spBullets;
	std::unique_ptr<LPlayers> m_spPlayers;
};
typedef std::unique_ptr<LStage> LStagePtr;

#endif