#ifndef __LPATHNODES_H__
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

	typedef NodeList::iterator iterator;
	typedef NodeList::const_iterator const_iterator;
	iterator begin() { return m_nodes.begin(); }
	iterator end() { return m_nodes.end(); }
	const_iterator cbegin() const { return m_nodes.cbegin(); }
	const_iterator cend() const { return m_nodes.cend(); }

	uint size() const { return m_nodes.size(); }
	bool empty() const { return m_nodes.empty(); }
	const LString& getName() const { return m_name; }
	uint getID() const { return m_id; }

protected:
	LPathNode* AddEmptyNode(uint frames);
	LLinePathNode* AddLineNode(const Vector2& detla, uint frames);
	LSinePathNode* AddSineNode(const Vector2& detla, const Vector2& scale, uint frames);
	void setID(uint id) { m_id = id; }
	void setName(const LString& name) { m_name = name; }
	void clear();

	friend class LPathSet;

private:
	LPathNodes(const LPathNodes& other) = delete;
	void operator=(const LPathNodes& other) = delete;

private:
	uint m_id;
	NodeList m_nodes;
	LString m_name;
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
	virtual ~LPathNode() {};

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame) const;
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
	virtual ~LLinePathNode() {};

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame) const override;
	virtual Type type() const override { return LineNode; }

private:
	Vector2 m_speed;	// 速度
	Vector2	m_detla;	// 相对移动位置（用于校正等）
};

// 正弦曲线移动
class LSinePathNode : public LPathNode
{
public:
	LSinePathNode(const Vector2& detla, const Vector2& scale, uint frames);
	virtual ~LSinePathNode() {};

	virtual Vector2 exec(const Vector2& beginPos, uint curFrame) const override;
	virtual Type type() const override { return SineNode; }

private:
	Vector2	m_detla;
	Vector2	m_scale;
	Vector2	m_endPos;
	float	m_fSpeed;
	Radian	m_dir;
};

#endif // __LPATHNODES_H__