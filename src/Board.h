#ifndef BOARD_H
#define BOARD_H

#include "LTexture.h"
#include <SDL.h>
using namespace std;

//The window we are renderering to
extern SDL_Window *window;
//The window renderer
extern SDL_Renderer *renderer;


enum EMove {UP, DOWN, LEFT, RIGHT};

class Board: public LTexture
{
public:
    Board();

    void randomizeBoard();
    void renderBoard();

    void move(const EMove);

    bool isSolved();
private:
    int spaceRow;
    int spaceCol;

    int currentBoard[4][4];

    static const int solvedBoard[4][4];

    SDL_Rect tiles[16];
};


#endif