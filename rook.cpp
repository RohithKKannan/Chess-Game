#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

void Rook::PreprocessAttackInfo(Board *board)
{
    cout << endl
         << "Processing Attack in Direction : " << 1 << " " << 0 << endl;
    // Up
    if (!board->ProcessAttackInDirection(this, 1, 0, true))
        return;

    cout << endl
         << "Processing Attack in Direction : " << -1 << " " << 0 << endl;

    // Down
    if (!board->ProcessAttackInDirection(this, -1, 0, true))
        return;

    cout << endl
         << "Processing Attack in Direction : " << 0 << " " << -1 << endl;

    // Left
    if (!board->ProcessAttackInDirection(this, 0, -1, true))
        return;

    cout << endl
         << "Processing Attack in Direction : " << 0 << " " << 1 << endl;

    // Right
    if (!board->ProcessAttackInDirection(this, 0, 1, true))
        return;
}

void Rook::SetLegalPositions(Board *board)
{
    cout << endl
         << "Setting legal positions in Direction : " << 1 << " " << 0 << endl;

    // Up
    if (!board->SetLegalMovesInDirection(this, 1, 0, true))
        return;

    cout << endl
         << "Setting legal positions in Direction : " << -1 << " " << 0 << endl;

    // Down
    if (!board->SetLegalMovesInDirection(this, -1, 0, true))
        return;

    cout << endl
         << "Setting legal positions in Direction : " << 0 << " " << -1 << endl;

    // Left
    if (!board->SetLegalMovesInDirection(this, 0, -1, true))
        return;

    cout << endl
         << "Setting legal positions in Direction : " << 0 << " " << 1 << endl;

    // Right
    if (!board->SetLegalMovesInDirection(this, 0, 1, true))
        return;
}
