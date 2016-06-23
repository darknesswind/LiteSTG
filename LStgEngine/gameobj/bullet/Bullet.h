#ifndef _BULLET_H_
#define _BULLET_H_
#pragma once
#include "LGameObject.h"

class LBulletStyle;
class Bullet : public LCollideObject
{
public:
	explicit Bullet(IGameObject* pParent);
	virtual ~Bullet() = default;

public:
	void*	operator new(size_t size);
	void	operator delete(void* pObject, size_t size);

	void*	operator new[](size_t size) = delete;
	void	operator delete[](void*) = delete;

public: // IGameObjBase
	virtual void	Update() override;
	virtual void	draw(LPainter& painter) override;

public: // Bullet
	virtual BulletType GetType() const { return BulletType::Generic; }

public:
	void	setData(const PhysicData& data);
	void	setPosition(const Vector2& pos);
	void	setSpeed(const Vector2& speed);
	void	setSpeed(float speed, Degree direction);
	void	setSpeedValue(float speed)					{ m_phyData.speed = speed * m_phyData.speed.normalized(); }
	void	setFriction(float friction)					{ m_phyData.friction = friction; }
	void	setAcceleration(float accel, Degree deg)	{ m_phyData.acceleration.setPolar(accel, deg); }
	void	setAcceleration(float accel, Radian rad)	{ m_phyData.acceleration.setPolar(accel, rad); }

	void	setStyle(LBulletStyle* pStyle, uint elem);

	void	Rotate(Radian rad);
	void	SetEntity(const EntityData& entity)			{ m_entity = entity; }
	void	SetLife(int life)							{ m_life = life; }

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

protected:
	void updateRadian()	{ m_phyData.radian = m_phyData.speed.radian(); }

protected:
	int		m_life;
	LBulletVisual	m_visual;
	destory_ptr<IWalker> m_spWalker;
};

#endif
