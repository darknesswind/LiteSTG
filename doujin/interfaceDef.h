#ifndef __INTERFACE_DEFINE__
#define __INTERFACE_DEFINE__
#include "interdef.h"

__interface IComponent // �������
{
	virtual void Update() PURE;
	virtual void Draw() PURE;
};

__interface IAnimateAtom
{
	virtual void update() PURE;
	virtual bool isValid() const PURE;
};

__interface IAnimationSrcHost
{
	virtual bool isValid() const PURE;
};

#endif // __INTERFACE_DEFINE__