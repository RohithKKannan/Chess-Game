#pragma once

#include <string>

#include "../Core/core.h"

#include "../Libraries/Spinach/spinach/core/spn_core.h"

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
        
        void InitGame();
        void Update(spn::Canvas*);
        void ProcessInput(const SDL_Event*);

        Square *SelectSquareFromInput();
        bool ParseInput(std::string *, int *, int *);
};
