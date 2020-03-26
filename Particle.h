#pragma once

#include"Vector2d.h"
class Particle
{
	public:
		Vector2d pos, vel, acc;
		float radius, density;
	private:
	
	public:
		Particle(Vector2d pos, Vector2d vel, Vector2d acc, float radius, float density);
		float getMass();	
	private:

};