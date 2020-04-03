#pragma once
#include"Vector2d.h"
#include"Integrator.h"
class Particle
{
	public:
		State state;
		float radius, density;
	private:

	public:
		Particle(Vector2d pos, Vector2d vel, Vector2d acc, float radius, float density);
		float getMass();
	private:

};
