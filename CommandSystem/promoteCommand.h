#pragma once

#include "../Core/core.h"
#include "command.h"

class Piece;
class Board;
class Square;

class PromoteCommand : public Command
{
    private:
        PieceType pieceType;
        Piece* pawnToPromote;
        Piece* promotedPiece;
        Square* promotionSquare;
        Square* sourceSquare;

    public:
        PromoteCommand(Board *board, PieceType pieceType, Piece* pawnToPromote, Square* promotionSquare, Square* sourceSquare) : Command(board)
        {
            this->pieceType = pieceType;
            this->pawnToPromote = pawnToPromote;
            this->promotionSquare = promotionSquare;
            this->sourceSquare = sourceSquare;
        }
        ~PromoteCommand() {};

        bool Execute();
        bool Undo();
};
