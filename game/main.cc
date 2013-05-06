#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "dirt.h"
#include <sstream>
#include <time.h>

const int SCREEN_WIDTH      = 576;
const int SCREEN_HEIGHT     = 960;
const int SCREEN_BPP        = 32; //BPP = Bits per pixel!
const int FRAMES_PER_SECOND = 40;

SDL_Surface *image          = NULL;
SDL_Surface *background     = NULL;
SDL_Surface *screen         = NULL;
SDL_Surface *bob            = NULL;
SDL_Surface *enemy          = NULL;
dirt field;

SDL_Rect clip[5];

SDL_Event event;

SDL_Surface *load_image(std::string filename)
{
	//This is temporary storage for the image that's loaded
	SDL_Surface* loadedImage    = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());
	
	//If nothing went wrong in loading the image, then--
	if(loadedImage != NULL)
	{
		//Create an optimized image!
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
		//if the image was optimized
		if(optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF);
			//set all pixles of colors that we put in to be transperent
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}

	}
	//Return the optimized image!
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
}

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		return false;
	}

	//Set up the screen
	screen=SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	// If there was an error setting up the screen
	if(screen == NULL)
	{
		return false;
	}

	//Sets the window caption
	SDL_WM_SetCaption("Game", NULL);

	return true;
}

bool load_files()
{
	image      = load_image("images/dirt.bmp");
	background = load_image("images/background.bmp");
	bob        = load_image("images/spritesheet.png");
	enemy      = load_image("images/enemy.png");

	if (image == NULL)
	{
		return (false);
	}
	if(bob == NULL)
	{
		return (false);
	}
	if(background == NULL)
	{
		return (false);
	}
	if(enemy == NULL)
	{
		return (false);
	}
	return (true);
}

void clean_up()
{
	SDL_FreeSurface(image);
	SDL_FreeSurface(background);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(bob);
	SDL_FreeSurface(enemy);

	SDL_Quit();
}

int applydirt()
{
	int x, y;
	x = 0;
	y = 96;

	for (y = 3; y < 30; y++)
	{
		for(x = 0; x < 18; x++)
		{
			if (field.get(x, y) != 0)
				apply_surface(x*32, y*32, image, screen);
		}
	}
	return(0);
}


//int removedirt(int x, int y)
//{
	 



int main(int argc, char* args[])
{
	int update;
	int frame = 0;
	bool cap = true;

	srand(time(NULL));

	int enemie = 0;
	int dead = 0;
	int f = 0;
	int x = 0, y = 0;
	int ex = 288, ey = 512;
	bool quit = false;
	field.init(0);

	if (init() == false)
	{
		return(1);
	}

	load_files();

	//this is sprite number 1
	clip[0].x = 1;
	clip[0].y = 34;
	clip[0].w = 24;
	clip[0].h = 32;
	//#2
	clip[1].x = 27;
	clip[1].y = 34;
	clip[1].w = 24;
	clip[1].h = 32;
	//#3
	clip[2].x = 52;
	clip[2].y = 34;
	clip[2].w = 24;
	clip[2].h = 34;

	clip[3].x = 153;
	clip[3].y = 34;
	clip[3].w = 22;
	clip[3].h = 34;
	//DIGGING SPRITE
	clip[4].x = 128;
	clip[4].y = 186;
	clip[4].w = 24;
	clip[4].h = 48; 

	while(quit == false)
	{
		update = SDL_GetTicks();
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_UP:
						y = y - 32;
						f++;
						break;

					case SDLK_DOWN:
						y = y + 32;
						f++;
						break;

					case SDLK_LEFT:
						x = x - 32;
						f++;
						break;

					case SDLK_RIGHT:
						x = x + 32;
						f++;
						break;

					case SDLK_ESCAPE:
						quit = true;
						break;

					case SDLK_RETURN:
						cap = (!cap);
						break;

					default:
						break;
				}
			}
			else if(event.type == SDL_QUIT)
			{ 
				quit = true;
			}
		}

		enemie = rand() % 4;

		switch(enemie)
		{
			case '0':
				if(field.get(((ex + 32)/32), (ey/32)) != 0)
				{
					ex = ex;
					ey = ey;
				}
				else
				{
					ex = ex + 32;
				}
			case '1':
				if(field.get(((ex -32)/32), (ey/32)) != 0)
				{
					ex = ex;
					ey = ey;
				}
				else
				{
					ex = ex -32;
				}
			case '2':
				if(field.get((ex/32), ((ey + 32)/32)) != 0)
				{
					ex = ex;
					ey = ey;
				}
				else
				{
					ey = ey + 32;
				}
			case '3':
				if(field.get((ex/32), ((ey - 32)/32)) != 0)
				{
					ex = ex;
					ey = ey;
				}
				else
				{
					ey = ey - 32;
				}
		}

		apply_surface(0, 0, background, screen);
		applydirt();

		if((f > 2) && (dead != 1))
		{
			f = 0;
		}

		if(x > 544 && y == 64)
		{
			x = 0;
		}
		else if(x > 544 && y > 64)
		{
			x = 544;
		}

		if(x < 0 && y == 64)
		{
			x = 544;
		}
		else if(x < 0 && y != 64)
		{
			x = 0;
		}

		if(y > 928)
		{
			y = 928;
		}

		if(y < 64)
		{
			y = 64;
		}

		if((x >= ex - 32) && (x <= ex) && (y == ey))
		{
			x = ex - 32;
			dead = 1;
		}

		if((x <= ex + 32) && (x > ex) && (y == ey))
		{
			x = ex + 32;
			dead = 1;
		}

		if((y == ey - 32) && (x == ex))
		{
			y = ey - 32;
			dead = 1;
		}

		if((y == ey + 32) && (x == ex))
		{
			y = ey + 32;
			dead = 1;
		}

		if(dead == 1)
		{
			f = 3;
			y = y - 32;
		}

/*		if(field.get(x, y) == 0)
		{
			f = 4;
		}
*/
		field.set((x / 32), (y / 32), 0);

		apply_surface(x, y, bob, screen, &clip[f]);
		apply_surface(ex, ey, enemy, screen);

		if(SDL_Flip(screen) == -1)
		{
			return(1);
		}

		frame++;
		if(update > 1000)
		{
			std::stringstream caption;
			caption<<"average trames per second:"<<frame / (SDL_GetTicks()/1000.f);
		}
	}

	clean_up();

	return(0);
}
