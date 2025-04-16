#include <iostream>

#include "bishop.h"
#include "../Utils/utilities.h"

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
    if (!ProcessAttackInDirection(board, this, 1, -1))
        return;

    // up-right
    if (!ProcessAttackInDirection(board, this, 1, 1))
        return;

    // down-left
    if (!ProcessAttackInDirection(board, this, -1, -1))
        return;

    // down-right
    if (!ProcessAttackInDirection(board, this, -1, 1))
        return;
}

void Bishop::SetLegalPositions(Board *board)
{
    // up-left
    if (!SetLegalMovesInDirection(board, this, 1, -1))
        return;

    // up-right
    if (!SetLegalMovesInDirection(board, this, 1, 1))
        return;

    // down-left
    if (!SetLegalMovesInDirection(board, this, -1, -1))
        return;

    // down-right
    if (!SetLegalMovesInDirection(board, this, -1, 1))
        return;
}
