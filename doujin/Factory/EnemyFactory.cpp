#include "stdafx.h"
#include "EnemyFactory.h"
#include "ShooterFactory.h"
#include "enemy/LEnemy.h"

LEnemy* EnemyFactory::getEnemy()
{
	LEnemy *pEnemy = new LEnemy(nullptr, 0);
	ShooterFactory::createPlayerSnipe(pEnemy);
	return pEnemy;
}
