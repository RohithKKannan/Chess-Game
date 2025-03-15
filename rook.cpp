#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

LegalPositions* Rook::GetLegalPositions(int row, int col, Board* board)
{
    LegalPositions *legalPositions = new LegalPositions();

    int count = 0;

    // Change iteraction origin from row, col

    for(int i = row + 1; i < 8; i++)
    {
        if(board->board[i][col].piece != NULL)
        {
            legalPositions->positions[count].row = i;
            legalPositions->positions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositions->positions[count].row = i;
        legalPositions->positions[count].col = col;
        
        count++;
    }

    for(int i = row - 1; i >= 0; i --)
    {
        if(board->board[i][col].piece != NULL)
        {
            legalPositions->positions[count].row = i;
            legalPositions->positions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositions->positions[count].row = i;
        legalPositions->positions[count].col = col;
        
        count++;
    }

    for(int j = col + 1; j < 8; j++)
    {
        if(board->board[row][j].piece != NULL)
        {
            legalPositions->positions[count].row = row;
            legalPositions->positions[count].col = j;

            count++;
        }

        legalPositions->positions[count].row = row;
        legalPositions->positions[count].col = j;

        count++;
    }

    for(int j = col - 1; j >= 0; j--)
    {
        if(board->board[row][j].piece != NULL)
        {
            legalPositions->positions[count].row = row;
            legalPositions->positions[count].col = j;

            count++;
        }

        legalPositions->positions[count].row = row;
        legalPositions->positions[count].col = j;

        count++;
    }

    legalPositions->numberOfPositions = count;

    return legalPositions;
}
