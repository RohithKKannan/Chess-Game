#pragma once

#include "../Core/core.h"
#include "command.h"

class Piece;
class Board;

class PromoteCommand : public Command
{
    private:
        PieceType pieceType;
        Piece* pawnToPromote;
        Piece* promotedPiece;

    public:
        PromoteCommand(Board *board, PieceType pieceType, Piece* pawnToPromote) : Command(board)
        {
            this->pieceType = pieceType;
            this->pawnToPromote = pawnToPromote;
        }
        ~PromoteCommand() {};

        bool Execute();
        bool Undo();
};
