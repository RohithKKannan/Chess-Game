#include "header.h"

Knight::Knight(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Knight::~Knight()
{

}

void Knight::PreprocessAttackInfo(Board *board)
{
    if (!board->ProcessKnightAttack(this, 1, 2))
        return;

    if (!board->ProcessKnightAttack(this, 1, -2))
        return;

    if (!board->ProcessKnightAttack(this, -1, 2))
        return;

    if (!board->ProcessKnightAttack(this, -1, -2))
        return;

    if (!board->ProcessKnightAttack(this, 2, 1))
        return;

    if (!board->ProcessKnightAttack(this, 2, -1))
        return;

    if (!board->ProcessKnightAttack(this, -2, 1))
        return;

    if (!board->ProcessKnightAttack(this, -2, -1))
        return;
}

void Knight::SetLegalPositions(Board *board)
{
    if (!board->SetLegalMoveForKnight(this, 1, 2))
        return;

    if (!board->SetLegalMoveForKnight(this, 1, -2))
        return;

    if (!board->SetLegalMoveForKnight(this, -1, 2))
        return;

    if (!board->SetLegalMoveForKnight(this, -1, -2))
        return;

    if (!board->SetLegalMoveForKnight(this, 2, 1))
        return;

    if (!board->SetLegalMoveForKnight(this, 2, -1))
        return;

    if (!board->SetLegalMoveForKnight(this, -2, 1))
        return;

    if (!board->SetLegalMoveForKnight(this, -2, -1))
        return;
}