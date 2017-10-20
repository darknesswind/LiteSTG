#ifndef __LMATH_H__
#define __LMATH_H__
#pragma once

#define SINE_COSINE_ACCUR_LEVEL 2

// π
#define L_PI 3.14159265358979323846264338327950288
// 2 * π
#define L_PI2 6.28318530717958647692528676655900577
// π / 2
#define L_PID2 1.57079632679489661923132169163975144
// √π
#define L_PI_SQR 9.86960440108935861883449099987615114
// √0.5
#define L_SQRT1_2 0.707106781186547524401

#define L_EPSIONF FLT_EPSILON

inline constexpr float Deg2Rad(float degrees)
{
	return degrees * float(L_PI / 180);
}

inline constexpr double Deg2Rad(double degrees)
{
	return degrees * (L_PI / 180);
}

inline constexpr float Rad2Deg(float radians)
{
	return radians * float(180 / L_PI);
}

inline constexpr double Rad2Deg(double radians)
{
	return radians * (180 / L_PI);
}

// Qt的计算方法
#define QT_SINE_TABLE_SIZE 256
extern const double qt_sine_table[QT_SINE_TABLE_SIZE];
inline constexpr double qFastSin(double x)
{
	int si = static_cast<int>(x * (0.5 * QT_SINE_TABLE_SIZE / L_PI)); // Would be more accurate with qRound, but slower.
	const double d = x - si * (2.0 * L_PI / QT_SINE_TABLE_SIZE);
	int ci = si + QT_SINE_TABLE_SIZE / 4;
	si &= QT_SINE_TABLE_SIZE - 1;
	ci &= QT_SINE_TABLE_SIZE - 1;
	return qt_sine_table[si] + (qt_sine_table[ci] - 0.5 * qt_sine_table[si] * d) * d;
}

inline constexpr double qFastCos(double x)
{
	int ci = static_cast<int>(x * (0.5 * QT_SINE_TABLE_SIZE / L_PI)); // Would be more accurate with qRound, but slower.
	const double d = x - ci * (2.0 * L_PI / QT_SINE_TABLE_SIZE);
	int si = ci + QT_SINE_TABLE_SIZE / 4;
	si &= QT_SINE_TABLE_SIZE - 1;
	ci &= QT_SINE_TABLE_SIZE - 1;
	return qt_sine_table[si] - (qt_sine_table[ci] + 0.5 * qt_sine_table[si] * d) * d;
}
#pragma warning( push )
#pragma warning( disable: 4244 )
template <typename ResType>
inline constexpr void qFastSinCos(double x, ResType& sine, ResType& cosine)
{
	int xi = static_cast<int>(x * (0.5 * QT_SINE_TABLE_SIZE / L_PI)); // Would be more accurate with qRound, but slower.
	const double d = x - xi * (2.0 * L_PI / QT_SINE_TABLE_SIZE);
	int yi = xi + QT_SINE_TABLE_SIZE / 4;

	xi &= QT_SINE_TABLE_SIZE - 1;
	yi &= QT_SINE_TABLE_SIZE - 1;

	sine = qt_sine_table[xi] + (qt_sine_table[yi] - 0.5 * qt_sine_table[xi] * d) * d;
	cosine = qt_sine_table[yi] - (qt_sine_table[xi] + 0.5 * qt_sine_table[yi] * d) * d;
}
#pragma warning( pop )

#if 1 == SINE_COSINE_ACCUR_LEVEL
#	define Sin(x) sin(x)
#	define Cos(x) cos(x)
#	define SinCos(x, sine, cosine)	\
{									\
	(sine) = Sin(x);				\
	(cosine) = Cos(x);				\
}
#elif 2 == SINE_COSINE_ACCUR_LEVEL
#	define Sin(x) qFastSin(x)
#	define Cos(x) qFastCos(x)
#	define SinCos(x, sine, cosine) qFastSinCos(x, sine, cosine)
#endif // lv1

#define SinDeg(x) Sin(Deg2Rad(x))
#define CosDeg(x) Cos(Deg2Rad(x))
#define SinCosDeg(x, sine, cosine)	SinCos(Deg2Rad(x), sine, cosine)

inline constexpr bool isSameSign(int lhs, int rhs)
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

static inline bool qFuzzyIsNull(double d)
{
	return fabs(d) <= 0.000000000001;
}

static inline bool qFuzzyIsNull(float f)
{
	return fabs(f) <= 0.00001f;
}

static inline constexpr bool qIsNull(double d)
{
	union U {
		double d;
		unsigned long long u;
	};
	U val{ d };
	return (val.u & 0x7fffffffffffffffui64) == 0;
}

static inline bool qFuzzyCompare(double p1, double p2)
{
	return (fabs(p1 - p2) * 1000000000000. <= fmin(fabs(p1), fabs(p2)));
}

static inline bool qFuzzyCompare(float p1, float p2)
{
	return (fabs(p1 - p2) * 100000.f <= fmin(fabs(p1), fabs(p2)));
}

#endif // !__LMATH_H__
