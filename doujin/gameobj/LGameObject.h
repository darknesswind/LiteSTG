#ifndef __LGAMEOBJECT_H__
#define __LGAMEOBJECT_H__

class LGameObject : public IGameObject
{
public:
	LGameObject(IGameObject* pParent = nullptr);
	virtual ~LGameObject() = 0 {}

public: // IGameObject
	virtual void	DrawHitBox();
	virtual bool	IsValid() const			{ return m_bValid; }
	virtual void	SetValid(bool bValid)	{ m_bValid = bValid; }
	virtual const LGraphHandle GetGraphHandle() const;
	virtual const RenderArgument& GetRenderArgument() const { return m_renderArg; }
	virtual IGameObject* GetParent()		{ return m_pParent; }
	virtual const Vector2& GetPosition()	{ return m_phyData.position; }

public:
	const RenderArgument& renderArg() const { return m_renderArg; }
	const PhysicData& physicData() const	{ return m_phyData; }
	const Vector2&	position() const	{ return m_phyData.position; }
	Vector2&		position() { return m_phyData.position; }

protected:
	PhysicData m_phyData;
	RenderArgument m_renderArg;
	IGameObject* m_pParent;
	bool m_bValid;
};

#endif