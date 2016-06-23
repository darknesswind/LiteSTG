#include "stdafx.h"
#include "baseFrame.h"
#include "render/LPainter.h"
#include "LAssets.h"
#include "ui/LUIImage.h"

BaseFrame::BaseFrame()
{
	LAssets* pAssets = LStgEngine::assets();
	auto paneLR = pAssets->GetSubGraphGroup(_T("主面板左右"));
	auto paneTB = pAssets->GetSubGraphGroup(_T("主面板上下"));

	LUIImage* pPaneLeft = new LUIImage(paneLR[0]);
	LUIImage* pPaneRight = new LUIImage(paneLR[1]);
	LUIImage* pPaneTop = new LUIImage(paneTB[0]);
	LUIImage* pPaneBottom = new LUIImage(paneTB[1]);

	pPaneRight->setPos(pPaneLeft->width() + pPaneTop->width(), 0);
	pPaneTop->setPos(pPaneLeft->width(), 0);
	pPaneBottom->setPos(pPaneLeft->width(), 480 - pPaneBottom->height());

	pushChild(pPaneLeft, true);
	pushChild(pPaneRight, true);
	pushChild(pPaneTop, true);
	pushChild(pPaneBottom, true);
}
