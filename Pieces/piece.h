#pragma once

#include "../Core/core.h"

#include "../Libraries/Spinach/spinach/core/spn_core.h"

class Position;
class LegalPositionData;
class Square;
class Board;

class Piece
{
    protected:
        char piece;
        int moveCount = 0;
        bool isWhite;
        PieceType pieceType;

        Position position;
        LegalPositionData *legalPositionData = nullptr;

        bool isPinned;
        Piece *pinningPiece = nullptr;

        bool isInCheck;
        int attackerCount = 0;
        Square **attackPath = new Square *[100];
        int attackPathSquareCount;

    public:
        Piece(char, bool);
        virtual ~Piece();
        
        spn::Image pieceImage;

        void SetPosition(int, int);
        void SetPieceMoved() { moveCount++; };
        void UndoPieceMoved() { if(moveCount > 0) moveCount--; };
        void PrintPiece();
        char GetPieceChar() { return piece; };

        bool GetIsKing() { return pieceType == PieceType::King; };
        bool GetIsWhite() { return isWhite; };
        bool GetIsInCheck() { return isInCheck; };
        bool GetIsPinned() { return isPinned; };
        int GetAttackerCount() { return attackerCount; };
        int GetMoveCount() { return moveCount; };
        Position GetPosition() { return position; };
        PieceType GetPieceType() { return pieceType; };
        LegalPositionData* GetLegalPositionData() { return legalPositionData; };

        void SetPieceIsPinned() { isPinned = true; };
        void AddPieceToPinningPiece(Piece *piece) { pinningPiece = piece; };
        void SetKingIsInCheck()
        {
            attackerCount++;
            isInCheck = true;
        };

        virtual void PreprocessAttackInfo(Board *) = 0;
        virtual void SetLegalPositions(Board *) = 0;
        bool CheckIfAttackPathContainsPosition(int row, int col);
        bool CheckIfPositionInLegalPositionsWithoutKing(int, int);
        void AddSquareToAttackPath(Square *square) { attackPath[attackPathSquareCount++] = square; };
        void ResetPieceInfo();
};
