#include "Board.h"

const int Board::solvedBoard[4][4] = {{1, 2, 3, 4},
                                     {5, 6, 7, 8},
                                     {9, 10, 11, 12},
                                     {13, 14, 15, 16}};

Board::Board()
    :spaceRow(3), spaceCol(3), LTexture()
{
    //initialize currentBoard[4][4]
    int k=1;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            currentBoard[i][j] = k;
            k++;
        }
    }

    //initialize tiles[16]
    for (int i = 1; i < 16; i++)
    {
        tiles[i].x = (i % 4 != 0)? (i % 4 - 1) * 100 : 300;
        tiles[i].y = (i - 1) / 4  * 100;
        tiles[i].w = 100;
        tiles[i].h = 100;
    }
}

void Board::randomizeBoard()
{
    for(int i=0; i<1000; i++)
    {
        int random = rand()%4;
        switch(random)
        {
        case 0:
            move(UP);
            break;
        case 1:
            move(DOWN);
            break;
        case 2:
            move(LEFT);
            break;
        case 3:
            move(RIGHT);
            break;
        }
    }
}

void Board::renderBoard()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            int tileNumber = currentBoard[i][j];
            if(tileNumber != 16)
                render(j*100, i*100, &tiles[tileNumber]);
        }
    }
}
    
void Board::move(const EMove direction)
{
    int moveRow = spaceRow;
    int moveCol = spaceCol;

    switch (direction) 
    {
        case UP:
            moveRow = spaceRow + 1;
            break;
        case DOWN:
            moveRow = spaceRow - 1;
            break;
        case LEFT:
            moveCol = spaceCol + 1;
            break;
        case RIGHT:
            moveCol = spaceCol - 1;
            break;
    }

    // Make sure that the square to be moved is in bounds
    if (moveRow >= 0 && moveRow < 4 && moveCol >= 0 && moveCol < 4) 
    {
        currentBoard[spaceRow][spaceCol] = currentBoard[moveRow][moveCol];
        currentBoard[moveRow][moveCol] = 16;

        switch (direction) 
        {
            case UP:
                spaceRow++;
                break;
            case DOWN:
                spaceRow--;
                break;
            case LEFT:
                spaceCol++;
                break;
            case RIGHT:
                spaceCol--;
                break;
        }
    } 
}

bool Board::isSolved()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if( currentBoard[i][j] != solvedBoard[i][j])
                return false;
        }
    }

    return true;
}