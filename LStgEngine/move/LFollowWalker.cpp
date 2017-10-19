#include "stdafx.h"
#include "LFollowWalker.h"

LFollowWalker::LFollowWalker(IGameObject* pTarget)
	: m_pTarget(pTarget)
{

}

LFollowWalker::~LFollowWalker()
{

}

void LFollowWalker::SetTarget(IGameObject* pGameObj)
{
	m_pTarget = pGameObj;
}

void LFollowWalker::nextStep(PhysicData& data)
{
	if (!m_pTarget)
		return;

	if (!m_pTarget->IsValid())
	{
		m_pTarget = nullptr;
		return;
	}

	data.position = m_pTarget->GetPosition();
}
