#pragma once

#include "../DEFS.h"

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	Color() : Color(0.f, 0.f, 0.f, 0.f)
	{
	}

	Color(int r, int g, int b, int a) : Color(r / 255.f, g / 255.f, b / 255.f, a / 255.f)
	{
	}

	bool operator ==(Color other)
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	static Color Lerp(Color a, Color b, float t)
	{
		if (t > 1.f)
			t = 1.f;
		else if (t < 0.f)
			t = 0.f;

		return Color(a.r + ((b.r - a.r) * t), a.g + ((b.g - a.g) * t),
			a.b + ((b.b - a.b) * t), a.a + ((b.a - a.a) * t));
	}
};

inline DWColors NativeToFrontendColor(color c)
{
	if (c == BLACK) return DWCOLOR_BLACK;
	if (c == YELLOW) return DWCOLOR_YELLOW;
	if (c == ORANGE) return DWCOLOR_ORANGE;
	if (c == RED) return DWCOLOR_RED;
	if (c == GREEN) return DWCOLOR_GREEN;
	if (c == BLUE) return DWCOLOR_BLUE;

	return DWCOLOR_BLACK;
}

inline color FrontendToNativeColor(DWColors c)
{
	switch (c)
	{
	case DWCOLOR_BLACK:
		return BLACK;

	case DWCOLOR_YELLOW:
		return YELLOW;

	case DWCOLOR_ORANGE:
		return ORANGE;

	case DWCOLOR_RED:
		return RED;

	case DWCOLOR_GREEN:
		return GREEN;

	case DWCOLOR_BLUE:
		return BLUE;

	case DWCOLOR_COUNT:
		break;
	}

	return BLACK;
}