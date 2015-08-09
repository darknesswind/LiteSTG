#ifndef __LPATHWALKER_H__
#define __LPATHWALKER_H__
#include "LWalker.h"
#include "LPathNodes.h"

class LPathNode;
class LPathWalker : public LWalker
{
public:
	LPathWalker();
	LPathWalker(uint id);
	~LPathWalker() override;

	void nextStep(PhysicData& data) override;
	void setPath(uint id);

private:
	const LPathNodes* m_pPath;
	LPathNodes::const_iterator m_curNode;
	Vector2 m_nodeBegin;
	uint m_curFrame;
};

#endif // __LPATHWALKER_H__