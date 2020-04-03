#include"Particle.h"

#include<math.h>

Particle::Particle(Vector2d pos, Vector2d vel, Vector2d acc, float radius, float density)
{
	this->state.pos = pos;
	this->state.vel = vel;
	this->state.acc = acc;
	this->radius = radius;
	this->density = density;
}

float Particle::getMass()
{
	return M_PI * radius * radius * density;
}
