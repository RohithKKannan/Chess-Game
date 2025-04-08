#pragma once

#include "piece.h"

class Board;

class Queen: public Piece
{
    public:
        Queen(char piece, bool isWhite);
        ~Queen();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};
