#pragma once

#include "command.h"

class Square;
class Board;
class King;
class Rook;

class CastleCommand : public Command
{
    private:
        King* king;
        Rook* rook;

        Square* kingSource;
        Square* kingDestination;
        Square* rookSource;
        Square* rookDestination;

    public:
        CastleCommand(Board *board, King *king, Rook *rook, Square* kingSource, Square *kingDestination, Square* rookSource, Square* rookDestination) : Command(board)
        {
            this->king = king;
            this->rook = rook;
            this->kingSource = kingSource;
            this->kingDestination = kingDestination;
            this->rookSource = rookSource;
            this->rookDestination = rookDestination;
        }
        ~CastleCommand() {};

        bool Execute();
        bool Undo();
};
