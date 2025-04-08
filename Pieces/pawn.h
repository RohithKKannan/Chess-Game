#pragma once

#include "piece.h"

class Board;

class Pawn: public Piece
{
    private:
        bool hasMovedTwoSteps;
        bool canMoveTwoSteps;
        bool canEnPassantLeft;
        bool canEnPassantRight;
    public:
        Pawn(char piece, bool isWhite);
        ~Pawn();

        void SetHasMovedTwoSteps(bool hasMovedTwoSteps) { this->hasMovedTwoSteps = hasMovedTwoSteps; };
        bool GetHasMovedTwoSteps() { return hasMovedTwoSteps; };

        bool GetCanMoveTwoSteps() { return canMoveTwoSteps; };
        void SetCanMoveTwoSteps() { canMoveTwoSteps = true; };
        bool GetCanEnPassantLeft() { return canEnPassantLeft; };
        void SetCanEnPassantLeft() { canEnPassantLeft = true; };
        bool GetCanEnPassantRight() { return canEnPassantRight; };
        void SetCanEnPassantRight() { canEnPassantRight = true; };

        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};
