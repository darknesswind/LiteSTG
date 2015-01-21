//////////////////////////////////////////////////////////////////////////
//	这里把拥有坐标的对象称为精灵
//////////////////////////////////////////////////////////////////////////
#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include "Vector2.hpp"
#include "interfaceDef.h"
#include "Animation/AnimationManager.h"
#include <vector>

class Sprite : public IComponent
	, public IAnimationSrcHost
{
public:
	explicit Sprite(void)
		: m_parent(0), m_bValid(true)
	{
		m_id = ++idCount;
	}
	virtual ~Sprite(void);

public: // IAnimationDataHost
	bool isValid() const { return m_bValid; }

public:
	const float x() const { return m_position.x(); }
	const float y() const { return m_position.y(); }
	virtual const Vector2& position() const	{ return m_position; }
	void setPosition(const Vector2& pos) { m_position = pos; }

	const int id() const { return m_id; }
	const int parentId() const { return m_parent; }
	void setParentId(int parent) { m_parent = parent; }

	void setValid(bool bValid) { m_bValid = bValid; }

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

public:
	void bindPositionWith(const Sprite& src);
	void bindPositionTo(Sprite& dest);

private:
	DeleteFunc(Sprite(const Sprite&));
	DeleteFunc(void operator=(const Sprite&));

protected:
	Vector2 m_position;
	int m_id;
	int m_parent;
	bool m_bValid;
	AnimationManager m_animations;

private:
	static int idCount;

};
#endif