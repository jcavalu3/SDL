#include "ball.h"

ball::ball(SDL_Surface* img, int x, int y, int w, int h, int xVel, int yVel)
{
	image = img;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	xvel = xVel;
	yvel = yVel;
};

ball:~ball()
{
	SDL_FreeSurface(image);
}

void ball::show()
{
	SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &box);
}

void ball::move()
{
	box.x += xvel;
	box.y += yvel;
}

bool ball::collision(SDL_Rect* rec1, SDL_Rect* rec2)
{
	if(rec1 -> y > rec2 -> y + rec2 -> h)
		return 0;
	if(rec1 -> x >= rec2 -> x + rec2 -> w)
		return 0;
}
