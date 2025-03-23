#include "header.h"

Pawn::Pawn(char piece, bool isWhite) : Piece(piece, isWhite)
{
}

Pawn::~Pawn()
{
}

void Pawn::PreprocessAttackInfo(Board *board)
{
    board->ProcessAttackInDirection(this, 1, 0, false);
    board->ProcessAttackInDirection(this, -1, 0, false);
}

void Pawn::SetLegalPositions(Board *board)
{
    int count = 0;

    int row = position.row;
    int col = position.col;

    int i, j;

    Piece *piece = NULL;

    // up
    if (isWhite)
    {
        // norm
        i = row + 1;
        j = col;

        if (i < BOARD_SIZE)
        {
            piece = board->board[i][j].piece;

            if (piece == NULL)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;

        // double
        if (row == 1)
        {
            i = row + 2;
            j = col;

            if (i < BOARD_SIZE)
            {
                piece = board->board[i][j].piece;

                if (piece == NULL)
                {
                    legalPositionData->legalPositions[count].row = i;
                    legalPositionData->legalPositions[count].col = j;

                    count++;
                }
            }
        }

        piece = NULL;

        // cross-left
        i = row + 1;
        j = col - 1;

        if (i < BOARD_SIZE && j >= 0)
        {
            piece = board->board[i][j].piece;

            if (piece != NULL && piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;

        // cross-right
        i = row + 1;
        j = col + 1;

        if (i < BOARD_SIZE && j < BOARD_SIZE)
        {
            piece = board->board[i][j].piece;

            if (piece != NULL && piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;
    }
    else
    {
        i = row - 1;
        j = col;

        if (i >= 0)
        {
            piece = board->board[i][j].piece;

            if (piece == NULL)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;

        if (row == 6)
        {
            i = row - 2;
            j = col;

            if (i < BOARD_SIZE)
            {
                piece = board->board[i][j].piece;

                if (piece == NULL)
                {
                    legalPositionData->legalPositions[count].row = row + 1;
                    legalPositionData->legalPositions[count].col = col;

                    count++;
                }
            }
        }

        piece = NULL;

        // cross-left
        i = row - 1;
        j = col - 1;

        if (i >= 0 && j >= 0)
        {
            piece = board->board[i][j].piece;

            if (piece != NULL && piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;

        // cross-right
        i = row - 1;
        j = col + 1;

        if (i >= 0 && j < BOARD_SIZE)
        {
            piece = board->board[i][j].piece;

            if (piece != NULL && piece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = i;
                legalPositionData->legalPositions[count].col = j;

                count++;
            }
        }

        piece = NULL;
    }

    legalPositionData->numberOfPositions = count;
}