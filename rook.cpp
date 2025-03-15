#include "header.h"

Rook::Rook(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Rook::~Rook()
{

}

void Rook::RefreshLegalPositions(Board* board)
{
    int count = 0;

    int row = position.row;
    int col = position.col;

    Piece *piece;

    // Up
    for(int i = row + 1; i < BOARD_SIZE; i++)
    {
        piece = board->board[i][col].piece;

        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = col;
            
                count++;
            }

            break;
        }
    
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = col;
        
        count++;
    }

    piece = NULL;

    // Down
    for(int i = row - 1; i >= 0; i --)
    {
        piece = board->board[i][col].piece;

        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = col;

                count++;
            }
            
            break;
        }
    
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = col;
        
        count++;
    }

    piece = NULL;

    // Right
    for(int j = col + 1; j < BOARD_SIZE; j++)
    {
        piece = board->board[row][j].piece;

        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }

        legalPositionData->legalPositions[count].row = row;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    piece = NULL;

    // Left
    for(int j = col - 1; j >= 0; j--)
    {
        piece = board->board[row][j].piece;

        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }

        legalPositionData->legalPositions[count].row = row;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    legalPositionData->numberOfPositions = count;
}
