#ifndef __LPHYSICWALKER_H__
#define __LPHYSICWALKER_H__
#include "LWalker.h"

class LPhysicWalker : public LWalker
{
public:
	LPhysicWalker() = default;
	virtual ~LPhysicWalker() = default;

	void nextStep(PhysicData& data);
private:

};

#endif // __LPHYSICWALKER_H__