#include "stdafx.h"
#include "LPhysicWalker.h"

void LPhysicWalker::nextStep(PhysicData& data)
{
	data.speed.fixFuzzyNull();
	data.position += data.speed;	// 速度造成的位移 
	Vector2 speedUnit = data.speed.normalized();
	Vector2 resultant; // 合力

	if (speedUnit.isNull() &&
		data.acceleration.lengthSquared() < data.friction * data.friction)
		resultant.reset();
	else
		resultant = data.acceleration - data.friction * speedUnit;

	data.speed += resultant;
	if (!resultant.isFuzzyNull() && !data.speed.isFuzzyNull())
		data.radian = data.speed.radian();

	if (!isSameSign(resultant.x(), data.acceleration.x()) &&
		isSameSign(data.speed.x(), resultant.x()))
		data.speed.setX(0);

	if (!isSameSign(resultant.y(), data.acceleration.y()) &&
		isSameSign(data.speed.y(), resultant.y()))
		data.speed.setY(0);
}
