#pragma once

#include "piece.h"

class Board;

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};
