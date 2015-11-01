#include "stdafx.h"
#include "LBulletStyles.h"
#include "LAssets.h"

LBulletStyles::LBulletStyles()
{

}

LBulletStyles::~LBulletStyles()
{

}

void LBulletStyles::LoadBulletSetting()
{
	LCsvTablePtr pTable = LEngine::assets()->LoadCSV(_T("resource\\data\\bullet.csv"));

}
