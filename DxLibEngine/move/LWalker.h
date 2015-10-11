#ifndef __LWALKER_H__
#define __LWALKER_H__

class LWalker : public IWalker
{
public:
	LWalker() = default;
	virtual ~LWalker() {}

	virtual void nextStep(PhysicData& data) override;

	static LWalker* CreateStableWalker();
	static LWalker* CreatePhysicWalker();
	static LWalker* CreatePathWalker(uint id = 0);
	static LWalker* CreateControlledWalker();
	static LWalker* CreateFollowWalker(IGameObject* pTarget);

protected:
	static LWalker* CreateWalker(WalkerType type);	// 不建议用

};

#endif // __LWALKER_H__