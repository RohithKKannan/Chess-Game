#include "header.h"

Bishop::Bishop(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Bishop::~Bishop()
{

}

void Bishop::RefreshLegalPositions(Board* board)
{
    int count = 0;

    int row = position.row;
    int col = position.col;

    Piece* piece = NULL;
    
    // Up Left
    for(int i = row + 1, j = col - 1; i < BOARD_SIZE && j >= 0; i++, j--)
    {
        piece = board->board[i][j].piece;
        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }

        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    piece = NULL;

    // Up Right
    for(int i = row + 1, j = col + 1; i < BOARD_SIZE && j < BOARD_SIZE; i++, j++)
    {
        piece = board->board[i][j].piece;
        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }
            
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    piece = NULL;

    // Down Left
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        piece = board->board[i][j].piece;
        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }
            
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    piece = NULL;

    // Down Right
    for(int i = row - 1, j = col + 1; i >= 0 && j < BOARD_SIZE; i--, j++)
    {
        piece = board->board[i][j].piece;

        if(piece != NULL)
        {
            if(piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }

            break;
        }

        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    legalPositionData->numberOfPositions = count;
}