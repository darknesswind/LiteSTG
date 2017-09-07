#ifndef __LGAMEOBJECT_H__
#define __LGAMEOBJECT_H__
#include "render/LPainter.h"
#include "physic/physic.h"

class LGameObject : public IGameObject
{
public:
	LGameObject(IGameObject* pParent = nullptr);
	virtual ~LGameObject() {}

public: // IGameObject
	bool	IsValid() const	final							{ return m_bValid; }
	void	SetValid(bool bValid) final						{ m_bValid = bValid; }
	const RenderArgument& GetRenderArgument() const final	{ return m_renderArg; }
	IGameObject* GetParent() final							{ return m_pParent; }
// 	const Vector2& GetPosition() = 0;

public:
	const RenderArgument& renderArg() const { return m_renderArg; }

protected:
	bool m_bValid;
	IGameObject* m_pParent;
	RenderArgument m_renderArg;
};

class LCollideObject : public LGameObject
{
public:
	LCollideObject(IGameObject* pParent = nullptr)
		: LGameObject(pParent)
	{
	}

	const Vector2& GetPosition() override final { return m_phyData.position; }

public:
	void DrawHitBox(LPainter& painter);

public:
	const PhysicData& physicData() const { return m_phyData; }
	const Vector2&	position() const { return m_phyData.position; }
	Vector2&		position() { return m_phyData.position; }

	const EntityData& entity() const { return m_entity; }
	bool CollideWith(const LCollideObject& other);

public:
	bool CollideWithCircle(const LCollideObject& other) const;
	bool CollideWithRectangle(const LCollideObject& other) const;
	bool CollideWithOffsetCircle(const LCollideObject& other) const;
	bool CollideWithOffsetRectangle(const LCollideObject& other) const;

private:
	template <bool c_bThisOffset, bool c_bOtherOffset>
	bool CircleCollideWithCircle(const LCollideObject& other) const;
	template <bool c_bThisOffset, bool c_bOtherOffset>
	bool RectCollideWithCircle(const LCollideObject& rect) const;
	template <bool c_bThisOffset, bool c_bOtherOffset>
	bool RectCollideWithRect(const LCollideObject& other) const;

protected:
	PhysicData m_phyData;
	EntityData m_entity;
	LRgb m_hitboxClr;
};

#endif