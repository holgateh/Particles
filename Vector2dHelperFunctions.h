#pragma once

#include"Vector2d.h"

static Vector2d sub(Vector2d v1, Vector2d v2)
{
	return Vector2d(v1.x - v2.x , v1.y - v2.y);
}

static float dist(Vector2d v1, Vector2d v2)
{
	return sub(v1, v2).mag();
}

static void normalize(Vector2d &v1)
{
	v1.x /= v1.mag();
	v1.y /= v1.mag();
}