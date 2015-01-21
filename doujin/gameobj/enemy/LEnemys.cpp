#include "stdafx.h"
#include "LEnemys.h"

LEnemy* LEnemys::Add()
{
	LEnemy* pEnemy = new LEnemy(nullptr);
	m_thisList.push_back(pEnemy);
	return pEnemy;
}
