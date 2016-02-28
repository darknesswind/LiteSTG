#include "stdafx.h"
#include "LoadingUI.h"
#include "LAssets.h"
#include "LPainter.h"
#include "ui/LUIImage.h"

LoadingUI::LoadingUI(LUIObjBase* parent /*= nullptr*/)
	: LUIObjBase(parent)
{
	LAssets* pAssets = CirnoEngine::assets();

	LGraphHandle hGB = pAssets->GetTexture(__T("sig"));
	pushChild(new LUIImage(hGB), true);

	LGraphHandles txLoading = pAssets->GetSubGraphGroup(__T("加载中"));
	LUIImage* pMajorText = new LUIImage(txLoading[0]);
	pMajorText->setFlash(90);
	pMajorText->setPos(500, 440);
	pushChild(pMajorText, true);

	LUIImage* pMinorText = new LUIImage(txLoading[1]);
	pMinorText->setFlash(60);
	pMinorText->setPos(520, 450);
	pushChild(pMinorText, true);

	m_snow = pAssets->GetSubGraphGroup(__T("加载雪花"))[0];
}

LoadingUI::~LoadingUI()
{
}

void LoadingUI::Draw(LPainter& painter)
{
	LUIObjBase::Draw(painter);
}
