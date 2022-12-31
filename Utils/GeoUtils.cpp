#include "GeoUtils.h"
#include "../DEFS.h"

#define _USE_MATH_DEFINES
#include <math.h>

//disable the buffer overrun warning
#pragma warning(push)
#pragma warning(disable: 6386)

void GetSegmentedCirclePoints(Point center, int segments, int radius, int** x, int** y)
{
	if (!x || !y) return;

	float _2pi = 2 * M_PI;
	float adv = _2pi / (float)segments;

	*x = new int[segments];
	*y = new int[segments];

	int idx = 0;
	for (float theta = adv; theta < _2pi; theta += adv)
	{
		(*x)[idx] = center.x + cosf(theta) * radius;
		(*y)[idx] = center.y - sinf(theta) * radius;
		idx++;
	}
}

#pragma warning(pop)

bool PointInPolygon(Point point, Point* points, int nvert)
{
	int i, j;
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++)
	{
		if (((points[i].y >= point.y) != (points[j].y >= point.y))
			&& (point.x <= (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
		{
			c = !c;
		}
	}

	return c;
}