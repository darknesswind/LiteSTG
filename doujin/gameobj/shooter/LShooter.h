#ifndef _SHOOTER_H_
#define _SHOOTER_H_
#pragma once
#include "LGameObject.h"
#include "MyTimer.h"
#include "interdef.h"

enum class ShooterType
{
	Normal,
	Segment,
	Ray,
	Curve,
};

// ͨ�÷�����
class LShooter : public LGameObject
{
public:
	explicit LShooter(IGameObject* pParent);
	virtual ~LShooter(void){}

public:
	virtual void Update();
	virtual void Draw(){}

public:
	LShooter& setFireWays(int _ways)	// �������·��
	{
		m_fireWays = _ways;
		m_angleIncrease = m_fireRange / m_fireWays;
		return *this;
	}
	LShooter& setFireRange(Degree degree)	//�趨������ΧDegree
	{
		m_fireRange = degree;
		m_angleIncrease = m_fireRange / m_fireWays;
		return *this;
	}
	LShooter& setFollowPlayer(bool bFollowPlayer)	// ���������������Ի�
	{
		m_bFollowPlayer = bFollowPlayer;
		return *this;
	}
	LShooter& setFireFreq(int frequency)	// ������Ƶ�ʣ�֡/����
	{
		m_frequency = frequency;
		return *this;
	}
	LShooter& setAngleSpeed(Degree angleSpeed)	// ���÷��������ٶ�
	{
		m_angleSpeed = angleSpeed;
		return *this;
	}
	LShooter& setAngleAccel(Degree angleAcceleration)	//���÷������Ǽ��ٶ�
	{
		m_angleAccel = angleAcceleration;
		return *this;
	}

	const PhysicData& bulletData() const { return m_bulletData; }
	BulletStyle& bulletStyle() { return m_bulletStyle; }
	void setBulletData(const PhysicData& bulletData);
	void setFireSpeed(Vector2 speed);// ��ʼ����ٶ�
	void setBulletFriction(float friction) { m_bulletData.friction = friction; }
	void setBulletAcceleration(Vector2 gravitation) { m_bulletData.acceleration = gravitation; }

	LShooter& setAdvBulletFunc(int funcType, int startTime)	// ���ӵ����Ӽ�ʱ����
	{
		bulletFunc.push_back(AdvBulletFuncSetting(funcType, startTime));
		return *this;
	}
	LShooter& setAdvShooterFunc(int funcType, int startTime)	// �����������Ӽ�ʱ����
	{
		mytimer.setup(funcList[funcType], startTime);
		return *this;
	}

	void Fun_test(int &);

protected:
	void baseInit();

	struct AdvBulletFuncSetting
	{
		AdvBulletFuncSetting(const int &f, const int &t) : funcType(f), startTime(t){}
		int funcType;
		int startTime;
	};

protected:
	// bullet data
	PhysicData m_bulletData;
	BulletStyle m_bulletStyle;
	float m_bulletSpeed;	// �����ٶ�
	Degree m_fireDegree;		// �������ĽǶ�

	// shooter data
	std::auto_ptr<IWalker> m_spWalker;
	int m_life;				// ����ʱ��
	Degree m_fireRange;		// ����Ƿ�Χ Degree
	Degree m_angleSpeed;	// ���ٶ�
	Degree m_angleAccel;	// �Ǽ��ٶ�
	int m_fireWays;			// ����·��	
	int m_frequency;		// ��������
	bool m_bFollowPlayer;	// �������Ľ��Ƿ�����Ի�

	Degree m_angleIncrease;	// ÿ·�ӵ��н�
	int m_counter;			// ���ڼ�����
	std::vector<AdvBulletFuncSetting> bulletFunc;
	MyTimer mytimer;
	timerFunc funcList[6];
};

#endif
