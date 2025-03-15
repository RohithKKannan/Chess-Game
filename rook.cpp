#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

void Rook::GetLegalPositions(int row, int col, Board* board, LegalPositionData* legalPositions)
{
    int count = 0;

    // Change iteraction origin from row, col

    for(int i = row + 1; i < BOARD_SIZE; i++)
    {
        if(board->board[i][col].piece != NULL)
        {
            legalPositions->legalPositions[count].row = i;
            legalPositions->legalPositions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositions->legalPositions[count].row = i;
        legalPositions->legalPositions[count].col = col;
        
        count++;
    }

    for(int i = row - 1; i >= 0; i --)
    {
        if(board->board[i][col].piece != NULL)
        {
            legalPositions->legalPositions[count].row = i;
            legalPositions->legalPositions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositions->legalPositions[count].row = i;
        legalPositions->legalPositions[count].col = col;
        
        count++;
    }

    for(int j = col + 1; j < BOARD_SIZE; j++)
    {
        if(board->board[row][j].piece != NULL)
        {
            legalPositions->legalPositions[count].row = row;
            legalPositions->legalPositions[count].col = j;

            count++;
        }

        legalPositions->legalPositions[count].row = row;
        legalPositions->legalPositions[count].col = j;

        count++;
    }

    for(int j = col - 1; j >= 0; j--)
    {
        if(board->board[row][j].piece != NULL)
        {
            legalPositions->legalPositions[count].row = row;
            legalPositions->legalPositions[count].col = j;

            count++;
        }

        legalPositions->legalPositions[count].row = row;
        legalPositions->legalPositions[count].col = j;

        count++;
    }

    legalPositions->numberOfPositions = count;
}
