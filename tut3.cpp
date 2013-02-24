// THIS IS A REVISED VERSION OF IMAGE LOADING FROM THE PREVIOUS TUTORIALS SO
// OTHER IMAGE TYPES SUCH AS BMP, PNM, XPM, LBM, JPEG, PNG, ETC.
//
// "PNGs have excellent lossless compression"

#include "SDL/SDL_image.h"

SDL_Surface *load_image(std::string filename)
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;
	
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	//Load the image using SDL_image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if(loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old iamge
		SDL_FreeSurface(loadedImage);
	}

	//Return the optimized image
	return optimizedImage;
}



