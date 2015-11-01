#ifndef InterDefine_H
#define InterDefine_H
#include "Vector2.hpp"

typedef unsigned int uint;
typedef int GraphHandle;
typedef int SoundHandle;

enum class BulletType
{
	Generic,
	SegmentLaser,
	RayLaser,
	CurveLaser,
};

enum BulletClass : unsigned int
{
	激光,
	鳞弹,
	小玉,
	小玉2,
	米弹,
	链弹,
	针弹,
	札弹,
	铳弹,
	黑米弹,
	星弹,
	大星弹,
	中玉,
	蝶弹,
	剑弹,
	椭弹,
	大玉,
	曲线激光,
};

struct BulletStyle
{
	BulletClass type;
	int color;

	BulletStyle(BulletClass _type = BulletClass::鳞弹, int _color = 2)
		: type(_type), color(_color)
	{
	}
};

struct BulletData
{
	Vector2	speed;		// 速度
	Vector2	gravitation;// 加速度
	float	friction;	// 摩擦
	BulletStyle	style;	// 样式

	BulletData() : friction(0)
	{}
};

struct _InnerEntityData	// 碰撞实体
{
	enum Type
	{
		tUnknown,
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
		: _InnerEntityData{ tUnknown, {0, 0}, 0, 0 }
	{
	}
	EntityData(_InnerEntityData&& other)
		: _InnerEntityData(std::move(other))
	{
	}
};

#endif