#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<SDL.h>

#include"Sim.h"
#include"PPair.h"
#include"Integrator.h"

#include"Vector2dHelperFunctions.h"
#include"SDLHelperFunctions.h"
#include"PhysicsHelperFunctions.h"

void Sim::update(float deltaTime)
{
	std::cout << "Update started...\n";
	std::vector<PPair<Particle>> collidingPairs;
	unsigned numUpdates = 10;

	for(unsigned k = 0; k < numUpdates; k++)
	{
		for(unsigned i=0; i < this->particles.size(); i++)
		{
			Integrator::integrate(&particles.at(i).state, 0, deltaTime/(float)numUpdates);
			//particles.at(i).state.pos.y += 1;
			// wrap objects around the screen space
			//Calculate static collisions:
			for(unsigned j=0; j < this->particles.size(); j++)
			{
				if(i!=j && (dist(particles.at(i).state.pos, particles.at(j).state.pos) < particles.at(i).getMass() + particles.at(j).getMass()))
				{
					float overlap = particles.at(i).getMass() + particles.at(j).getMass() - dist(particles.at(i).state.pos, particles.at(j).state.pos);
					Vector2d centerDir = sub(particles.at(j).state.pos, particles.at(i).state.pos);
					normalize(centerDir);
					particles.at(i).state.pos.x += -centerDir.x * overlap / 2;
					particles.at(j).state.pos.x += centerDir.x * overlap / 2;
					particles.at(i).state.pos.y += -centerDir.y * overlap / 2;
					particles.at(j).state.pos.y += centerDir.y * overlap / 2;

					// add pair to dynamic collision vector:
					PPair<Particle> p = PPair<Particle>(&particles.at(i), &particles.at(j));
					collidingPairs.push_back(p);
				}
			}
			if(particles.at(i).state.pos.y > this->simHeight-1)
			{
				particles.at(i).state.pos.y = 0;
			}
			if(particles.at(i).state.pos.y < 0)
			{
				particles.at(i).state.pos.y = this->simHeight-1;
			}
			if(particles.at(i).state.pos.x > this->simWidth-1)
			{
				particles.at(i).state.pos.x = 0;
			}
			if(particles.at(i).state.pos.x < 0)
			{
				particles.at(i).state.pos.x = this->simWidth-1;
			}
		}

		for(unsigned i = 0; i < collidingPairs.size(); i++)
		{
			PhysicsHelperFunctions::resolveDynamicCollision(*(collidingPairs.at(i).getFirst()), *(collidingPairs.at(i).getSecond()));
		}

		PhysicsHelperFunctions::calculateParticleAcceleration(particles);

	}
	std::cout << "Update finished...\n";
}

void Sim::render()
{
	for(unsigned i=0; i< this->particles.size(); i++)
	{
		if(particles.at(i).state.pos.x >= 0 && particles.at(i).state.pos.x < this->simWidth && particles.at(i).state.pos.y >= 0 && particles.at(i).state.pos.y < this->simHeight)
		{
			SDLHelperFunctions::circle(particles.at(i).state.pos.x, particles.at(i).state.pos.y,
			       particles.at(i).getMass(), this->surface);
		}
	}
	Vector2d v[] = { Vector2d(0, 0), Vector2d(0,100), Vector2d(100, 100)};
	SDLHelperFunctions::rasterizeTriangle(v, 255, 255, 255, this->surface); 
}

void Sim::run()
{
    	surface = SDL_SetVideoMode(this->simWidth, this->simHeight, 32, 0);
    	SDL_EnableKeyRepeat(150, 30);
    	SDL_ShowCursor(SDL_ENABLE);

    	for(;;)
    	{
		SDL_LockSurface(surface);
		SDL_UnlockSurface(surface);
		SDL_Flip(surface);
		SDL_FillRect(surface, NULL, 0x000000);

		this->update(deltaTime);
		this->render();
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
	    		switch(ev.type)
	    		{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
		    			switch(ev.key.keysym.sym)
		    			{
						default: break;
		    			}
		    			break;
				case SDL_QUIT: goto done;
	    		}


    	}
	done:
	    SDL_Quit();

}

Sim::Sim(unsigned simWidth, unsigned simHeight, unsigned numParticles)
{
	this->deltaTime = 1.0f / 60.0f;
	this->simWidth = simWidth;
	this->simHeight = simHeight;

	srand(time(NULL));
	float pDensity = 1.0f;

	for(unsigned i = 0; i < numParticles; i++)
	{
		Vector2d pos(rand() % simWidth, rand() % simHeight), vel( (1 + -2 * (rand() % 2)) * rand() % 5, (1 + -2 * (rand() % 2)) * rand() % 5), acc;
		Particle p(pos, vel, acc, 2.0f, pDensity);
		particles.push_back(p);
	}

	std::cout << "Simulation started.\n";
}
