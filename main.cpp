#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "LTexture.h"
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

//The window we are renderering to
SDL_Window *window = NULL;
//The window renderer
SDL_Renderer *renderer = NULL;

bool Restart = false;
bool Exit = false;

bool init();
bool loadMedia(LTexture &, LTexture &, Board &);
void showIntro(LTexture &); 
void inGame(Board &);
void gameWon(LTexture &);
void close(LTexture &, LTexture &, Board &);


int main(int argc, char * argv[])
{
	srand(time(0));
	LTexture introduction;
	LTexture won;
	Board game;

	if (!init())
	{
		cout << "Failed to initialize!\n";
	}
	else
	{
		//Load media
		if (!loadMedia(introduction, won, game))
		{
			cout << "Failed to load media!\n";
		}
		else
		{
			showIntro(introduction);
			if (Exit) goto closeWindow;

			restart:
			inGame(game);
			if (Exit) goto closeWindow;

			gameWon(won);
			if (Exit) goto closeWindow;
			if (Restart) goto restart;
		}
    }

	closeWindow:
	close(introduction, won, game);

	system("pause");
    return 0;
}


bool init()
{ 
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Fifteen Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}

	return success;
}


bool loadMedia(LTexture &introduction, LTexture &won, Board &game) 
{
	//Loading success flag
	bool success = true;

	//Load introduction texture
	if (!introduction.loadFromFile("intro.bmp"))
	{
		cout << "Failed to load introduction texture!\n";
		success = false;
	}

	//Load game won texture
	if (!won.loadFromFile("won.bmp"))
	{
		cout << "Failed to load game won texture!\n";
		success = false;
	}

	//Load board texture
	if (!game.loadFromFile("puzzle.bmp"))
	{
		cout << "Failed to load board texture!\n";
		success = false;
	}

	return success;
}

void showIntro(LTexture &introduction) 
{
	//Event handler
	SDL_Event event;

	bool quit = false;
	bool startGame = false;

	//While application is running
	while (!quit)
	{
		SDL_WaitEvent(&event);
	
		if(event.type == SDL_QUIT)
		{
			quit = true;
		}
		//User presses a key
		else if( event.type == SDL_KEYDOWN )
		{
			switch( event.key.keysym.sym )
			{
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					startGame = true;
					break;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Render introduction to screen
		introduction.render(0, 0);

		//Update screen
		SDL_RenderPresent(renderer);

		if(startGame)
			break;

		if (quit) 
		{
			Restart = false;
			Exit = true;
		}
	}
}

void inGame(Board &game) 
{
	Restart = false;
	Exit = false;

	game.randomizeBoard();

	SDL_Event event;
	bool quit = false;

	//While application is running
	while (!quit)
	{
		SDL_WaitEvent(&event);

		if(event.type == SDL_QUIT)
		{
			quit = true;
		}
		//User presses a key
		else if( event.type == SDL_KEYDOWN )
		{
			switch( event.key.keysym.sym )
			{
				case SDLK_UP:
					game.move(UP);
					break;
				case SDLK_DOWN:
					game.move(DOWN);
					break;             
				case SDLK_LEFT:
					game.move(LEFT);
					break;       
				case SDLK_RIGHT:
					game.move(RIGHT);
					break;
				default:  break;
			}
		}	

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); //white
		// SDL_SetRenderDrawColor(renderer,0, 0,0, 0xFF);          //black     
		SDL_RenderClear(renderer);
		
		//render board
		game.renderBoard();

		//Update screen
		SDL_RenderPresent(renderer);

		if(game.isSolved())
			break;

		if (quit) 
		{
			Restart = false;
			Exit = true;
		}
	}
}

void gameWon(LTexture &won) 
{
	//Event handler
	SDL_Event event;

	bool quit = false;

	//While application is running
	while (!quit)
	{
		SDL_WaitEvent(&event);
	
		if(event.type == SDL_QUIT)
		{
			quit = true;
		}
		//User presses a key
		else if( event.type == SDL_KEYDOWN )
		{
			switch( event.key.keysym.sym )
			{
				case SDLK_RETURN:
				case SDLK_KP_ENTER:
					Restart = true;
					Exit = false;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Render introduction to screen
		won.render(0, 0);

		//Update screen
		SDL_RenderPresent(renderer);

		if(Restart)
			break;
		
		if (quit) 
		{
			Restart = false;
			Exit = true;
		}
	}
}

void close(LTexture &introduction, LTexture &won, Board &game) 
{
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	introduction.free();
	won.free();
	game.free();

	//Quit SDL subsystems
	SDL_Quit();
}