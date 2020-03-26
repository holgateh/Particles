#pragma once
#include<vector>

class Sim
{
	public:
		
	private: 
		std::vector<Particle> particles;
	private:
		void update();
		void render();
	public: 
		void run();
}	
