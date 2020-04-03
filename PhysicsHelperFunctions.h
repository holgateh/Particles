#pragma once
#include"Vector2d.h"
#include"Integrator.h"
#include"Particle.h"
#include"Vector2dHelperFunctions.h"

#include<vector>
/* Define gravitational constant */
#define G 6.67*pow(10,-11);
class PhysicsHelperFunctions
{
	public:
			static void resolveDynamicCollision(Particle &p1, Particle &p2)
			{
				Vector2d newV1, newV2;
				newV1.x = (p1.state.vel.x * (p1.getMass() - p2.getMass()) + 2 * p2.getMass() * p2.state.vel.x)
					  / (p1.getMass() + p2.getMass());
				newV2.x = (p2.state.vel.x * (p2.getMass() - p1.getMass()) + 2 * p1.getMass() * p1.state.vel.x)
					  / (p1.getMass() + p2.getMass());
				newV1.y = (p1.state.vel.y * (p1.getMass() - p2.getMass()) + 2 * p2.getMass() * p2.state.vel.y)
					  / (p1.getMass() + p2.getMass());
				newV2.y = (p2.state.vel.y * (p2.getMass() - p1.getMass()) + 2 * p1.getMass() * p1.state.vel.y)
					  / (p1.getMass() + p2.getMass());
				p1.state.vel = newV1;
				p2.state.vel = newV2;
			}

			static Vector2d getGravitationalAttraction(Particle &p1, Particle &p2)
			{
				float r = dist(p1.state.pos, p2.state.pos);

				float force = (0.05f)*(p1.getMass())*(p2.getMass())/(r*r);

				Vector2d direction = sub(p2.state.pos, p1.state.pos);

				normalize(direction);

			 	direction.scale(force);

				return direction;
			}

			static void calculateParticleAcceleration(std::vector<Particle> &particles)
			{
				for(int i=0; i < particles.size(); i++)
				{
					particles.at(i).state.acc.x = 0;
					particles.at(i).state.acc.y = 0;
					for(int j=0; j < particles.size(); j++)
					{
						if(j!=i)
						{
							Vector2d force = getGravitationalAttraction(particles.at(i), particles.at(j));
							particles.at(i).state.acc.x += force.x / particles.at(i).getMass();
						       	particles.at(i).state.acc.y += force.y / particles.at(i).getMass();
						}
					}
				}
			}
};
