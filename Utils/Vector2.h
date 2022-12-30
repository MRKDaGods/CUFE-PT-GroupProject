#pragma once

//Point representation as a floating point
struct Vector2
{
	float x;
	float y;

	static Vector2 Zero;

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2() : Vector2(0.0f, 0.0f)
	{
	}

	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	float Magnitude();

	Vector2 operator+(Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	void operator+=(Vector2 other)
	{
		x += other.x;
		y += other.y;
	}

	Vector2 operator-(Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}

	bool operator==(Vector2 other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(Vector2 other)
	{
		return x != other.x || y != other.y;
	}

	Vector2 operator*(float other)
	{
		return Vector2(x * other, y * other);
	}
};