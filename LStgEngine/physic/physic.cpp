#include "stdafx.h"
#include "physic.h"
#include "protobuf.h"

void EntityData::fromConfig(const proto::Collide& config)
{
	type = (EntityData::Type)config.type();
	center.rx() = config.centerx();
	center.ry() = config.centery();
	halfWidth = config.radianx();
	halfHeight = config.radiany();
}
