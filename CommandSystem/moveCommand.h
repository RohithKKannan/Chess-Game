#pragma once

#include "command.h"

class Square;
class Board;
class Piece;

class MoveCommand : public Command
{
    private:
        Piece* piece;
        Square* sourceSquare;
        Square* destinationSquare;

    public:
        MoveCommand(Board* board, Piece* piece, Square* sourceSquare, Square* destinationSquare) : Command(board)
        {
            this->piece = piece;
            this->sourceSquare = sourceSquare;
            this->destinationSquare = destinationSquare;
        }
        ~MoveCommand() {};

        bool Execute();
        bool Undo();
};
