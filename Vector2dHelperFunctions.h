#pragma once

#include"Vector2d.h"
#include<math.h>
class Vector2dHelperFunctions
{
public:
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

	static Vector2d rotate(float angle, Vector2d origin, Vector2d v)
	{
		v.x -= origin.x;
		v.y -= origin.y;
		v = Vector2d(v.x*cos(angle) - v.y*sin(angle), v.x*sin(angle) + v.y*cos(angle));
		v.x += origin.x;
		v.y += origin.y;
		return v;
	}
};
