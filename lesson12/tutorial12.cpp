//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

//Sceen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *startStop = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0xF0, 0xFF, 0xF0 };

SDL_Surface *load_image( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename.c_str() );

	//If the image loaded
	if( loadedImage != NULL )
	{   
		//Create an optimized surface
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old surface
		SDL_FreeSurface( loadedImage );

		//If the surface was optimized
		if( optimizedImage != NULL )
		{   
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
		}
	}   

	//Return the optimized surface
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Holds offsets
	SDL_Rect offsets;

	//GEt offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface( source, clip, destination, &offset );

int main( int argc, char* args[] )
{
	//Quit flag
	bool quit = false;

	//The timer starting time
	Unit32 start = 0;

	//The timer start/stop flag
	bool running = true;

	//Start the timer
	start = SDL_GetTicks();

	//While the user hasn't quit
	while( quit == false )
	{
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
			//If a key was pressed
			if( event.type == SDL_KEYDOWN )
			{
				//If s was pressed
				if( event.key.keysym.sym == SDLK_s )
				{
					//If the timer is running
					if( running == true )
					{
						//Stop the timer
						running = false;
						start = 0;
					}
					else
					{
						//Start the timer
						running = true;
						start = SDL_GetTicks();
					}
				}
			}
		}
		//If the timer is running
		if( running == true )
		{
			//The timer's time as a string
			std::stringstream time;

			//Convert the timer's time to a string
			time << "Timer: " << SDL_GetTicks() - start;

			//REnter the time surface
			seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );
			
			//Apply the time surface
			apply_surface( ( SCREEN_WIDTH - seconds -> w ) / 2, 50, seconds, screen );

			//Free the time surface
			SDL_FreeSurface( seconds );
		}

		//Update the screen
		if( SDL_Flip( screen ) == -1 )
		{
			return 1;
		}
	}

