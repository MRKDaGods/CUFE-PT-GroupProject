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