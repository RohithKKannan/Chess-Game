#pragma once

#include <string>

#include "../Core/core.h"

class Square;
class Board;
class Piece;

class GameManager
{
    private:
        Board *board;
        Piece *selectedPiece;
        Square *selectedSquare;
        GameState currentGameState;

    public:
        GameManager();
        ~GameManager();
        
        void StartGame();
        bool Game();
        bool InitiateTurn();

        Square *SelectSquareFromInput();
        bool ParseInput(std::string *, int *, int *);
};
