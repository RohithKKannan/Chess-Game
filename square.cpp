#include "header.h"

Square::Square()
{
    this->isMarked = false;
    this->piece = NULL;
}

Square::~Square()
{

}

void Square::SetPosition(int row, int col)
{
    this->position.row = row;
    this->position.col = col;
}

void Square::MarkSquare()
{
    this->isMarked = true;
}

void Square::UnMarkSquare()
{
    this->isMarked = false;
}

void Square::ClearPiece()
{
    delete this->piece;
    this->piece = NULL;
}

void Square::SetPiece(Piece *piece)
{
    this->piece = piece;
}

void Square::PrintSquare()
{
    if(isMarked)
    {
        cout << "x";
        return;
    }

    if(piece == NULL)
    {
        cout << " ";
        return;
    }

    piece->PrintPiece();
}
