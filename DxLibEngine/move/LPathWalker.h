#ifndef __LPATHWALKER_H__
#define __LPATHWALKER_H__
#include "LWalker.h"
#include "LPathNodes.h"

class LPathNode;
class LPathWalker : public LWalker
{
public:
	LPathWalker();
	~LPathWalker();

	void nextStep(PhysicData& data);

private:
	LPathNodes m_nodes;
	LPathNodes::iterator m_curNode;
	Vector2 m_nodeBegin;
	uint m_curFrame;
};

#endif // __LPATHWALKER_H__