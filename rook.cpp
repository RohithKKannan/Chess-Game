#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

void Rook::PreprocessAttackInfo(Board *board)
{
    // Up
    if (!board->ProcessAttackInDirection(this, 1, 0, false))
        return;

    // Down
    if (!board->ProcessAttackInDirection(this, -1, 0, false))
        return;

    // Left
    if (!board->ProcessAttackInDirection(this, 0, -1, false))
        return;

    // Right
    if (!board->ProcessAttackInDirection(this, 0, 1, false))
        return;
}

void Rook::SetLegalPositions(Board *board)
{
    // Up
    if (!board->SetLegalMovesInDirection(this, 1, 0, false, false))
        return;

    // Down
    if (!board->SetLegalMovesInDirection(this, -1, 0, false, false))
        return;

    // Left
    if (!board->SetLegalMovesInDirection(this, 0, -1, false, false))
        return;

    // Right
    if (!board->SetLegalMovesInDirection(this, 0, 1, false, false))
        return;
}
