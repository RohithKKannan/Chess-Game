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
    if (!board->ProcessAttackInDirection(this, 1, -1))
        return;

    // up-right
    if (!board->ProcessAttackInDirection(this, 1, 1))
        return;

    // down-left
    if (!board->ProcessAttackInDirection(this, -1, -1))
        return;

    // down-right
    if (!board->ProcessAttackInDirection(this, -1, 1))
        return;
}

void Bishop::SetLegalPositions(Board *board)
{
    // up-left
    if (!board->SetLegalMovesInDirection(this, 1, -1))
        return;

    // up-right
    if (!board->SetLegalMovesInDirection(this, 1, 1))
        return;

    // down-left
    if (!board->SetLegalMovesInDirection(this, -1, -1))
        return;

    // down-right
    if (!board->SetLegalMovesInDirection(this, -1, 1))
        return;
}