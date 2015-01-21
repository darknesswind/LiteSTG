#ifndef _TLASER_H_
#define _TLASER_H_
#pragma once
#include "DxLib.h"
#include "Bullet.h"
#include "CollideEntity/RectEntity.h"
class RayLaser : public Bullet
{
	enum RayState
	{
		RayExpand = 1,
		RayHold = 0,
		RayCollapse = -1,
	};

public:
	RayLaser(IGameObject* pParent);
	~RayLaser();

	virtual void Draw();
	virtual void Update();
	virtual BulletType GetType() const { return BulletType::RayLaser; }

	void setWidthExtRange(float width)	{ m_width = width; }
	void setLengthExtRange(float length) { m_length = length; }
	void setTurnFlag(BOOL bTurn) { turnFlag = bTurn; }

private:
	static const int g_nPlayTime = 20; // 展开/衰减时间
	float m_width;	// 宽度缩放倍率
	float t_wid;
	float m_length;
	int m_nExpandCount, m_nCollapseCount;
	RayState m_state;
	int turnFlag;

	RectEntity *m_pMutableEntity;
	const RectEntity *m_pOriginEntity;
};

#endif