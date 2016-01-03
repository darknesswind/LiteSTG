#ifndef _SHOOTERFACTORY_H_
#define _SHOOTERFACTORY_H_
#pragma once

class LEnemy;

class ShooterFactory // ·¢ÉäÆ÷¹¤³§
{
	ShooterFactory(void);
public:
	static void createNWaysFlower(LEnemy* pEnemy, int difficulty = 1);
	static void createPlayerSnipe(LEnemy* pEnemy, int difficulty = 1);
	static void createTest(LEnemy* pEnemy, int difficulty = 1);
};
#endif