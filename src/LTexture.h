#ifndef LTECTURE_H
#define LTECTURE_H

#include <string>
#include <SDL.h>
using namespace std;

//The window we are renderering to
extern SDL_Window *window;
//The window renderer
extern SDL_Renderer *renderer;


//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Rect *clip = NULL );

protected:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif