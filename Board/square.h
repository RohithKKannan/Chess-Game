#pragma once

#include "../Libraries/Spinach/spinach/core/spn_core.h"

class Position;
class Piece;

class Square
{
    private:
        Position* position;
        bool isMarked;
        Piece* piece;

    public:
        Square();
        ~Square();
        
        void SetPosition(int, int);
        Position* GetPosition() { return position; };
        
        void MarkSquare();
        void UnMarkSquare();
        
        void SetPiece(Piece *);
        Piece* GetPiece() { return piece; };
        Piece* ClearPiece();
        
        void PrintSquare();
};
