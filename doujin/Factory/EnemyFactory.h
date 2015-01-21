#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#pragma once
class LEnemy;
class EnemyFactory
{
	EnemyFactory(void);
public:
	static LEnemy* getEnemy();
};

#endif