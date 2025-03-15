#include "header.h"

Piece::Piece(char piece, bool isWhite)
{
    this->piece = piece;
    this->isWhite = isWhite;
}

void Piece::SetPosition(int row, int col)
{
    this->position.row = row;
    this->position.col = col;
}

Piece::~Piece()
{

}

void Piece::PrintPiece()
{
    cout << this->piece;
}

Position Piece::GetPosition()
{
    Position position;

    position.row = this->position.row;
    position.col = this->position.col;

    return position;
}
