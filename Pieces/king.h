#pragma once

#include "piece.h"

class Board;

class King: public Piece
{
    private:
        bool isShortCastlingPossible;
        bool isLongCastlingPossible;
    public:
        King(char piece, bool isWhite);
        ~King();
        bool GetIsShortCastlingPossible() { return isShortCastlingPossible; };
        void SetIsShortCastlingPossible() { isShortCastlingPossible = true; };
        bool GetIsLongCastlingPossible() { return isLongCastlingPossible; };
        void SetIsLongCastlingPossible() { isLongCastlingPossible = true; };
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};
