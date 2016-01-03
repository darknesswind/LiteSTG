#ifndef __LPLAYERWALKER_H__
#define __LPLAYERWALKER_H__
#include "LWalker.h"

class LInput;
class LControlledWalker : public LWalker
{
public:
	LControlledWalker();
	virtual ~LControlledWalker() = default;

	void nextStep(PhysicData& data);
	void setSpeed(float fNormal, float fFocus);

private:
	enum SpeedIDX
	{
		sNormal	= 0x0,
		sFocus	= 0x1,
		sDiagNormal	= 0x2,
		sDiagFocus	= 0x3,

		sDiagFlag	= 0x2,
	};

private:
	float m_speeds[4];
	LInput* m_pInput;
};

#endif // __LPLAYERWALKER_H__