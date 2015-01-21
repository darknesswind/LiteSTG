#ifndef __LFOLLOWWALKER_H__
#define __LFOLLOWWALKER_H__
#include "LWalker.h"

class LFollowWalker : public LWalker
{
public:
	LFollowWalker();
	~LFollowWalker();
	void SetTarget(IGameObject* pGameObj);

public:
	virtual void nextStep(PhysicData& data);

private:
	IGameObject* m_pTarget;
};

#endif