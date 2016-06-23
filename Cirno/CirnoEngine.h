#pragma once
#include "LStgEngine.h"

class GameMenu;
class BaseFrame;
class CirnoEngine : public LStgEngine
{
	typedef LStgEngine Base;
	friend class EngineStateHandle;
public:
	CirnoEngine();
	~CirnoEngine();

public:
	static CirnoEngine* engine() { return static_cast<CirnoEngine*>(s_pEngine); }

public:

protected:
	virtual bool Init() override;
	virtual void OnAsyncLoading() override;
	virtual void Update() override;

	void OnEnterState(uint state) override;
	void OnExecState(uint state) override;
	bool OnExitState(uint state) override;

private:
	std::unique_ptr<GameMenu> m_spMainMenu;
	std::unique_ptr<BaseFrame> m_spPane;
};
