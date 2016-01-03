#pragma once
#include "tools/LRect.h"

class LRender;
class LUIObjBase : public IUIObject
{
public:
	LUIObjBase(LUIObjBase* parent = nullptr, bool bAutoDel = false);
	virtual ~LUIObjBase();

public:
	virtual uint GetSortKey() const override { return LHandle::hInvalid; }
	virtual const RenderArgument& GetRenderArgument() const override final { return m_renderArg; };
	virtual void Update() override;
	virtual void Draw(LPainter&) override;

public:
	LUIObjBase* parent()				{ return m_pParent; }
	const LUIObjBase* parent() const	{ return m_pParent; }
	bool addChild(LUIObjBase* pChild);
	bool removeChild(LUIObjBase* pChild);
	void clearChildren();
	
	bool autoDelete() const				{ return m_bAutoDelete; }
	void setAutoDelete(bool bAutoDel)	{ m_bAutoDelete = bAutoDel; }

	LPoint pos() const { return m_rect.pos(); }
	void setPos(int x, int y) { m_rect.setPos(x, y); }

protected:
	void commitRender(LRender* pRender);

protected:
	LUIObjBase* m_pParent;
	bool m_bAutoDelete;
	std::vector<LUIObjBase*> m_children;

	LRect m_rect;
	RenderArgument m_renderArg;
};

class LEmptyUI : public LUIObjBase
{
public:
	using LUIObjBase::LUIObjBase;
	~LEmptyUI() override = default;

	virtual void Update() override { }
	virtual void Draw(LPainter&) override { }
};

class LUIRoot : public LUIObjBase
{
public:
	using LUIObjBase::LUIObjBase;
	~LUIRoot() override = default;

	void commitRender();
private:

};