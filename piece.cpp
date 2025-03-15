#include "header.h"

Piece::Piece(char piece, bool isWhite)
{
    this->piece = piece;
    this->isWhite = isWhite;
}

Piece::~Piece()
{

}

void Piece::PrintPiece()
{
    cout << this->piece;
}
