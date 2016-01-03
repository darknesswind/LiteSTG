#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#pragma once

class LEnemy;
class EnemyFactory
{
	EnemyFactory(void);
public:
	static LEnemy* getEnemy();

private:
	std::vector<LEnemy> m_template;
};

#endif