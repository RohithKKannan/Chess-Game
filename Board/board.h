#pragma once

#include "../Libraries/Spinach/spinach/core/spn_core.h"

#include "../Core/core.h"
#include <unordered_map>
#include <queue>
#include <string>

class Square;
class Piece;
class Pawn;
class Command;
class LegalPositionData;
class GameManager;

class Board
{
    private:
        Square **board;

        Piece** pieces;
        Piece** whitePieces;
        Piece** blackPieces;
        Pawn** whitePawns;
        Pawn** blackPawns;
        Piece *whiteKing;
        Piece *blackKing;

        int pieceCount = 0;
        int whitePieceCount = 0;
        int blackPieceCount = 0;
        int whitePawnCount = 0;
        int blackPawnCount = 0;

        int blackKnightCount = 0;
        int whiteKnightCount = 0;
        int blackWhiteBishopCount = 0;
        int blackBlackBishopCount = 0;
        int whiteWhiteBishopCount = 0;
        int whiteBlackBishopCount = 0;

        int moveCountWithoutPawnMoveOrCapture = 0;

        std::string boardState;

        std::unordered_map<std::string, int> positionCount;

        std::queue<Command*> commandQueue;
        
        GameManager* gameManager;
        
        Piece* pawnToPromote = nullptr;
        Square* promotionSquare = nullptr;
        Square* promotionSourceSquare = nullptr;

    public:
        Board(GameManager*);
        ~Board();
        
        spn::Image boardImage;
        spn::Image overlayImage;

        void SetupBoard();
        void ClearBoard();
        void DisplayBoard();
        void DisplayBoard(spn::Canvas*);
        
        Square* GetSquareAtCoords(int,int);

        bool CheckForDraw();
        bool CheckIfPositionRepeatedThrice();

        void MarkPositions(LegalPositionData*);
        void UnMarkPositions();

        std::string GetBoardState();
        void TrackBoardState(const std::string &boardState);

        Square* GetSquare(int row, int col);

        void AddPiece(Piece*, int, int);
        void AddPiece(char, int, int);

        void RemovePiece(Piece*);

        bool MovePieceToSquare(Piece*, int, int);

        bool CheckIfPositionProtected(int row, int col, bool protectedByWhite);
        bool CheckIfAnyLegalMovesAvailable(bool isWhite);

        Piece *GetKing(bool isWhite) { return isWhite ? whiteKing : blackKing; };

        void PreprocessAllPieceAttacks();
        void SetAllPieceLegalMoves();
        void ResetAllPieceInfo();
        void ResetPawnsTwoStepsMove(bool isWhite);

        void AddCommandToQueue(Command* command) { commandQueue.push(command); };
        bool ExecuteCommands();
        
        void PromotePawn(PieceType);
};
