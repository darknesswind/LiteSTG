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
	virtual ~LWalker() {}
	virtual void nextStep(PhysicData& data);

	static IWalker* CreateWalker(WalkerType type);
	static LWalker* CreateStableWalker();
	static LPhysicWalker* CreatePhysicWalker();
	static LPathWalker* CreatePathWalker(uint id = 0);
	static LControlledWalker* CreateControlledWalker();
	static LFollowWalker* CreateFollowWalker();
private:

};

#endif // __LWALKER_H__