#include "header.h"

Square::Square()
{
    this->piece = NULL;
}

Square::~Square()
{

}

void Square::SetPiece(Piece *piece)
{
    this->piece = piece;
}

void Square::PrintSquare()
{
    if(piece == NULL)
    {
        cout << " ";
        return;
    }

    cout << piece->piece;
}