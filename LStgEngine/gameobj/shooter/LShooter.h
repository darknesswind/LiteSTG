#ifndef _SHOOTER_H_
#define _SHOOTER_H_
#pragma once
#include "LGameObject.h"

class LWalker;
enum class ShooterType
{
	Normal,
	Segment,
	Ray,
	Curve,
};

// 通用发射器
class LShooter : public LGameObject
{
public:
	explicit LShooter(IGameObject* pParent);
	virtual ~LShooter(void){}

public:
	virtual void Update();
	virtual void Draw(LPainter&){}

public:
	LShooter& setFireWays(int _ways)	// 设置射击路数
	{
		m_fireWays = _ways;
		m_angleIncrease = m_fireRange / m_fireWays;
		return *this;
	}
	LShooter& setFireRange(Degree degree)	//设定攻击范围Degree
	{
		m_fireRange = degree;
		m_angleIncrease = m_fireRange / m_fireWays;
		return *this;
	}
	LShooter& setFollowPlayer(bool bFollowPlayer)	// 设置射击方向跟随自机
	{
		m_bFollowPlayer = bFollowPlayer;
		return *this;
	}
	LShooter& setFireFreq(int frequency)	// 设计射击频率（帧/发）
	{
		m_frequency = frequency;
		return *this;
	}
	LShooter& setAngleSpeed(Degree angleSpeed)	// 设置发射器角速度
	{
		m_angleSpeed = angleSpeed;
		return *this;
	}
	LShooter& setAngleAccel(Degree angleAcceleration)	//设置发射器角加速度
	{
		m_angleAccel = angleAcceleration;
		return *this;
	}

	const PhysicData& bulletData() const { return m_bulletData; }
	void setBulletData(const PhysicData& bulletData);
	void setFireSpeed(Vector2 speed);// 初始射击速度
	void setBulletFriction(float friction) { m_bulletData.friction = friction; }
	void setBulletAcceleration(Vector2 gravitation) { m_bulletData.acceleration = gravitation; }

protected:
	void baseInit();

protected:
	// bullet data
	PhysicData m_bulletData;
	LBulletStyle* m_pBulletStyle;
	float m_bulletSpeed;	// 发射速度
	Degree m_fireDegree;		// 发射中心角度

	// shooter data
	destory_ptr<IWalker> m_spWalker;
	int m_life;				// 生存时间
	Degree m_fireRange;		// 发射角范围 Degree
	Degree m_angleSpeed;	// 角速度
	Degree m_angleAccel;	// 角加速度
	int m_fireWays;			// 发射路数	
	int m_frequency;		// 发射周期
	bool m_bFollowPlayer;	// 发射中心角是否跟随自机

	Degree m_angleIncrease;	// 每路子弹夹角
	int m_counter;			// 周期计数器
};

#endif
