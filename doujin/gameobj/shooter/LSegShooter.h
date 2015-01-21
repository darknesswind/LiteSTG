#ifndef __LSEGSHOOTER_H__
#define __LSEGSHOOTER_H__
#pragma once
#include "LShooter.h"

class LSegShooter : public LShooter
{
public:
	explicit LSegShooter(IGameObject* pParent)
		: LShooter(pParent)
	{
	}
	virtual ~LSegShooter(void){}

	virtual void Update();

};

#endif