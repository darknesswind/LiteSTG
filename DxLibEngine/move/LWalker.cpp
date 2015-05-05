#include "stdafx.h"
#include "LWalker.h"
#include "LPhysicWalker.h"
#include "LPathWalker.h"
#include "LControlledWalker.h"
#include "LFollowWalker.h"

void LWalker::nextStep(PhysicData& data)
{
}

IWalker* LWalker::CreateWalker(WalkerType type)
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
		return new LFollowWalker;
	case WalkerType::Stable:
	default:
		return new LWalker();
	}
}

LWalker* LWalker::CreateStableWalker()
{
	return new LWalker();
}

LPhysicWalker* LWalker::CreatePhysicWalker()
{
	return new LPhysicWalker();
}

LPathWalker* LWalker::CreatePathWalker(uint id /*= 0*/)
{
	return new LPathWalker(id);
}

LControlledWalker* LWalker::CreateControlledWalker()
{
	return new LControlledWalker();
}

LFollowWalker* LWalker::CreateFollowWalker()
{
	return new LFollowWalker;
}
