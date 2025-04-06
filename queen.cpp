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
    if (!board->ProcessAttackInDirection(this, 1, 0))
        return;

    // down
    if (!board->ProcessAttackInDirection(this, -1, 0))
        return;

    // left
    if (!board->ProcessAttackInDirection(this, 0, -1))
        return;

    // right
    if (!board->ProcessAttackInDirection(this, 0, 1))
        return;

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

    cout << "Queen process attack complete!" << endl;
}

void Queen::SetLegalPositions(Board *board)
{
    // up
    if (!board->SetLegalMovesInDirection(this, 1, 0))
        return;

    // down
    if (!board->SetLegalMovesInDirection(this, -1, 0))
        return;

    // left
    if (!board->SetLegalMovesInDirection(this, 0, -1))
        return;

    // right
    if (!board->SetLegalMovesInDirection(this, 0, 1))
        return;

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