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
    if (!ProcessAttackInDirection(board, this, 1, 0))
        return;

    // down
    if (!ProcessAttackInDirection(board, this, -1, 0))
        return;

    // left
    if (!ProcessAttackInDirection(board, this, 0, -1))
        return;

    // right
    if (!ProcessAttackInDirection(board, this, 0, 1))
        return;

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

void Queen::SetLegalPositions(Board *board)
{
    // up
    if (!SetLegalMovesInDirection(board, this, 1, 0))
        return;

    // down
    if (!SetLegalMovesInDirection(board, this, -1, 0))
        return;

    // left
    if (!SetLegalMovesInDirection(board, this, 0, -1))
        return;

    // right
    if (!SetLegalMovesInDirection(board, this, 0, 1))
        return;

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