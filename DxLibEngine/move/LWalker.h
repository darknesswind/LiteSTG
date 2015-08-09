#ifndef __LWALKER_H__
#define __LWALKER_H__

class LPhysicWalker;
class LPathWalker;
class LControlledWalker;
class LFollowWalker;
class LWalker : public IWalker
{
public:
	LWalker() = default;
	virtual void destory() override { delete this; }
	virtual void nextStep(PhysicData& data) override;

	static IWalker* CreateWalker(WalkerType type);
	static LWalker* CreateStableWalker();
	static LPhysicWalker* CreatePhysicWalker();
	static LPathWalker* CreatePathWalker(uint id = 0);
	static LControlledWalker* CreateControlledWalker();
	static LFollowWalker* CreateFollowWalker();

protected:
	virtual ~LWalker() {}

};

#endif // __LWALKER_H__