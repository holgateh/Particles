#include"Vector2d.h"

#include<math.h>

Vector2d::Vector2d()
{
	this->x = 0;
	this->y = 0;
}


Vector2d::Vector2d(float x, float y)
{
	this->x = x;
	this->y = y;	
}


Vector2d::Vector2d(const Vector2d& v)
{
	this->x = v.x;
	this->y = v.y;
}

Vector2d Vector2d::perp()
{
	return Vector2d(-this->y, this->x);
}

float Vector2d::mag()
{
	return sqrt(this->x * this->x + this->y * this->y); 
}

Vector2d Vector2d::normalized()
{
	return Vector2d(this->x / this->mag(), this->y / this->mag());
}

void Vector2d::scale(float s)
{
	this->x *= s;
	this->y *= s;
}
