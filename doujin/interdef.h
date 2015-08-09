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
	����,
	�۵�,
	С��,
	С��2,
	�׵�,
	����,
	�뵯,
	����,
	掠�,
	���׵�,
	�ǵ�,
	���ǵ�,
	����,
	����,
	����,
	�ֵ�,
	����,
	���߼���,
};

struct BulletStyle
{
	BulletClass type;
	int color;

	BulletStyle(BulletClass _type = BulletClass::�۵�, int _color = 2)
		: type(_type), color(_color)
	{
	}
};

struct BulletData
{
	Vector2	speed;		// �ٶ�
	Vector2	gravitation;// ���ٶ�
	float	friction;	// Ħ��
	BulletStyle	style;	// ��ʽ

	BulletData() : friction(0)
	{}
};

#endif