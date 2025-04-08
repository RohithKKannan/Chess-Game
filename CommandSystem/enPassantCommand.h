#pragma once

#include "command.h"

class Square;
class Piece;
class Pawn;
class Board;

class EnPassantCommand : public Command
{
    private:
        Pawn* pawn;
        Piece* capturedPawn;
        Square* sourceSquare;
        Square* destinationSquare;
        Square* capturingSquare;

    public:
        EnPassantCommand(Board *board, Pawn* pawn, Square* source, Square* destination, Square* captureSquare) : Command(board)
        {
            this->pawn = pawn;
            this->capturedPawn = nullptr;
            this->sourceSquare = source;
            this->destinationSquare = destination;
            this->capturingSquare = captureSquare;
        };
        ~EnPassantCommand() {};

        bool Execute();
        bool Undo();
};
