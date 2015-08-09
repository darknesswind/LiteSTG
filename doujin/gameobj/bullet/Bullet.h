#ifndef _BULLET_H_
#define _BULLET_H_
#pragma once
#include "LGameObject.h"
#include "MyTimer.h"
#include "interdef.h"
#include "Factory/EntityFactory.h"

class Entity;

// 子弹的类
class Bullet : public LGameObject
{
public:
	explicit Bullet(IGameObject* pParent);
	virtual ~Bullet() = default;

public:
	void*	operator new(size_t size);
	void*	operator new[](size_t size) = delete;
	void	operator delete(void* pObject, size_t size);
	void	operator delete[](void*) = delete;

public: // IGameObjBase
	virtual void	Update() override;
	virtual void	Draw(LPainter& painter) override;
	virtual void	DrawHitBox(LPainter& painter) override;
	virtual const LGraphHandle GetGraphHandle() const override;

public: // Bullet
	virtual BulletType GetType() const { return BulletType::Generic; }

public:
	void	setData(const PhysicData& data);
	void	setPosition(const Vector2& pos);
	void	setSpeed(const Vector2& speed);
	void	setSpeed(float speed, Degree direction);
	void	setSpeedValue(float speed)					{ m_phyData.speed = speed * m_phyData.speed.normalized(); }
	void	setFriction(float friction)					{ m_phyData.friction = friction; }
	void	setAcceleration(float accel, Degree deg)	{ m_phyData.acceleration.InitFromPolar(accel, deg); }
	void	setAcceleration(float accel, Radian rad)	{ m_phyData.acceleration.InitFromPolar(accel, rad); }

	const	BulletStyle& style() const					{ return m_style; }
	void	setBulletClass(const BulletClass type);
	void	setBulletColor(int color)					{ m_style.color = color; }
	void	setStyle(const BulletStyle &style);

	void	Rotate(Radian rad);
	void	SetEntity(const Entity* entity)				{ m_pEntity = entity; }
	void	SetLife(int life)							{ m_life = life; }
	void	setWalkerType(WalkerType type);

	template<class T>
	Degree degreeBetween(const T& other)
	{
		return (other.position() - position()).degree();
	}
	template<class T>
	Radian radianBetween(const T& other)
	{
		return (other.position() - position()).radian();
	}


	// Timer相关
	void	setAdvBulletFunc(uint funcType, int startTime)
	{
		if (funcType < m_funcList.size())
			mytimer.setup(m_funcList[funcType], startTime);
	}
	void	Fun_test(int &);
	void	Fun_turnToPlayer(int &);

protected:
	void updateEntity() { m_pEntity = EntityFactory::getBulletEntity(m_style.type);	}
	void updateRadian()	{ m_phyData.radian = m_phyData.speed.radian(); }

protected:
	int		m_life;
	BulletStyle	m_style;

	MyTimer mytimer;
	std::vector<timerFunc> m_funcList;
	destory_ptr<IWalker> m_spWalker;
	const Entity* m_pEntity;	
};

#endif
