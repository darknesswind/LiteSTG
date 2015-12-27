#ifndef __LENEMYs_H__
#define __LENEMYs_H__
#pragma once
#include "Manager/SpriteManager.h"
#include "LEnemy.h"

class LEnemys :	public SpriteManager<LEnemy>
{
public:
	LEnemys() = default;

public:
	LEnemy* Add();

protected:

};

#endif