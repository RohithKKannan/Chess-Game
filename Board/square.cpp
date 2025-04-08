#include <iostream>

#include "square.h"
#include "../Core/core.h"
#include "../Pieces/piece.h"

Square::Square()
{
    this->isMarked = false;
    this->piece = nullptr;

    position = new Position();

    position->row = -1;
    position->col = -1;
}

Square::~Square()
{
    if(position != nullptr)
        delete position;
}

void Square::SetPosition(int row, int col)
{
    this->position->row = row;
    this->position->col = col;
}

void Square::MarkSquare()
{
    this->isMarked = true;
}

void Square::UnMarkSquare()
{
    this->isMarked = false;
}

Piece* Square::ClearPiece()
{
    Piece* pieceToRemove = this->piece;
    this->piece = nullptr;

    return pieceToRemove;
}

void Square::SetPiece(Piece *piece)
{
    this->piece = piece;

    piece->SetPosition(this->position->row, this->position->col);
}

void Square::PrintSquare()
{
    if(piece != nullptr)
    {
        piece->PrintPiece();
        return;
    }
    
    if(isMarked)
    {
        std::cout << "x";
        return;
    }

    std::cout << " ";
}
