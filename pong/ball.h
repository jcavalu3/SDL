#include <SDL/SDL.h>
#ifndef BALL_H
#define BALL_H

class ball{
	int xvel, yvel;
	SDL_Surface* image;
	SDL_Rect box;
	bool collision(SDL_Rect rec1, SDL_rect* rec2);

	public:
		ball(SDL_Surface* img, int x, int y, int w, int h, int xVel, int yVel);
		~ball();
		void show();
		void move();

};


#endif
