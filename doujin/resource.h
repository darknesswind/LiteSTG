#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#pragma once
#include "interdef.h"
#include "LHandle.h"
namespace NS_Resource
{
	enum FrameBackgroundID { BG_Left, BG_Top, BG_Right, BG_Bottom };
	enum SoundEffectID { SE_Miss };
	enum BackgroundMusic {};
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

	static inline LGraphHandle frameBG(NS_Resource::FrameBackgroundID bgid)
	{
		return frameBackground[bgid];
	}
	static inline const int &SE(NS_Resource::SoundEffectID seid)
	{
		return soundEffect[seid];
	}
	static inline const int &BGM(NS_Resource::BackgroundMusic bgmid)
	{
		return soundEffect[0];
	}
	static inline LGraphHandle title(NS_Resource::TitleID tid)
	{
		return titleImage[tid];
	}
	static inline LGraphHandle TitleSelection(int index)
	{
		return titleSelection[index];
	}
	static inline LGraphHandle hitBox()
	{
		return _hitBox;
	}
	static inline LGraphHandle player(int index)
	{
		return _player[index];
	}
	static inline LGraphHandle enemy(int type, int index)
	{
		return hEnemyImg[type][index];
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
	static GraphHandle frameBackground[4];
	static SoundHandle soundEffect[1];
	static GraphHandle titleImage[2];
	static GraphHandle titleSelection[10];
	static GraphHandle _hitBox;
	static GraphHandle _player[24];
	static GraphHandle _attack[3];
	static GraphHandle hEnemyImg[6][12];
	static GraphHandle hBulletImg[18][16];
	static GraphHandle hEffect[8];

};
#endif