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
	int getPixel(int x, int y);			// ȡ�û�����ָ��λ�õ�����
	int getPixel(const LPoint& point);
	void setDrawScreen(DrawScreen drawScreen);	// ���û���Ŀ��
	void setDrawScreen(int hScreenGraph);

public:	// Dx��ʼ��ǰ����
	void setGraphMode(int ScreenSizeX, int ScreenSizeY, int ColorBitDepth, int RefreshRate = 60);	// ȡ�õ�ǰ��ͼ��ģʽ���ֱ��ʵȣ�
	void setGraphMode(const LPoint& point, int ColorBitDepth, int RefreshRate = 60);
	void setWaitVSync(bool bVSync);
	bool getWaitVSync();

public: // other
	void screenFlip();	// ���������彻����ǰ̨
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
