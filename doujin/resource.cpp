#include "stdafx.h"
#include "resource.h"
#include "DxLib.h"
#include "Graph.h"

namespace NS_FileName
{
	const auto IMG_SELECT = _T("resource\\image\\title\\select.png");

	const auto IMG_BULLET1 = _T("resource\\image\\bullet\\etama.png");
	const auto IMG_BULLET2 = _T("resource\\image\\bullet\\etama2.png");
	const auto IMG_BULLET3 = _T("resource\\image\\bullet\\etama6.png");
	const auto IMG_BULLET4 = _T("resource\\image\\bullet\\etama9.png");

	const auto IMG_PLAYER0 = _T("resource\\image\\player\\pl00.png");

	const auto IMG_ENEMY = _T("resource\\image\\enemy\\enemy.png");
}
using namespace NS_FileName;
using namespace NS_Resource;

Resource::Resource()
{

}

#pragma region 静态成员定义
int Resource::_hitBox;
int Resource::_player[24];
int Resource::_attack[3];
int Resource::hBulletImg[18][16];
int Resource::hEffect[8];
#pragma endregion 静态成员定义

bool Resource::loadPrimaryGameResource()
{
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
	DxLib::LoadDivGraph(IMG_BULLET4, 16, 1, 16, 256, 16, hBulletImg[px16_num + px32_num + px64_num]);

	LoadDivGraphEx(IMG_BULLET3, 0, 32 * 5, 8, 8, 1, 32, 32, hEffect);
#pragma endregion 弹幕

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



