#ifndef __VECTOR3_HPP__
#define __VECTOR3_HPP__
#include "LPoint.h"
#include "Vector2.hpp"

class Vector3 : public DxLib::tagVECTOR
{
public:
	Vector3()
	{
		x = y = z = 0;
	}

	template <typename T1, typename T2, typename T3>
	Vector3(T1 fx, T2 fy, T3 fz)
	{
		x = (float)fx;
		y = (float)fy;
		z = (float)fz;
	}

	Vector3(const Vector2& vect2)
	{
		x = vect2.x();
		y = vect2.y();
		z = 0.0f;
	}

	Vector3(const LPoint& pos2)
	{
		x = pos2.x();
		y = pos2.y();
		z = 0.0f;
	}

	operator DxLib::VECTOR&() { return *this; }
};

#endif //__VECTOR3_HPP__
