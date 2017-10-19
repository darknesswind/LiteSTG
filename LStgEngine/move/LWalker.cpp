#include "stdafx.h"
#include "LWalker.h"
#include "LPhysicWalker.h"
#include "LPathWalker.h"
#include "LControlledWalker.h"
#include "LFollowWalker.h"

void LWalker::nextStep(PhysicData& data)
{
}

WalkerPtr LWalker::CreateWalker(WalkerType type)
{
	switch (type)
	{
	case WalkerType::Physic:
		return new LPhysicWalker();
	case WalkerType::Path:
		return new LPathWalker();
	case WalkerType::Controlled:
		return new LControlledWalker();
	case WalkerType::Follow:
		return new LFollowWalker(nullptr);
	case WalkerType::Stable:
	default:
		return new LWalker();
	}
}

WalkerPtr LWalker::CreateStableWalker()
{
	return new LWalker();
}

WalkerPtr LWalker::CreatePhysicWalker()
{
	return new LPhysicWalker();
}

WalkerPtr LWalker::CreatePathWalker(uint id /*= 0*/)
{
	return new LPathWalker(id);
}

WalkerPtr LWalker::CreateControlledWalker()
{
	return new LControlledWalker();
}

WalkerPtr LWalker::CreateFollowWalker(IGameObject* pTarget)
{
	return new LFollowWalker(pTarget);
}
