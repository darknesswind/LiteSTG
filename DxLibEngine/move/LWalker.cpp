#include "stdafx.h"
#include "LWalker.h"
#include "LPhysicWalker.h"
#include "LPathWalker.h"
#include "LControlledWalker.h"
#include "LFollowWalker.h"

void LWalker::nextStep(PhysicData& data)
{
}

LWalker* LWalker::CreateWalker(WalkerType type)
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

LWalker* LWalker::CreateStableWalker()
{
	return new LWalker();
}

LWalker* LWalker::CreatePhysicWalker()
{
	return new LPhysicWalker();
}

LWalker* LWalker::CreatePathWalker(uint id /*= 0*/)
{
	return new LPathWalker(id);
}

LWalker* LWalker::CreateControlledWalker()
{
	return new LControlledWalker();
}

LWalker* LWalker::CreateFollowWalker(IGameObject* pTarget)
{
	return new LFollowWalker(pTarget);
}
