#include "stdafx.h"
#include "ShooterFactory.h"
#include "enemy/LEnemy.h"
#include "shooter/LShooters.h"
#include "shooter/LShooter.h"
#include "shooter/LRayShooter.h"
#include "shooter/LSegShooter.h"
#include "bullet/LBulletStyles.h"

void ShooterFactory::createNWaysFlower(LEnemy* pEnemy, int difficulty)
{	
	LShooter *pShooter = pEnemy->GetShooters()->AddNormalShooter(pEnemy);
	pShooter->setBulletStyle(CirnoEngine::bulletStyles()->getStyle(__T("Á×µ¯")));
	(*pShooter).setFireWays(6).setFireFreq(8).setAngleSpeed(Degree(3));
	pShooter->setBulletAcceleration(Vector2(0, 0.01));

	pShooter = pEnemy->GetShooters()->AddRayShooter(pEnemy);
	pShooter->setFollowPlayer(true);
	(*pShooter).setFireWays(1).setFireFreq(32).setAngleSpeed(Degree(-64));
}

void ShooterFactory::createPlayerSnipe(LEnemy* pEnemy, int difficulty)
{
	LShooter *pShooter = pEnemy->GetShooters()->AddNormalShooter(pEnemy);
	pShooter->setBulletStyle(CirnoEngine::bulletStyles()->getStyle(__T("Ð¡Óñ2")));
	pShooter->setFollowPlayer(true);
}

void ShooterFactory::createTest(LEnemy* pEnemy, int difficulty)
{
	LRayShooter *pShooter = pEnemy->GetShooters()->AddRayShooter(pEnemy);
	pShooter->setWarningTime(180);
	pShooter->setDurationTime(120);
	pShooter->setWidthExtRange(1);
	pShooter->setLengthExtRange(30);
	pShooter->setTurnFlag(true);
	pShooter->setBulletStyle(CirnoEngine::bulletStyles()->getStyle(__T("µûµ¯")));
	(*pShooter).setFollowPlayer(true).setFireWays(5).setFireRange(Degree(90));
}