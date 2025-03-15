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

    // Up
    for(int i = row + 1; i < BOARD_SIZE; i++)
    {
        if(board->board[i][col].piece != NULL)
        {
            cout << "Piece found in the way! " << i << " " << col << endl;

            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = col;
        
        count++;
    }

    // Down
    for(int i = row - 1; i >= 0; i --)
    {
        if(board->board[i][col].piece != NULL)
        {
            cout << "Piece found in the way! " << i << " " << col << endl;

            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = col;
            
            count++;

            break;
        }
    
        legalPositionData->legalPositions[count].row = i;
        legalPositionData->legalPositions[count].col = col;
        
        count++;
    }

    // Right
    for(int j = col + 1; j < BOARD_SIZE; j++)
    {
        if(board->board[row][j].piece != NULL)
        {
            cout << "Piece found in the way! " << row << " " << j << endl;

            legalPositionData->legalPositions[count].row = row;
            legalPositionData->legalPositions[count].col = j;

            count++;

            break;
        }

        legalPositionData->legalPositions[count].row = row;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    // Left
    for(int j = col - 1; j >= 0; j--)
    {
        if(board->board[row][j].piece != NULL)
        {
            cout << "Piece found in the way! " << row << " " << j << endl;

            legalPositionData->legalPositions[count].row = row;
            legalPositionData->legalPositions[count].col = j;

            count++;

            break;
        }

        legalPositionData->legalPositions[count].row = row;
        legalPositionData->legalPositions[count].col = j;

        count++;
    }

    legalPositionData->numberOfPositions = count;
}
