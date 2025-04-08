#pragma once

#include "piece.h"

class Board;

class Knight: public Piece
{
    public:
        Knight(char piece, bool isWhite);
        ~Knight();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
        bool ProcessKnightAttack(Board *, int, int);
        bool SetLegalMoveForKnight(Board *, int, int);
};
