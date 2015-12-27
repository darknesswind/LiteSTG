#ifndef InterDefine_H
#define InterDefine_H
#include "Vector2.hpp"
#include "LHandle.h"

typedef unsigned int uint;

enum class BulletType
{
	Generic,
	SegmentLaser,
	RayLaser,
	CurveLaser,
	Count
};

class LBulletStyle;
struct LBulletVisual
{
	LBulletStyle* pStyle = nullptr;
	LGraphHandle hGraph;
};

struct _InnerEntityData	// 碰撞实体
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

class LPainter;
__interface IComponent // 组件基类
{
	virtual void Update() = 0;
	virtual void Draw(LPainter& painter) = 0;
};


#endif