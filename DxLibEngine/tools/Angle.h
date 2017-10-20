#ifndef __ANGLE_H__
#define __ANGLE_H__
#include "base/LMath.h"
class Radian;
class Degree
{
	typedef float dtype;
public:
	explicit Degree(dtype degree = 0) : m_deg(degree) { }

	static Degree fromDegree(dtype degree) { return Degree(degree); }
	static Degree fromRadian(dtype radian) { return Degree(Rad2Deg(radian)); }
	Degree toDegree() const { return *this; }
	inline Radian toRadian() const;

public:
	dtype	degree() const { return m_deg; }
	dtype	radian() const { return Deg2Rad(m_deg); }
	void	setDegree(dtype degree) { m_deg = degree; }
	void	setRadian(dtype radian) { m_deg = Rad2Deg(radian); }

	void	sincos(dtype& sine, dtype& cosine) const
	{
		SinCosDeg(m_deg, sine, cosine);
	}
	dtype	sin() const { return static_cast<dtype>(SinDeg(m_deg)); }
	dtype	cos() const { return static_cast<dtype>(CosDeg(m_deg)); }

public:
	void operator+=(const Degree& rhs) { m_deg += rhs.m_deg; }
	void operator-=(const Degree& rhs) { m_deg -= rhs.m_deg; }
	Degree operator+(const Degree& rhs) const { return Degree(m_deg + rhs.m_deg); }
	Degree operator-(const Degree& rhs) const { return Degree(m_deg - rhs.m_deg); }
	Degree operator-() const { return Degree(-m_deg); }

	void operator+=(dtype rhs) { m_deg += rhs; }
	void operator-=(dtype rhs) { m_deg -= rhs; }
	Degree operator+(dtype rhs) const { return Degree(m_deg + rhs); }
	Degree operator-(dtype rhs) const { return Degree(m_deg - rhs); }

public:
	template <typename T> void operator*=(const T& rhs) { m_deg *= rhs; }
	template <typename T> void operator/=(const T& rhs) { m_deg /= rhs; }
	template <typename T> Degree operator*(const T& rhs) const { return Degree(m_deg * rhs); }
	template <typename T> Degree operator/(const T& rhs) const { return Degree(m_deg / rhs); }

private:
	dtype m_deg;
};

class Radian
{
	typedef float dtype;
public:
	explicit Radian(dtype radian = 0) : m_rad(radian) { }

	static Radian fromDegree(dtype degree) { return Radian(Deg2Rad(degree)); }
	static Radian fromRadian(dtype radian) { return Radian(radian); }
	Degree toDegree() const { return Degree(degree()); }
	Radian toRadian() const { return *this; }

public:
	dtype	degree() const { return Rad2Deg(m_rad); }
	dtype	radian() const { return m_rad; }
	void	setDegree(dtype degree) { m_rad = Deg2Rad(degree); }
	void	setRadian(dtype radian) { m_rad = radian; }

	void	sincos(dtype& sine, dtype& cosine) const
	{
		SinCos(m_rad, sine, cosine);
	}
	dtype	sin() const { return static_cast<dtype>(Sin(m_rad)); }
	dtype	cos() const { return static_cast<dtype>(Cos(m_rad)); }

public:
	void operator+=(const Radian& rhs) { m_rad += rhs.m_rad; }
	void operator-=(const Radian& rhs) { m_rad -= rhs.m_rad; }
	Radian operator+(const Radian& rhs) const { return Radian(m_rad + rhs.m_rad); }
	Radian operator-(const Radian& rhs) const { return Radian(m_rad - rhs.m_rad); }
	Radian operator-() const { return Radian(-m_rad); }

	void operator+=(dtype rhs) { m_rad += rhs; }
	void operator-=(dtype rhs) { m_rad -= rhs; }
	Radian operator+(dtype rhs) const { return Radian(m_rad + rhs); }
	Radian operator-(dtype rhs) const { return Radian(m_rad - rhs); }

public:
	template <typename T> void operator*=(const T& rhs) { m_rad *= rhs; }
	template <typename T> void operator/=(const T& rhs) { m_rad /= rhs; }
	template <typename T> Radian operator*(const T& rhs) const { return Radian(m_rad + rhs); }
	template <typename T> Radian operator/(const T& rhs) const { return Radian(m_rad - rhs); }

private:
	dtype m_rad;
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
