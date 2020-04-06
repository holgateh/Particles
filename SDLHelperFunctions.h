#pragma once
#include<SDL.h>
#include<math.h>
#include<vector>
#include"Vector2d.h"
#include<utility>
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.

class SDLHelperFunctions
{
    public:
        /* line: Draw a line on screen, with a different color pixel in top & bottom */
        static void line(int x1, int y1, int x2, int y2, int top, int middle, int bottom, SDL_Surface* surface)
        {
            y1 = clamp(y1, 0,surface->h-1);
            y2 = clamp(y2, 0,surface->h-1);
            x1 = clamp(x1, 0,surface->w-1);
            x2 = clamp(x2, 0,surface->w-1);
            float mag = (x2-x1 != 0 ||  y2-y1 != 0) ? sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) : 1;
            float u1 = (x2-x1)/mag;
            float u2 = (y2-y1)/mag;
            ((int*)surface->pixels)[y1*(int)surface->w+x1] = top;
            for(int i = 1; i < mag; i++){((int*)surface->pixels)[(int)floor((y1+u2*i))*(int)surface->w+(int)floor(x1+u1*i)] = middle;}
            ((int*)surface->pixels)[y2*(int)surface->w+x2] = bottom;
        }

	static void line(Vector2d v1, Vector2d v2, int top, int middle, int bottom, SDL_Surface* surface)
	{
		line(v1.x, v1.y, v2.x, v2.y, top, middle, bottom, surface);
	}


        static void circle(int x, int y, int r, SDL_Surface* surface)
        {
        	int n = 100;	// The number of sides of the n-agon.
        	float a = 0; //current angle;
        	for(int i =0; i<n; i++)
        	{
        		line(x + r*cos(2*M_PI*(float)(i)/n), y + r*sin(2*M_PI*(float)(i)/n),
        		     x + r*cos(2*M_PI*(float)(i+1)/n), y + r*sin(2*M_PI*(float)(i+1)/n), 255, 255, 255, surface);
        	}
        }

	static void rasterizeTriangle(Vector2d v[3], int top, int middle, int bottom, SDL_Surface* surface)
	{
		//Sort so vertex with smallest first;
		bool swap = false;
		do
		{	for(int i = 0; i < 2; i++)
			{
				if(v[i].y > v[i+1].y)
				{
					Vector2d temp = v[i];
					v[i] = v[i+1];
					v[i+1] = temp;
					swap = true;	
				}	
			}	
		}
		while(swap);

		float min = v[0].y;
		float max = v[2].y;
		
		if(v[2].x <= v[1].x)
		{
			Vector2d temp = v[2];
			v[2] = v[1];
			v[1] = temp;
		}
		
		int range = round(max - min);
		std::pair<float, float> pair[range];
		for(int i = 0; i < range; i++)
		{
			if(v[1].y < v[2].y)
			{
				if(i <= v[1].y - v[0].y)
				{
					pair[i].first = (v[0].x + (v[1].x - v[0].x)/(v[1].y - v[0].y) * i);
				}		
				else
				{
					pair[i].first = (v[1].x + (v[2].x - v[1].x)/(v[2].y - v[1].y) * i);
				}

				pair[i].second = (v[0].x + (v[2].x - v[0].x)/(v[2].y - v[0].y) * i);
			}
			else
			{
				if(i <= v[2].y - v[0].y)
				{
					pair[i].second = (v[0].x + (v[2].x - v[0].x)/(v[2].y - v[0].y) * i);
				}		
				else
				{
					pair[i].second = (v[2].x + (v[1].x - v[2].x)/(v[1].y - v[2].y) * i);
				}

				pair[i].first = (v[0].x + (v[1].x - v[0].x)/(v[1].y - v[0].y) * i);
			}
		}
		
		for(int i = 0; i < range; i++)
		{
			line(pair[i].first, v[0].y + i, pair[i].second, v[0].y + i, top, middle, bottom, surface);
		}	


	}	
};
