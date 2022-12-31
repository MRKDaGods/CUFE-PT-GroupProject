#include "Vector2.h"
#include "../DEFS.h"

#include <corecrt_math.h>

//avoid inline declaration (compatibility)
Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);

float Vector2::Magnitude()
{
	return sqrtf(SqrMagnitude());
}

Point::operator Vector2()
{
	return Vector2(x, y);
}

Vector2 Vector2::Normalize()
{
	float mag = Magnitude();
	return (*this) * (1.0f / mag);
}

Vector2::operator Point()
{
	return Point{ (int)x, (int)y };
}
