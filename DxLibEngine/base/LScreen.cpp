#include "stdafx.h"
#include "LScreen.h"
#include "LPoint.h"

LScreen LScreen::Instance;

LScreen::LScreen()
{
}

LScreen::~LScreen()
{
}

int LScreen::getPixel(int x, int y)
{
	return DxLib::GetPixel(x, y);
}

int LScreen::getPixel(const LPoint& point)
{
	return DxLib::GetPixel(point.x(), point.y());
}

void LScreen::setGraphMode(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate /*= 60*/)
{
	CheckRes(DxLib::SetGraphMode(ScreenSizeX, ScreenSizeY, ColorBitDepth, RefreshRate));
}

void LScreen::setGraphMode(const LPoint& point, int ColorBitDepth, int RefreshRate /*= 60*/)
{
	CheckRes(DxLib::SetGraphMode(point.x(), point.y(), ColorBitDepth, RefreshRate));
}

void LScreen::setDrawScreen(DrawScreen drawScreen)
{
	CheckRes(DxLib::SetDrawScreen((int)drawScreen));
}

void LScreen::setDrawScreen(int hScreenGraph)
{
	CheckRes(DxLib::SetDrawScreen(hScreenGraph));
}

void LScreen::screenFlip()
{
	DxLib::ScreenFlip();
}

void LScreen::setWaitVSync(bool bVSync)
{
	CheckRes(DxLib::SetWaitVSyncFlag(bVSync));
}

bool LScreen::getWaitVSync()
{
	return DxLib::GetWaitVSyncFlag();
}

void LScreen::clearDrawScreen()
{
	CheckRes(DxLib::ClearDrawScreen());
}
