#include "header.h"

Piece::Piece(char piece, bool isWhite)
{
    this->piece = piece;
    this->isWhite = isWhite;

    legalPositionData = new LegalPositionData();
}

void Piece::SetPosition(int row, int col)
{
    this->position.row = row;
    this->position.col = col;
}

Piece::~Piece()
{
    delete legalPositionData;
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

bool Piece::CheckIfPositionInLegalPositions(int row, int col)
{
    for(int i = 0; i < legalPositionData->numberOfPositions; i++)
    {
        if(legalPositionData->legalPositions[i].row == row && legalPositionData->legalPositions[i].col == col)
        {
            return true;
        }
    }

    return false;
}
