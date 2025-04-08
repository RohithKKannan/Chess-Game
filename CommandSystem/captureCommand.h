#pragma once

#include "command.h"

class Square;
class Board;
class Piece;

class CaptureCommand : public Command
{
    private:
        Piece* attackingPiece;
        Piece* capturedPiece;
        Square* sourceSquare;
        Square* destinationSquare;

    public:
        CaptureCommand(Board *board, Piece* attackingPiece, Square* sourceSquare, Square* destinationSquare) : Command(board)
        {
            this->attackingPiece = attackingPiece;
            this->sourceSquare = sourceSquare;
            this->destinationSquare = destinationSquare;
        }
        ~CaptureCommand() {};

        bool Execute();
        bool Undo();
};
