#ifndef __ANIMATION_MANAGER_H__
#define __ANIMATION_MANAGER_H__
#include "interfaceDef.h"
#include <vector>

class AnimationManager
{
	typedef std::vector<IAnimateAtom*> AnimationList;
public:
	AnimationManager() {}
	~AnimationManager();

	void update();
	template <class AnimaType>
	AnimaType* createAnimation();

private:
	AnimationList m_animations;
};

template <class AnimaType>
AnimaType* AnimationManager::createAnimation()
{
	AnimaType* pAnimation = new AnimaType();
	m_animations.push_back(pAnimation);
	return pAnimation;
}

#endif //__ANIMATION_MANAGER_H__
