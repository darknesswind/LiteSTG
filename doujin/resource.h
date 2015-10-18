#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#pragma once
#include "interdef.h"
#include "LHandle.h"
namespace NS_Resource
{
	enum TitleID { Title_BG, Title_MainSelection };
	enum PlayerItem { P_Image, P_HitBox, P_Attack};
	enum PlayerID { Reimu };
}

//using namespace NS_Resource;
class Resource
{
public:
	static bool loadPrimaryGameResource();
	static bool loadPlayerResource(NS_Resource::PlayerID pid);
	static inline LGraphHandle hitBox()
	{
		return _hitBox;
	}
	static inline LGraphHandle player(int index)
	{
		return _player[index];
	}
	static inline LGraphHandle bullet(const BulletStyle &style)
	{
		return hBulletImg[style.type][style.color];
	}
	static inline LGraphHandle laserEffect(int index)
	{
		return hEffect[index];
	}

private:
	Resource();
	static GraphHandle _hitBox;
	static GraphHandle _player[24];
	static GraphHandle _attack[3];
	static GraphHandle hBulletImg[18][16];
	static GraphHandle hEffect[8];

	int __dummy;
};
#endif