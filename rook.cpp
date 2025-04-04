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
    if (!board->ProcessAttackInDirection(this, 1, 0))
        return;

    // Down
    if (!board->ProcessAttackInDirection(this, -1, 0))
        return;

    // Left
    if (!board->ProcessAttackInDirection(this, 0, -1))
        return;

    // Right
    if (!board->ProcessAttackInDirection(this, 0, 1))
        return;
}

void Rook::SetLegalPositions(Board *board)
{
    // Up
    if (!board->SetLegalMovesInDirection(this, 1, 0))
        return;

    // Down
    if (!board->SetLegalMovesInDirection(this, -1, 0))
        return;

    // Left
    if (!board->SetLegalMovesInDirection(this, 0, -1))
        return;

    // Right
    if (!board->SetLegalMovesInDirection(this, 0, 1))
        return;
}
