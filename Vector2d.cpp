#include"Vector2d.h"

Vector2d::Vector2d()
{
	this.x = 0;
	this.y = 0;
}


Vector2d::Vector2d(float x, float y)
{
	this.x = x;
	this.y = y;	
}


Vector2d::Vector2d(const Vector2d& v)
{
	this.x = v.x;
	this.y = v.y;
}
