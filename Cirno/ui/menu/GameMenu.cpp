#include "stdafx.h"
#include "GameMenu.h"
#include "LAssets.h"
#include "ui/LUIMenu.h"
#include "ui/LUIImage.h"

enum MainMenuEnum
{
	Menu_Start,
	Menu_Replay,
	Menu_Result,
	Menu_Music,
	Menu_Option,
	Menu_Quit,
	Menu_Count
};

class MainMenu : public LUIMenu
{
public:
	using LUIMenu::LUIMenu;

	void OnOk() override
	{
		switch (m_activeIdx)
		{
		case Menu_Start:
			CirnoEngine::engine()->ChangeState(GameState::Test);
			break;
		case Menu_Quit:
			CirnoEngine::engine()->setEndFlag(true);
			break;
		default: break;
		}
	}

	void OnCancel() override
	{
		m_activeIdx = Menu_Quit;
	}
};

GameMenu::GameMenu(LUIObjBase* parent /*= nullptr*/)
	: LUIObjBase(parent)
{
	LGraphHandle hTitleBG = LEngine::assets()->GetTexture(_T("select00"));
	pushChild(new LUIImage(hTitleBG), true);

	LGraphHandle hCirno = LEngine::assets()->GetTexture(_T("title00a"));
	pushChild(new LUIImage(hCirno), true);

	LGraphHandle hLogo = LEngine::assets()->GetTexture(_T("title_logo"));
	pushChild(new LUIImage(hLogo), true)->setPos(200, 0);

	LGraphHandle hCopyright = LEngine::assets()->GetTexture(_T("copyright"));
	pushChild(new LUIImage(hCopyright), true)->setPos(0, 460);

	LGraphHandle hVersion = LEngine::assets()->GetTexture(_T("title_ver"));
	pushChild(new LUIImage(hVersion), true)->setPos(320, 440);

	const LGraphHandles& selItems = LEngine::assets()->GetSubGraphGroup(_T("主菜单白"));
	const LGraphHandles& unselItems = LEngine::assets()->GetSubGraphGroup(_T("主菜单蓝"));

	LUIMenu* pMenu = (LUIMenu*)pushChild(new LUIMenu(), true);
	for (int i = 0; i < Menu_Count; ++i)
	{
		pMenu->addMenuItem(selItems[i], unselItems[i]);
	}
	pMenu->setPos(450, 300);
}
