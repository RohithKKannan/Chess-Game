#include "header.h"

Bishop::Bishop(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Bishop;
}

Bishop::~Bishop()
{
}

void Bishop::PreprocessAttackInfo(Board *board)
{
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

void Bishop::SetLegalPositions(Board *board)
{
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