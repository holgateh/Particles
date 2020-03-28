#include"Particle.h"

Particle::Particle(Vector2d pos, Vector2d vel, Vector2d acc, float radius, float density)
{
	this.pos = pos;
	this.vel = vel;
	this.acc = acc;
	this.radius = radius;
	this.density = density;
}

float Particle getMass()
{
	return M_PI * radius * raduis * density;
}
