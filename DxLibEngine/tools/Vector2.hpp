﻿#pragma once

#include <utility>
#include "Angle.h"

#pragma warning(disable:4244)
class Vector2
{
	typedef float ValueT;
public:
	Vector2() : cx(0), cy(0) { }

	template<typename T1, typename T2>
	Vector2(T1 xpos, T2 ypos)
		: cx(static_cast<ValueT>(xpos)), cy(static_cast<ValueT>(ypos))
	{
	}

	template<typename posType>
	explicit Vector2(const posType& point)
		: cx(static_cast<ValueT>(point.x())), cy(static_cast<ValueT>(point.y()))
	{
	}

	~Vector2(void){};
	
	ValueT x() const { return cx; }
	ValueT y() const { return cy; }
	ValueT& rx() { return cx; }
	ValueT& ry() { return cy; }
	void setX(ValueT fx) { cx = fx; }
	void setY(ValueT fy) { cy = fy; }

	void reset()	{ memset(this, 0, sizeof(Vector2)); }

	void reset(ValueT xpos, ValueT ypos)
	{
		cx = xpos;
		cy = ypos;
	}

	template<typename Angle>
	void setPolar(float len, Angle angle)	// 用极坐标方式初始化
	{
		float sine = 0, cosine = 0;
		angle.sincos(sine, cosine);
		cx = len * cosine;
		cy = len * sine;
	}

	template<typename Angle>
	static Vector2 fromPolar(float len, Angle angle)
	{
		float sine = 0, cosine = 0;
		angle.sincos(sine, cosine);
		return Vector2(len * cosine, len * sine);
	}

	template<typename Angle>
	Vector2 rotated(Angle angle) const	// 返回旋转rad后的向量
	{
		float tx(cx), ty(cy);
		float sine, cosine;
		angle.sincos(sine, cosine);
		return Vector2(tx * cosine + ty * sine, tx * sine - ty * cosine);
	}
	template<typename Angle>
	Vector2& rotate(Angle angle)	// 将向量旋转rad
	{
		float tx(cx), ty(cy);
		float sine = 0, cosine = 0;
		angle.sincos(sine, cosine);
		cx = tx * cosine + ty * sine;
		cy = tx * sine - ty * cosine;
		return *this;
	}
	template<typename Angle>
	Vector2& rotateAt(const Vector2 &origin, Angle angle)	// 绕指定点旋转
	{
		float tx(cx - origin.cx), ty(cy - origin.cy);
		float sine = 0, cosine = 0;
		angle.sincos(sine, cosine);
		cx = tx * cosine - ty * sine + origin.cx;
		cy = tx * sine + ty * cosine + origin.cy;
		return *this;
	}

	void negate()	// 取负
	{
		cx = -cx;
		cy = -cy;
	}

	const ValueT dotProduct(const Vector2 &vect2)	// 点积
	{
		return cx * vect2.cx + cy * vect2.cy;
	}
	static const ValueT dotProduct(const Vector2 &vect1, const Vector2 &vect2)	// 点积
	{
		return vect1.cx * vect2.cx + vect1.cy * vect2.cy;
	}

