#pragma once
namespace proto
{
	class Collide;
}

struct EntityData
{
public:
	enum Type
	{
		tCircle		= 0,
		tRectangle	= 1,

		OffsetMask	= 0x1000,
		tOffsetCircle = OffsetMask | tCircle,
		tOffsetRect = OffsetMask | tRectangle,
	};
public:
	void fromConfig(const proto::Collide& config);

public:
	Type type{ tCircle };
	Vector2 center;
	float halfWidth{ 0 };
	float halfHeight{ 0 };
};
