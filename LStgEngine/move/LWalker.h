#ifndef __LWALKER_H__
#define __LWALKER_H__

typedef destory_ptr<IWalker> WalkerPtr;
class LWalker : public IWalker
{
public:
	LWalker() = default;
	virtual ~LWalker() {}
	virtual void destory() override { delete this; }
	virtual void nextStep(PhysicData& data) override;

	static WalkerPtr CreateStableWalker();
	static WalkerPtr CreatePhysicWalker();
	static WalkerPtr CreatePathWalker(uint id = 0);
	static WalkerPtr CreateControlledWalker();
	static WalkerPtr CreateFollowWalker(IGameObject* pTarget);

protected:
	static WalkerPtr CreateWalker(WalkerType type);	// 不建议用

};

#endif // __LWALKER_H__