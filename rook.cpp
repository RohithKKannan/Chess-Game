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

    int count = 0;

    for(int i = 0; i < 8; i++)
    {
        if(i != row)
        {
            legalPositions->positions[count].row = i;
            legalPositions->positions[count].col = col;

            count++;
        }
    }

    for(int j = 0; j < 8; j++)
    {
        if(j != col)
        {
            legalPositions->positions[count].row = row;
            legalPositions->positions[count].col = j;

            count++;
        }
    }

    legalPositions->numberOfPositions = count;

    return legalPositions;
}
