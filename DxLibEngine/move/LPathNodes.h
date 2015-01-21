﻿#ifndef __LPATHNODES_H__
#define __LPATHNODES_H__
#include "LWalker.h"

class LPathNode;
class LLinePathNode;
class LSinePathNode;
class LPathNodes
{
	typedef std::vector<LPathNode*> NodeList;
public:
	LPathNodes();
	~LPathNodes();

	LPathNode* AddEmptyNode(uint frames);
	LLinePathNode* AddLineNode(const Vector2& detla, uint frames);
	LSinePathNode* AddSineNode(const Vector2& detla, const Vector2& scale, uint frames);

	typedef NodeList::iterator iterator;
	iterator begin() { return m_nodes.begin(); }
	iterator end() { return m_nodes.end(); }
	uint size() const { return m_nodes.size(); }
	bool empty() const { return m_nodes.empty(); }

private:
	NodeList m_nodes;
};

// 空节点（待机）
class LPathNode
{
public:
	enum Type
	{
		EmptyNode,
		LineNode,
		SineNode,
	};
public:
	LPathNode(uint frames);
	~LPathNode() = default;

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame);
	virtual Type type() const { return EmptyNode; }

	uint getFrames() const { return m_frames; }
	void setFrames(uint frames) { m_frames = frames; }

protected:
	uint	m_frames;	// 持续时间
};  

// 直线移动
class LLinePathNode : public LPathNode
{
public:
	LLinePathNode(const Vector2& detla, uint frames);
	~LLinePathNode() = default;

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame);
	virtual Type type() const { return LineNode; }

private:
	Vector2 m_speed;	// 速度
	Vector2	m_detla;	// 相对移动位置（用于校正等）
};

// 正弦曲线移动
class LSinePathNode : public LPathNode
{
public:
	LSinePathNode(const Vector2& detla, const Vector2& scale, uint frames);
	~LSinePathNode() = default;

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame);
	virtual Type type() const { return SineNode; }

private:
	Vector2	m_detla;
	Vector2	m_scale;
	float	m_fSpeed;
	Radian	m_dir;
};

#endif // __LPATHNODES_H__