#ifndef __INTERFACE_DEFINE__
#define __INTERFACE_DEFINE__
#include "interdef.h"

class LPainter;
__interface IComponent // 组件基类
{
	virtual void Update() PURE;
	virtual void Draw(LPainter& painter) PURE;
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