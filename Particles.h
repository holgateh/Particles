#pragma once
class Particle
{
	public:
		Vector2d pos, vel, acc;
		float radius, density;
	private:
	
	public:
		particle(Vector2d pos, Vector2d vel, Vector2d acc, float radius, float density);
		float getMass();	
	private:

}
