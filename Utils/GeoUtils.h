#pragma once

struct Point;

void GetSegmentedCirclePoints(Point center, int segments, int radius, int** x, int** y);

//ref: https://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
// Checks if a point lies inside a polygon
bool PointInPolygon(Point point, Point* points, int nvert);