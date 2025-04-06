#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Rook;
}

Rook::~Rook()
{

}

void Rook::PreprocessAttackInfo(Board *board)
{
    // Up
    if (!ProcessAttackInDirection(board, this, 1, 0))
        return;

    // Down
    if (!ProcessAttackInDirection(board, this, -1, 0))
        return;

    // Left
    if (!ProcessAttackInDirection(board, this, 0, -1))
        return;

    // Right
    if (!ProcessAttackInDirection(board, this, 0, 1))
        return;
}

void Rook::SetLegalPositions(Board *board)
{
    // Up
    if (!SetLegalMovesInDirection(board, this, 1, 0))
        return;

    // Down
    if (!SetLegalMovesInDirection(board, this, -1, 0))
        return;

    // Left
    if (!SetLegalMovesInDirection(board, this, 0, -1))
        return;

    // Right
    if (!SetLegalMovesInDirection(board, this, 0, 1))
        return;
}
