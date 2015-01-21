#ifndef __ANGLE_H__
#define __ANGLE_H__
#include "LMath.h"
class Radian;
class Degree
{
public:
	explicit Degree(float degree = 0) : m_deg(degree) { }

	static Degree fromDegree(float degree) { return Degree(degree); }
	static Degree fromRadian(float radian) { return Degree(Rad2Deg(radian)); }
	Degree toDegree() const { return *this; }
	inline Radian toRadian() const;

public:
	float	degree() const { return m_deg; }
	float	radian() const { return Deg2Rad(m_deg); }
	void	setDegree(float degree) { m_deg = degree; }
	void	setRadian(float radian) { m_deg = Rad2Deg(radian); }

	void	getSinCos(float& sine, float& cosine)
	{
		SinCosDeg(m_deg, sine, cosine);
	}

	void operator+=(const Degree& rhs) { m_deg += rhs.m_deg; }
	void operator-=(const Degree& rhs) { m_deg -= rhs.m_deg; }
	Degree operator+(const Degree& rhs) const { return Degree(m_deg + rhs.m_deg); }
	Degree operator-(const Degree& rhs) const { return Degree(m_deg - rhs.m_deg); }
	Degree operator-() const { return Degree(-m_deg); }

	template <typename T> void operator*=(const T& rhs) { m_deg *= rhs; }
	template <typename T> void operator/=(const T& rhs) { m_deg /= rhs; }
	template <typename T> Degree operator*(const T& rhs) const { return Degree(m_deg * rhs); }
	template <typename T> Degree operator/(const T& rhs) const { return Degree(m_deg / rhs); }

private:
	float m_deg;
};

class Radian
{
public:
	explicit Radian(float radian = 0) : m_rad(radian) { }

	static Radian fromDegree(float degree) { return Radian(Deg2Rad(degree)); }
	static Radian fromRadian(float radian) { return Radian(radian); }
	Degree toDegree() const { return Degree(degree()); }
	Radian toRadian() const { return *this; }

public:
	float	degree() const { return Rad2Deg(m_rad); }
	float	radian() const { return m_rad; }
	void	setDegree(float degree) { m_rad = Deg2Rad(degree); }
	void	setRadian(float radian) { m_rad = radian; }

	void	getSinCos(float& sine, float& cosine)
	{
		SinCos(m_rad, sine, cosine);
	}

	void operator+=(const Radian& rhs) { m_rad += rhs.m_rad; }
	void operator-=(const Radian& rhs) { m_rad -= rhs.m_rad; }
	Radian operator+(const Radian& rhs) const { return Radian(m_rad + rhs.m_rad); }
	Radian operator-(const Radian& rhs) const { return Radian(m_rad - rhs.m_rad); }
	Radian operator-() const { return Radian(-m_rad); }

	template <typename T> void operator*=(const T& rhs) { m_rad *= rhs; }
	template <typename T> void operator/=(const T& rhs) { m_rad /= rhs; }
	template <typename T> Radian operator*(const T& rhs) const { return Radian(m_rad + rhs); }
	template <typename T> Radian operator/(const T& rhs) const { return Radian(m_rad - rhs); }

private:
	float m_rad;
};

Radian Degree::toRadian() const
{
	return Radian(radian());
}

extern const Radian Radian0;
extern const Radian Radian90;
extern const Radian Radian180;
extern const Radian Radian270;

#endif // __ANGLE_H__
