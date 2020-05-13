#include "LTexture.h"
#include <iostream>
using namespace std;

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(string path )
{
    //Get rid of preexisting texture
    free();

	//The final texture
    SDL_Texture *Texture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
		cout << "Unable to load image " << path.c_str() << "!" << endl << SDL_GetError() << endl;
    }
    else
    {
		//Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface );

        if( Texture == NULL )
        {
			cout << "Unable to create texture from " << path.c_str() << "!" << endl << SDL_GetError() << endl;
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = Texture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, SDL_Rect *clip)  
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != NULL)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
		SDL_QueryTexture(mTexture, NULL, NULL, &dst.w, &dst.h);
	
	SDL_RenderCopy(renderer, mTexture, clip, &dst);
}

