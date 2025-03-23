#include "header.h"

Piece::Piece(char piece, bool isWhite)
{
    this->piece = piece;
    this->isWhite = isWhite;

    legalPositionData = new LegalPositionData();

    pinningPiece = nullptr;
    attackingPieces = new Piece *[100];
    attackPath = new Square *[100];
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

bool Piece::CheckIfPositionInLegalPositionsWithoutKing(int row, int col)
{
    for (int i = 0; i < legalPositionData->numberOfPositionsWithoutKing; i++)
    {
        if (legalPositionData->legalPositionsWithoutKing[i].row == row && legalPositionData->legalPositionsWithoutKing[i].col == col)
        {
            return true;
        }
    }

    return false;
}

void Piece::ResetPiecesInfo()
{
    legalPositionData->numberOfPositions = 0;
    legalPositionData->numberOfPositionsWithoutKing = 0;

    attackPathSquareCount = 0;
    attackingPieces = 0;

    pinningPiece = nullptr;

    isPinned = false;
    isInCheck = false;
}

bool Piece::CheckIfAttackPathContainsPosition(int row, int col)
{
    Position position;

    for (int i = 0; i < attackPathSquareCount; i++)
    {
        position = attackPath[i]->GetPosition();
        if (position.row == row && position.col == col)
            return true;
    }

    return false;
}
