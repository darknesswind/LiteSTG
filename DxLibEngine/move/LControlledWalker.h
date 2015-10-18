#ifndef __LPLAYERWALKER_H__
#define __LPLAYERWALKER_H__
#include "LWalker.h"

class LControlledWalker : public LWalker
{
public:
	LControlledWalker();
	virtual ~LControlledWalker() = default;

	void nextStep(PhysicData& data);
	void setSpeed(float fNormal, float fFocus);

private:
	float m_normalSpeed;
	float m_focusSpeed;
};

#endif // __LPLAYERWALKER_H__