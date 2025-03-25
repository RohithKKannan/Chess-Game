#include "header.h"

Queen::Queen(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Queen;
}

Queen::~Queen()
{
}

void Queen::PreprocessAttackInfo(Board *board)
{
    // up
    if (!board->ProcessAttackInDirection(this, 1, 0, false))
        return;

    // down
    if (!board->ProcessAttackInDirection(this, -1, 0, false))
        return;

    // left
    if (!board->ProcessAttackInDirection(this, 0, -1, false))
        return;

    // right
    if (!board->ProcessAttackInDirection(this, 0, 1, false))
        return;

    // up-left
    if (!board->ProcessAttackInDirection(this, 1, -1, false))
        return;

    // up-right
    if (!board->ProcessAttackInDirection(this, 1, 1, false))
        return;

    // down-left
    if (!board->ProcessAttackInDirection(this, -1, -1, false))
        return;

    // down-right
    if (!board->ProcessAttackInDirection(this, -1, 1, false))
        return;
}

void Queen::SetLegalPositions(Board *board)
{
    // up
    if (!board->SetLegalMovesInDirection(this, 1, 0, false, false))
        return;

    // down
    if (!board->SetLegalMovesInDirection(this, -1, 0, false, false))
        return;

    // left
    if (!board->SetLegalMovesInDirection(this, 0, -1, false, false))
        return;

    // right
    if (!board->SetLegalMovesInDirection(this, 0, 1, false, false))
        return;

    // up-left
    if (!board->SetLegalMovesInDirection(this, 1, -1, false, false))
        return;

    // up-right
    if (!board->SetLegalMovesInDirection(this, 1, 1, false, false))
        return;

    // down-left
    if (!board->SetLegalMovesInDirection(this, -1, -1, false, false))
        return;

    // down-right
    if (!board->SetLegalMovesInDirection(this, -1, 1, false, false))
        return;
}