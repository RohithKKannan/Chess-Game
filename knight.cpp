#include "header.h"

Knight::Knight(char piece, bool isWhite) : Piece(piece, isWhite)
{

}

Knight::~Knight()
{

}

void Knight::RefreshLegalPositions(Board* board)
{
    int count = 0;

    int row = position.row;
    int col = position.col;

    int i, j;

    Piece* piece = NULL;
    
    // row + 1, col + 2
    i = row + 1;
    j = col + 2;

    if(i < BOARD_SIZE && j < BOARD_SIZE)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row + 1, col - 2
    i = row + 1;
    j = col - 2;
    
    if(i < BOARD_SIZE && j >= 0)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row - 1, col + 2
    i = row - 1;
    j = col + 2;

    if(i >= 0 && j < BOARD_SIZE)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row - 1, col - 2
    i = row - 1;
    j = col - 2;
    
    if(i >= 0 && j >= 0)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row + 2, col + 1
    i = row + 2;
    j = col + 1;

    if(i < BOARD_SIZE && j < BOARD_SIZE)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row + 2, col - 1
    i = row + 2;
    j = col - 1;

    if(i < BOARD_SIZE && j >= 0)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row - 2, col + 1
    i = row - 2;
    j = col + 1;

    if(i >= 0 && j < BOARD_SIZE)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    piece = NULL;

    // row - 2, col - 1
    i = row - 2;
    j = col - 1;

    if(i >= 0 && j >= 0)
    {
        piece = board->board[i][j].piece;
        if(piece == NULL || (piece != NULL && piece->GetIsWhite() != isWhite))
        {
            legalPositionData->legalPositions[count].row = i;
            legalPositionData->legalPositions[count].col = j;

            count++;
        }
    }

    legalPositionData->numberOfPositions = count;
}