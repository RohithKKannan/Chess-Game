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
        InputState currentInputState;
        
        spn::Image whiteQueenImage;
        spn::Image whiteBishopImage;
        spn::Image whiteKnightImage;
        spn::Image whiteRookImage;
        
        spn::Image blackQueenImage;
        spn::Image blackBishopImage;
        spn::Image blackKnightImage;
        spn::Image blackRookImage;

    public:
        GameManager();
        ~GameManager();
        
        void StartGame();
        bool Game();
        bool InitiateTurn();

        Square *SelectSquareFromInput();
        bool ParseInput(std::string *, int *, int *);
        
        void InitGame();
        void Update(spn::Canvas*);
        void ProcessInput(const SDL_Event*);
        void ProcessMouseClick(int, int);
        
        void GUIStartGame();
        void GUIInitiateTurn();
        void GUIEndGame();
        
    	void SourceSelected(Square*);
    	void PieceSelected(Piece*);
    	void PieceDeselected();
    	void DestinationSelected(Square*);
        
        void SelectSquareAt(int,int);
        
        void MoveComplete();
        void PrepForNextTurn();
        
        void InitiatePromotePawn();
        void PromotePieceSelected(int, int);
    	void DisplayPromotionPopup(spn::Canvas* canvas);
    	void PromotionComplete();
};
