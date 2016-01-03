#ifndef __LSCREEN_H__
#define __LSCREEN_H__
#pragma once

#define Screen LScreen::Instance

#pragma region pre-define
class LPoint;
enum class DrawScreen : uint;

#pragma endregion

class LScreen
{
public:
	static LScreen Instance;
	~LScreen();

public:
	int getPixel(int x, int y);			// 取得画面上指定位置的像素
	int getPixel(const LPoint& point);
	void setDrawScreen(DrawScreen drawScreen);	// 设置绘制目标
	void setDrawScreen(int hScreenGraph);

public:	// Dx初始化前调用
	void setGraphMode(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate = 60);	// 取得当前的图形模式（分辨率等）
	void setGraphMode(const LPoint& point, int ColorBitDepth, int RefreshRate = 60);
	void setWaitVSync(bool bVSync);
	bool getWaitVSync();

public: // other
	void screenFlip();	// 将离屏缓冲交换到前台
	void clearDrawScreen();

private:
	LScreen();

private:
	LScreen(const LScreen&) = delete;
	void operator=(const LScreen&) = delete;
};

enum class DrawScreen : uint
{
	dsHandle,
	dsFront = 0xfffffffc,
	dsBack = 0xfffffffe,
	dsWork = 0xfffffffd,
	dsTempFront = 0xfffffffb,
};

#endif // !__LSCREEN_H__
