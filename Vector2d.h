#pragma once
#include <cmath>

struct Vector2d
{
	double x;
	double y;

	Vector2d()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2d(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	void Add(double x, double y)
	{
		this->x += x;
		this->y += y;
	}

	void Add(Vector2d p)
	{
		this->x += p.x;
		this->y += p.y;
	}

	double GetLength()
	{
		return sqrt(x*x + y*y);
	}

	void normalize()
	{
		double length = GetLength();
		this->x /= length;
		this->y /= length;
	}

	Vector2d normalized()
	{
		double len = GetLength();
		return Vector2d(this->x / len, this->y / len);
	}

	Vector2d operator*(double d)
	{
		return Vector2d(this->x * d, this->y * d);
	}
	Vector2d operator/(double d)
	{
		return Vector2d(this->x / d, this->y / d);
	}
	void operator/=(double d)
	{
		this->x /= d;
		this->y /= d;
	}
	Vector2d operator+(Vector2d v)
	{
		return Vector2d(this->x + v.x, this->y + v.y);
	}
	Vector2d operator-(Vector2d v)
	{
		return Vector2d(this->x - v.x, this->y - v.y);
	}

	static double Distance(Vector2d p1, Vector2d p2)
	{
		return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
	}
};
