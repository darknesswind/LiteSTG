#ifndef __LMATH_H__
#define __LMATH_H__
#pragma once
#include "typedef.h"
#include <QtMath>

#define SINE_COSINE_ACCUR_LEVEL 2

// ¦Ð
#define L_PI 3.14159265358979323846264338327950288
// 2 * ¦Ð
#define L_PI2 6.28318530717958647692528676655900577
// ¦Ð / 2
#define L_PID2 1.57079632679489661923132169163975144
// ¡Ì¦Ð
#define L_PI_SQR 9.86960440108935861883449099987615114
// ¡Ì0.5
#define L_SQRT1_2 M_SQRT1_2

#define L_EPSIONF FLT_EPSILON

inline float Deg2Rad(float degrees)
{
	return degrees * float(L_PI / 180);
}

inline double Deg2Rad(double degrees)
{
	return degrees * (L_PI / 180);
}

inline float Rad2Deg(float radians)
{
	return radians * float(180 / L_PI);
}

inline double Rad2Deg(double radians)
{
	return radians * (180 / L_PI);
}

extern const float lookuptbl[360];
#ifdef _DEBUG
template <typename T> float LookUpSinDeg(T x)
{
	int index = (int)(x + 0.5f) % 360;
	if (index < 0) index += 360;
	return lookuptbl[index];
}
template <typename T> float LookUpCosDeg(T x)
{
	int index = (int)(x + 90.5f) % 360;
	if (index < 0) index += 360;
	return lookuptbl[index];
}
template <typename T> float LookUpSin(T x)
{
	return LookUpSinDeg(Rad2Deg(x));
}
template <typename T> float LookUpCos(T x)
{
	return LookUpCosDeg(Rad2Deg(x));
}
#else
#define LookUpSinDeg(x) lookuptbl[(int)((x) + 360.5f) % 360]
#define LookUpCosDeg(x) lookuptbl[(int)((x) + 450.5f) % 360]
#define LookUpSin(x) LookUpSinDeg(Rad2Deg(x))
#define LookUpCos(x) LookUpCosDeg(Rad2Deg(x))
#endif

#if 1 == SINE_COSINE_ACCUR_LEVEL
#	define Sin(x) LookUpSin(x)
#	define Cos(x) LookUpCos(x)
#	define SinDeg(x) LookUpSinDeg(x)
#	define CosDeg(x) LookUpCosDeg(x)
#	define SinCosDeg(x, sine, cosine)	\
{										\
	(sine) = SinDeg(x);					\
	(cosine) = CosDeg(x);				\
}
#else
#if 2 == SINE_COSINE_ACCUR_LEVEL
#	define Sin(x) qFastSin(x)
#	define Cos(x) qFastCos(x)
#else
#	define Sin(x) sin(x)
#	define Cos(x) cos(x)
#endif // lv2
#	define SinDeg(x) Sin(Deg2Rad(x))
#	define CosDeg(x) Cos(Deg2Rad(x))
#	define SinCosDeg(x, sine, cosine)	\
{										\
	auto radians = qDegreesToRadians(x);\
	(sine) = Sin(radians);				\
	(cosine) = Cos(radians);			\
}
#endif // lv1
#	define SinCos(x, sine, cosine)	\
{									\
	(sine) = Sin(x);				\
	(cosine) = Cos(x);				\
}

template <uint i>
struct factorial { static const uint value = i * factorial<i - 1>::value; };
template <>
struct factorial<1> { static const uint value = 1; };

inline bool isSameSign(int lhs, int rhs)
{
	return !((lhs ^ rhs) & 0x80000000);
}

inline bool isSameSign(float lhs, float rhs)
{
	union _Dummy
	{
		int i;
		float f;
	};

	_Dummy iLhs, iRhs;
	iLhs.f = lhs;
	iRhs.f = rhs;
	return isSameSign(iLhs.i, iRhs.i);
}

#endif // !__LMATH_H__
