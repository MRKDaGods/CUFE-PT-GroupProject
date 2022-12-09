#pragma once

#include "Vector2.h"

//Rectangle
struct Rect
{
	float x;
	float y;
	float w;
	float h;

	Rect(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	Rect() : Rect(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	Vector2 Position()
	{
		return Vector2(x, y);
	}

	Vector2 Size()
	{
		return Vector2(w, h);
	}

	float XMin()
	{
		return x;
	}

	float XMax()
	{
		return x + w;
	}

	float YMin()
	{
		return y;
	}

	float YMax()
	{
		return y + h;
	}

	bool Contains(Vector2 pos)
	{
		return pos.x >= XMin() && pos.x <= XMax() && pos.y >= YMin() && pos.y <= YMax();
	}
};