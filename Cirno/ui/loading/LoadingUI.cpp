#include "stdafx.h"
#include "LoadingUI.h"
#include "LAssets.h"
#include "LPainter.h"
#include "ui/LUIImage.h"

LoadingUI::LoadingUI(LUIObjBase* parent, bool bAutoDel)
	: LUIObjBase(parent, bAutoDel)
{
	LAssets* pAssets = Engine::assets();

	LGraphHandle hGB = pAssets->GetTexture(__T("sig"));
	LUIImage* pBackground = new LUIImage(hGB, this, true);

	LGraphHandles txLoading = pAssets->GetSubGraphGroup(__T("加载中"));
	LUIFlashImage* pMajorText = new LUIFlashImage(txLoading[0], this, true);
	pMajorText->setFlash(90);

	LUIFlashImage* pMinorText = new LUIFlashImage(txLoading[1], this, true);
	pMinorText->setFlash(60);
	pMinorText->setPos(30, 30);

	m_snow = pAssets->GetSubGraphGroup(__T("加载雪花"))[0];
}

LoadingUI::~LoadingUI()
{
}

void LoadingUI::Draw(LPainter& painter)
{
	LUIObjBase::Draw(painter);
}
