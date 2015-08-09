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
class LStage : public LGameObject
{
public:
	LStage(IGameObject* pParent);
	virtual ~LStage();

public: // IGameObject
	virtual void Update();
	virtual void Draw(LPainter& painter){}

public:
	void loadStage();

private:
	int m_timeCount;
	std::deque<timeLineItem> m_timeLine;
	std::auto_ptr<LEnemys> m_spEnemys;
};
#endif