#pragma once
#include "LStgEngine.h"

class Engine : public LStgEngine
{
	typedef LStgEngine Base;
public:
	Engine();
	~Engine();

public:
	static Engine* engine() { return static_cast<Engine*>(s_pEngine); }

public:

protected:
	virtual void BeforeDxInit() override;
	virtual void PreLoad() override;
	virtual void OnLoading() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	void checkState();

private:
	std::unique_ptr<GameMenu> m_spGameMenu;
};
