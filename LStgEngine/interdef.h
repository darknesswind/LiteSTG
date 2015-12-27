#ifndef InterDefine_H
#define InterDefine_H
#include "Vector2.hpp"

typedef unsigned int uint;

enum class BulletType
{
	Generic,
	SegmentLaser,
	RayLaser,
	CurveLaser,
};

class LBulletStyle;
struct LBulletVisual
{
	LBulletStyle* pStyle = nullptr;
	LGraphHandle hGraph;
};

struct _InnerEntityData	// Åö×²ÊµÌå
{
	enum Type
	{
		tCircle,
		tRectangle,
	};

	Type type;
	Vector2 center;
	float halfWidth;
	float halfHeight;
};

struct EntityData : public _InnerEntityData
{
	EntityData()
		: _InnerEntityData{ tCircle, {0, 0}, 0, 0 }
	{
	}
	EntityData(_InnerEntityData&& other)
		: _InnerEntityData(std::move(other))
	{
	}
};

#endif