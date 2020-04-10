#include<vector>
#include<SDL.h>

#include"Particle.h"

class Sim
{
	public:
		
	private: 
		std::vector<Particle> particles;
		float deltaTime;
		float timeElapsed;
		SDL_Surface* surface = NULL;		
		unsigned simWidth, simHeight;
	public: 
		Sim(unsigned simWidth, unsigned simHeight, unsigned numParticles);
		void run();
	private:
		void update(float deltaTime);
		void render();
	
};	
