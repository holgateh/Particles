#pragma once
class Vector2d
{
	public:
		float x,y;
	private:

	public:
		Vector2d();
		Vector2d(float x, float y);
		Vector2d(const Vector2d& v);
		Vector2d perp();
		float mag();
		Vector2d normalized();
		void scale(float s);
	private:
};