	const Vector2 normalized() const	// 返回向量的单位向量
	{
		const double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f))
			return *this;
		else if (!qFuzzyIsNull(len))
			return *this / sqrt(len);
		else
			return Vector2();
	}
	const Vector2 normalized(float times) const	// 返回向量的单位向量的times倍
	{
		const double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f))
			return *this * times;
		else if (!qFuzzyIsNull(len))
			return *this * times / sqrt(len);
		else
			return Vector2();
	}
	void normalize()	// 将向量单位化
	{
		double len = double(cx) * double(cx) +
			double(cy) * double(cy);
		if (qFuzzyIsNull(len - 1.0f) || qFuzzyIsNull(len))
			return;

		len = sqrt(len);

		cx /= len;
		cy /= len;
	}
	void fixFuzzyNull()
	{
		if (qFuzzyIsNull(cx)) cx = 0;
		if (qFuzzyIsNull(cy)) cy = 0;
	}

	const Degree degree() const	// 返回角度形式的向量方向
	{
		return Degree(radian().degree());
	}
	const Radian radian() const	// 返回弧度形式的向量方向
	{
		return Radian(atan2(cy, cx));
	}

	const ValueT length() const	// 返回长度
	{
		return sqrt(cx * cx + cy * cy);
	}
	const ValueT manhattanLength() const	// 曼哈顿距离
	{
		return std::abs(cx) + std::abs(cy);
	}
	const ValueT lengthSquared() const	// 返回长度的平方
	{
		return cx * cx + cy * cy;
	}

	/*
	返回与向量v2的距离
	*/
	const ValueT distance(const Vector2 &v2) const
	{
		return (*this - v2).length();
	}
	/// <summary>
	/// 返回与向量v2的距离的平方
	/// </summary>
	const ValueT distanceSquared(const Vector2 &v2) const
	{
		return (*this - v2).lengthSquared();
	}
	/// <summary>
	/// 返回与向量v2的曼哈顿距离
	/// </summary>
	const ValueT manhattanDistance(const Vector2 &v2) const
	{
		return std::abs(cx - v2.cx) + std::abs(cy - v2.cy);
	}

	static Vector2 reflect(const Vector2 &enter, const Vector2 &normal)
	{
		return enter - 2 * dotProduct(enter, normal) / normal.lengthSquared() * normal;
	}
	/// <summary>
	/// 返回在镜面法向量normal上的反射
	/// </summary>
	/// <param name="normal">法向量</param>
	/// <returns>反射向量</returns>
	Vector2 reflect(const Vector2 &normal)
	{
		return *this - 2 * dotProduct(normal) / normal.lengthSquared() * normal;
	}

	/// <summary>
	/// 返回src在dest上的投影长度
	/// </summary>
	static const ValueT project(const Vector2 &src, const Vector2 &dest)
	{
		return dotProduct(src, dest) / dest.length();
	}
	/// <summary>
	/// 返回在dest上的投影长度
	/// </summary>
	const ValueT project(const Vector2 &dest)
	{
		return dotProduct(dest) / dest.length();
	}

	/// <summary>
	/// 到向量dest的角度夹角（弧度转角度）
	/// </summary>
	Degree degreeBetween(const Vector2& dest) const
	{
		const float dx = dest.cx - cx;
		const float dy = dest.cy - cy;
		return Degree(Rad2Deg(atan2(dy, dx)));
	}
	/// <summary>
	/// 到向量dest的弧度夹角
	/// </summary>
	Radian radianBetween(const Vector2& dest) const
	{
		const float dx = dest.cx - cx;
		const float dy = dest.cy - cy;
		return Radian(atan2(dy, dx));
	}


	const Vector2 absed() const	// 对x,y取绝对值后的向量
	{
		return Vector2(std::abs(cx), std::abs(cy));
	}
	void abs()	// 向量绝对值化
	{
		cx = std::abs(cx);
		cy = std::abs(cy);
	}

	bool isNull() const	// 是否为0值
	{
		return qIsNull(cx) && qIsNull(cy);
	}
	bool isFuzzyNull() const	// 约等于0
	{
		return qFuzzyIsNull(cx)
			&& qFuzzyIsNull(cy);
	}
	bool fuzzyCompare(const Vector2 &vect2)	const //  近似比较
	{
		return qFuzzyCompare(cx, vect2.cx)
			&& qFuzzyCompare(cy, vect2.cy);
	}

	bool isDirFuzzyEqual(const Vector2 &vect2) const
	{
		if (isFuzzyNull() || vect2.isFuzzyNull())
			return true;
		const bool bVert = qFuzzyIsNull(cx);
		const bool bOtherVert = qFuzzyIsNull(vect2.cx);
		if (!bVert && !bOtherVert)
			return qFuzzyCompare(cy / cx, vect2.cy / vect2.cx);
		else if (bVert && bOtherVert)
			return true;
		else
			return false;
	}

public:
	static const Vector2 zero()
	{
		return Vector2(0.0f, 0.0f);
	}

#pragma region 操作符重载

	const bool operator< (const Vector2 &other) const
	{
		return this->manhattanLength() < other.manhattanLength();
	}
	const bool operator> (const Vector2 &other) const
	{
		return this->manhattanLength() > other.manhattanLength();
	}

	const bool operator== (const Vector2 &vect2)const
	{
		return (cx == vect2.cx && cy == vect2.cy);
	}
	const bool operator!= (const Vector2 &vect2)const
	{
		return !operator==(vect2);
	}
	const Vector2 operator+ (const Vector2 &vect2)const
	{
		return Vector2(cx + vect2.cx, cy + vect2.cy);
	}
	const Vector2 operator* (const Vector2 &vect2)const
	{		
		return Vector2(cx * vect2.cx, cy * vect2.cy);
	}

	const Vector2 operator- (const Vector2 &vect2)const
	{		
		return Vector2(cx-vect2.cx, cy-vect2.cy);
	}
	Vector2 &operator+= (const Vector2 &vect2)
	{
		cx += vect2.cx;
		cy += vect2.cy;
		return *this;
	}
	Vector2 &operator-= (const Vector2 &vect2)
	{
		cx -= vect2.cx;
		cy -= vect2.cy;
		return *this;
	}
	Vector2 &operator*= (const Vector2 &vect2)
	{
		cx *= vect2.cx;
		cy *= vect2.cy;
		return *this;
	}
	const Vector2 operator- ()
	{
		return Vector2(-cx, -cy);
	}

	template <class U>
	friend const Vector2 operator*(U u, Vector2 vect2)
	{
		return Vector2(u * vect2.cx, u * vect2.cy);
	}
	template <class U>
	friend const Vector2 operator*(Vector2 vect2, U u)
	{
		return Vector2(u * vect2.cx, u * vect2.cy);
	}
	template <class U>
	friend const Vector2 operator/(Vector2 vect2, U u)
	{
		return Vector2(vect2.cx / u, vect2.cy / u);
	}
	template <class U>
	Vector2& operator*=(U u)
	{
		cx *= u;
		cy *= u;
		return *this;
	}
	template <class U>
	Vector2& operator/=(U u)
	{
		cx /= u;
		cy /= u;
		return this;
	}

#pragma endregion

protected:
	ValueT cx, cy;
};
