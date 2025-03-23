#include "header.h"

Queen::Queen(char piece, bool isWhite) : Piece(piece, isWhite)
{
}

Queen::~Queen()
{
}

void Queen::PreprocessAttackInfo(Board *board)
{
    // up
    if (!board->ProcessAttackInDirection(this, 1, 0, true))
        return;

    // down
    if (!board->ProcessAttackInDirection(this, -1, 0, true))
        return;

    // left
    if (!board->ProcessAttackInDirection(this, 0, -1, true))
        return;

    // right
    if (!board->ProcessAttackInDirection(this, 0, 1, true))
        return;

    // up-left
    if (!board->ProcessAttackInDirection(this, 1, -1, true))
        return;

    // up-right
    if (!board->ProcessAttackInDirection(this, 1, 1, true))
        return;

    // down-left
    if (!board->ProcessAttackInDirection(this, -1, -1, true))
        return;

    // down-right
    if (!board->ProcessAttackInDirection(this, -1, 1, true))
        return;
}

void Queen::SetLegalPositions(Board *board)
{
    // up
    if (!board->SetLegalMovesInDirection(this, 1, 0, true))
        return;

    // down
    if (!board->SetLegalMovesInDirection(this, -1, 0, true))
        return;

    // left
    if (!board->SetLegalMovesInDirection(this, 0, -1, true))
        return;

    // right
    if (!board->SetLegalMovesInDirection(this, 0, 1, true))
        return;

    // up-left
    if (!board->SetLegalMovesInDirection(this, 1, -1, true))
        return;

    // up-right
    if (!board->SetLegalMovesInDirection(this, 1, 1, true))
        return;

    // down-left
    if (!board->SetLegalMovesInDirection(this, -1, -1, true))
        return;

    // down-right
    if (!board->SetLegalMovesInDirection(this, -1, 1, true))
        return;
}