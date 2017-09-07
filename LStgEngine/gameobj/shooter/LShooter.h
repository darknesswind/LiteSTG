#ifndef _SHOOTER_H_
#define _SHOOTER_H_
#pragma once
#include "LGameObject.h"

class LWalker;
class LBulletStyle;
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
	virtual void Update() override;
	virtual void draw(LPainter&) override {}
	virtual const Vector2& GetPosition() override { return m_phyData.position; }

	const Vector2&	position() const { return m_phyData.position; }
	Vector2&		position() { return m_phyData.position; }
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
	void setBulletData(const PhysicData& bulletData);
	void setFireSpeed(Vector2 speed);// ��ʼ����ٶ�
	void setBulletFriction(float friction) { m_bulletData.friction = friction; }
	void setBulletAcceleration(Vector2 gravitation) { m_bulletData.acceleration = gravitation; }
	void setBulletStyle(LBulletStyle* style) { m_pBulletStyle = style; }

protected:
	void baseInit();

protected:
	PhysicData m_phyData;
	// bullet data
	PhysicData m_bulletData;
	LBulletStyle* m_pBulletStyle;
	float m_bulletSpeed;	// �����ٶ�
	Degree m_fireDegree;		// �������ĽǶ�

	// shooter data
	destory_ptr<IWalker> m_spWalker;
	int m_life;				// ����ʱ��
	Degree m_fireRange;		// ����Ƿ�Χ Degree
	Degree m_angleSpeed;	// ���ٶ�
	Degree m_angleAccel;	// �Ǽ��ٶ�
	int m_fireWays;			// ����·��	
	int m_frequency;		// ��������
	bool m_bFollowPlayer;	// �������Ľ��Ƿ�����Ի�

	Degree m_angleIncrease;	// ÿ·�ӵ��н�
	int m_counter;			// ���ڼ�����
};

#endif
