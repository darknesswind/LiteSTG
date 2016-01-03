#ifndef __LGAMEOBJECT_H__
#define __LGAMEOBJECT_H__
#include "LRgb.h"

class LGameObject : public IGameObject
{
public:
	LGameObject(IGameObject* pParent = nullptr);
	virtual ~LGameObject() {}

public: // IGameObject
	virtual bool	IsValid() const	final							{ return m_bValid; }
	virtual void	SetValid(bool bValid) final						{ m_bValid = bValid; }
	virtual uint GetSortKey() const override;
	virtual const RenderArgument& GetRenderArgument() const final	{ return m_renderArg; }
	virtual IGameObject* GetParent() final							{ return m_pParent; }
	virtual const Vector2& GetPosition() final						{ return m_phyData.position; }

public:
	const RenderArgument& renderArg() const { return m_renderArg; }
	const PhysicData& physicData() const	{ return m_phyData; }
	const Vector2&	position() const		{ return m_phyData.position; }
	Vector2&		position()				{ return m_phyData.position; }

protected:
	bool m_bValid;
	IGameObject* m_pParent;
	RenderArgument m_renderArg;
	PhysicData m_phyData;
};

class LCollideObject : public LGameObject
{
public:
	LCollideObject(IGameObject* pParent = nullptr)
		: LGameObject(pParent)
	{
	}

public:
	void DrawHitBox(LPainter& painter);

public:
	const EntityData& entity() const { return m_entity; }
	bool CollideWith(const LCollideObject& other);

public:
	bool CollideWithCircle(const LCollideObject& other) const;
	bool CollideWithRectangle(const LCollideObject& other) const;

protected:
	EntityData m_entity;
	LRgb m_hitboxClr;
};
#endif