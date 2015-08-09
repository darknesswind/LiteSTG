#include "stdafx.h"
#include "resource.h"
#include "DxLib.h"
#include "Graph.h"

namespace NS_FileName
{
	const auto IMG_BG_L = _T("resource\\image\\front\\bg_left.png");
	const auto IMG_BG_R = _T("resource\\image\\front\\bg_right.png");
	const auto IMG_BG_T = _T("resource\\image\\front\\bg_top.png");
	const auto IMG_BG_B = _T("resource\\image\\front\\bg_bottom.png");

	const auto IMG_TITLE = _T("resource\\image\\title\\title.png");
	const auto IMG_SELECT = _T("resource\\image\\title\\select.png");

	const auto IMG_BULLET1 = _T("resource\\image\\bullet\\etama.png");
	const auto IMG_BULLET2 = _T("resource\\image\\bullet\\etama2.png");
	const auto IMG_BULLET3 = _T("resource\\image\\bullet\\etama6.png");
	const auto IMG_BULLET4 = _T("resource\\image\\bullet\\etama9.png");

	const auto IMG_PLAYER0 = _T("resource\\image\\player\\pl00.png");

	const auto IMG_ENEMY = _T("resource\\image\\enemy\\enemy.png");

	const auto SOUND_MISS = _T("resource\\sound\\miss.mp3");
}
using namespace NS_FileName;
using namespace NS_Resource;

Resource::Resource()
{

}

#pragma region 静态成员定义
int Resource::frameBackground[4];
int Resource::soundEffect[1];
int Resource::titleImage[2];
int Resource::titleSelection[10];
int Resource::_hitBox;
int Resource::_player[24];
int Resource::_attack[3];
int Resource::hEnemyImg[6][12];
int Resource::hBulletImg[18][16];
int Resource::hEffect[8];
#pragma endregion 静态成员定义

bool Resource::loadPrimaryGameResource()
{

#pragma region 框架背景
	frameBackground[BG_Left] = DxLib::LoadGraph(IMG_BG_L);
	frameBackground[BG_Top] = DxLib::LoadGraph(IMG_BG_T);
	frameBackground[BG_Right] = DxLib::LoadGraph(IMG_BG_R);
	frameBackground[BG_Bottom] = DxLib::LoadGraph(IMG_BG_B);
#pragma endregion 框架背景

#pragma region 标题画面
	titleImage[Title_BG] = DxLib::LoadGraph(IMG_TITLE);
	DxLib::LoadDivGraph(IMG_SELECT, 10, 1, 10, 192, 32, titleSelection);
#pragma endregion 标题画面	

#pragma region 敌人
	for (int i = 0; i < 4; ++i)
	{
		LoadDivGraphEx(IMG_ENEMY, 0, 256, 12, 12, 4, 32, 32, hEnemyImg[i]);
	}
	LoadDivGraphEx(IMG_ENEMY, 0, 384, 8, 8, 1, 64, 64, hEnemyImg[5]);
	LoadDivGraphEx(IMG_ENEMY, 384, 256, 4, 2, 2, 64, 64, &hEnemyImg[5][8]);
#pragma endregion 敌人

#pragma region 弹幕
	const int px16_num = 11;
	const int px32_num = 5;
	const int px64_num = 1;
	const int ray_num = 1;
	for (int i = 0; i < px16_num; ++i)
	{
		LoadDivGraphEx(IMG_BULLET1, 0, 16 * i, 16, 16, 1, 16, 16, hBulletImg[i]);
	}
	for (int i = 0; i < px32_num; ++i)
	{
		int* buf = hBulletImg[px16_num + i];
		LoadDivGraphEx(IMG_BULLET3, 0, 32 * i, 8, 8, 1, 32, 32, buf);
		for (int j = 15; j > 0; --j)
		{
			buf[j] = buf[j / 2];
		}
	}
	for (int i = 0; i < px64_num; ++i)
	{
		int* buf = hBulletImg[px16_num + px32_num + i];
		LoadDivGraphEx(IMG_BULLET3, 0, 32 * 6, 4, 4, 1, 64, 64, buf);
		for (int j = 15; j > 0; --j)
		{
			buf[j] = buf[j / 4];
		}
	}
	LoadDivGraphEx(IMG_BULLET3, 0, 32 * 5, 8, 8, 1, 32, 32, hEffect);
	DxLib::LoadDivGraph(IMG_BULLET4, 16, 1, 16, 256, 16, hBulletImg[px16_num + px32_num + px64_num]);
#pragma endregion 弹幕

	soundEffect[SE_Miss] = DxLib::LoadSoundMem(SOUND_MISS);
	return true;
}


bool Resource::loadPlayerResource(PlayerID pid)
{
	int hTemp = DxLib::LoadGraph(IMG_BULLET2);
	_hitBox = DxLib::DerivationGraph(0, 16, 64, 64, hTemp);
	DxLib::DeleteGraph(hTemp);
	LoadDivGraphEx(IMG_PLAYER0, 0, 0, 24, 8, 3, 32, 48, _player);
	LoadDivGraphEx(IMG_PLAYER0, 0, 4 * 48 - 16, 3, 3, 1, 64, 16, _attack);

	return true;
}



