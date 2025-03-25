#include "header.h"

Pawn::Pawn(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Pawn;
}

Pawn::~Pawn()
{
}

void Pawn::PreprocessAttackInfo(Board *board)
{
    // up.down-left
    if (!board->ProcessAttackInDirection(this, isWhite ? 1 : -1, -1, true))
        return;

    // up.down-right
    if (!board->ProcessAttackInDirection(this, isWhite ? 1 : -1, 1, true))
        return;
}

void Pawn::SetLegalPositions(Board *board)
{
    // up.down
    if (!board->SetLegalMovesInDirection(this, isWhite ? 1 : -1, 0, true, hasMoved))
        return;

    // up.down-left
    if (!board->SetLegalMovesInDirection(this, isWhite ? 1 : -1, -1, true, hasMoved))
        return;

    // up.down-right
    if (!board->SetLegalMovesInDirection(this, isWhite ? 1 : -1, 1, true, hasMoved))
        return;
}