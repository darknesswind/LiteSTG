#include "stdafx.h"
#include "Sprite.h"
#include "Animation/AnimationBase.h"

int Sprite::idCount = 0;

Sprite::~Sprite(void)
{
}

void Sprite::bindPositionWith(const Sprite& src)
{
	SyncAnimationBase<Vector2>* pAnima = m_animations.createAnimation<SyncAnimationBase<Vector2>>();	
	pAnima->bind(&src, &src.m_position, &m_position);
}

void Sprite::bindPositionTo(Sprite& dest)
{
	SyncAnimationBase<Vector2>* pAnima = m_animations.createAnimation<SyncAnimationBase<Vector2>>();
	pAnima->bind(this, &m_position, &dest.m_position);
}
