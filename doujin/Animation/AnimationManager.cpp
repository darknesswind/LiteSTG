#include "stdafx.h"
#include "AnimationManager.h"


AnimationManager::~AnimationManager()
{
	for each(IAnimateAtom* pAnima in m_animations)
	{
		delete pAnima;
	}
}

void AnimationManager::update()
{
	for each(IAnimateAtom* pAnima in m_animations)
	{
		pAnima->update();
	}
}
