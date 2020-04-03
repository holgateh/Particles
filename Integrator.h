#pragma once
#include "Vector2d.h"
struct state
{
	Vector2d pos;
	Vector2d vel;
	Vector2d acc;
};
typedef struct state State;
struct derivative
{
	Vector2d dpos;
	Vector2d dvel;
};
typedef struct derivative Derivative;
// integrator functions:
class Integrator
{
	public:
		static Vector2d acceleration(const State state, double t)
		{
			return state.acc;
		}

		static Derivative evaluate(const State initial, double t, float dt, const Derivative d)
		{
		    State state = {{0,0},{0,0}};
			state.pos.x = initial.pos.x + d.dpos.x*dt;
			state.pos.y = initial.pos.y + d.dpos.y*dt;
			state.vel.x = initial.vel.x + d.dvel.x*dt;
			state.vel.y = initial.vel.y + d.dvel.y*dt;
			state.acc = initial.acc;

			Derivative output;
			output.dpos = state.vel;
			output.dvel = acceleration(state, t+dt);
			return output;
		}
		
		static void integrate(State *state, double t, double dt)
		{
		    Derivative a,b,c,d;

			Derivative initialDerivative = {{0,0}, {0,0}};
			a = evaluate(*state, t, 0.0f, initialDerivative);
			b = evaluate(*state, t, dt*0.5f, a);
			c = evaluate(*state, t, dt*0.5f, b);
			d = evaluate(*state, t, dt, c);

			Derivative resultant;
			resultant.dpos.x = 1.0f/6.0f * (a.dpos.x + 2.0f * (b.dpos.x + c.dpos.x) + d.dpos.x);
			resultant.dpos.y = 1.0f/6.0f * (a.dpos.y + 2.0f * (b.dpos.y + c.dpos.y) + d.dpos.y);
			resultant.dvel.x = 1.0f/6.0f * (a.dvel.x + 2.0f * (b.dvel.x + c.dvel.x) + d.dvel.x);
			resultant.dvel.y = 1.0f/6.0f * (a.dvel.y + 2.0f * (b.dvel.y + c.dvel.y) + d.dvel.y);

			state->pos.x += resultant.dpos.x*dt;
			state->pos.y += resultant.dpos.y*dt;
			state->vel.x += resultant.dvel.x*dt;
			state->vel.y += resultant.dvel.y*dt;
		}
};
