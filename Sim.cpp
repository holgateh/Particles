#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<SDL.h>

#include"Sim.h"
#include"PPair.h"
#include"Vector2dHelperFunctions.h"

void Sim::update(float deltaTime)
{
	std::cout << "Update started...\n";
	std::vector<PPair<Particle>> collidingPairs;
	unsigned numUpdates = 10;

	for(unsigned k = 0; k < numUpdates; k++)
	{
		for(unsigned i=0; i < this->particles.size(); i++)
		{	
			//integrate(&particles.at(i), 0, dt/numUpdates);
			//particles.at(i).pos.y += 1;
			// wrap objects around the screen space
			//Calculate static collisions:	
			for(unsigned j=0; j < this->particles.size(); i++)
			{
				if(i!=j && (dist(particles.at(i).pos, particles.at(j).pos) < particles.at(i).getMass() + particles.at(j).getMass()))
				{
					float overlap = particles.at(i).getMass() + particles.at(j).getMass() - dist(particles.at(i).pos, particles.at(j).pos);
					Vector2d centerDir = sub(particles.at(j).pos, particles.at(i).pos);
					normalize(centerDir);
					particles.at(i).pos.x += -centerDir.x * overlap / 2;
					particles.at(j).pos.x += centerDir.x * overlap / 2;
					particles.at(i).pos.y += -centerDir.y * overlap / 2;
					particles.at(j).pos.y += centerDir.y * overlap / 2;

					// add pair to dynamic collision array:	
					PPair<Particle> p = PPair<Particle>(&particles.at(i), &particles.at(j));
					collidingPairs.push_back(p);
				}
			}
			if(particles.at(i).pos.y > this->simHeight-1)
			{
				particles.at(i).pos.y = 0;
			}
			if(particles.at(i).pos.y < 0)
			{
				particles.at(i).pos.y = this->simHeight-1;
			}
			if(particles.at(i).pos.x > this->simWidth-1)
			{
				particles.at(i).pos.x = 0; 
			}
			if(particles.at(i).pos.x < 0)
			{
				particles.at(i).pos.x = this->simWidth-1;
			}
		}
		/*
		while(numCollidingPairs > 0)	
		{
			resolveDynamicCollision(collidingPairs[numCollidingPairs-1].p1, collidingPairs[numCollidingPairs-1].p2);	
			numCollidingPairs--;
		}
		
		calculateParticleAcceleration(particles, NUM_OF_PARTICLES);	
		*/
	}
	std::cout << "Update finished...\n";
}

void Sim::render()
{

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
	float pDensity = 10.0f; 

	for(unsigned i = 0; i < numParticles; i++)
	{
		Vector2d pos(rand() % simWidth, rand() % simHeight), vel(5.0f, 5.0f), acc;
		Particle p(pos, vel, acc, 10.0f, pDensity);
		particles.push_back(p);	
	}

	std::cout << "Simulation started.\n";
}

