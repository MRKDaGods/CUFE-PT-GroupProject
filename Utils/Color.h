#pragma once

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