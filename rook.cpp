#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

LegalPositions* Rook::GetLegalPositions(int row, int col)
{
    LegalPositions *legalPositions = new LegalPositions();

    Position positions[100];

    int count = 0;

    for(int i = 0; i < 8; i++)
    {
        if(i != row)
        {
            positions[count].row = i;
            positions[count].col = col;

            count++;
        }
    }

    for(int j = 0; j < 8; j++)
    {
        if(j != col)
        {
            positions[count].row = row;
            positions[count].col = j;

            count++;
        }
    }

    legalPositions->positions = positions;
    legalPositions->numberOfPositions = count;

    return legalPositions;
}
