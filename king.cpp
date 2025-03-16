#include "header.h"

King::King(char piece, bool isWhite) : Piece(piece, isWhite)
{
}

King::~King()
{
}

void King::RefreshLegalPositions(Board *board)
{
    int count = 0;

    int row = position.row;
    int col = position.col;

    Piece *pieceAtPosition = nullptr;

    // up
    if (row + 1 < BOARD_SIZE && !board->CheckIfPositionProtected(row + 1, col, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row + 1, col)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row + 1;
            legalPositionData->legalPositions[count].col = col;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row + 1;
                legalPositionData->legalPositions[count].col = col;

                count++;
            }
        }
    }

    // down
    if (row - 1 >= 0 && !board->CheckIfPositionProtected(row - 1, col, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row - 1, col)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row - 1;
            legalPositionData->legalPositions[count].col = col;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row - 1;
                legalPositionData->legalPositions[count].col = col;

                count++;
            }
        }
    }

    // left
    if (col - 1 >= 0 && !board->CheckIfPositionProtected(row, col - 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row, col - 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row;
            legalPositionData->legalPositions[count].col = col - 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = col - 1;

                count++;
            }
        }
    }

    // right
    if (col + 1 < BOARD_SIZE && !board->CheckIfPositionProtected(row, col + 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row, col + 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row;
            legalPositionData->legalPositions[count].col = col + 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = col + 1;

                count++;
            }
        }
    }

    // upLeft
    if (row + 1 < BOARD_SIZE && col - 1 >= 0 && !board->CheckIfPositionProtected(row + 1, col - 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row + 1, col + 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row + 1;
            legalPositionData->legalPositions[count].col = col + 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row + 1;
                legalPositionData->legalPositions[count].col = col + 1;

                count++;
            }
        }
    }

    // upRight
    if (row + 1 < BOARD_SIZE && col + 1 < BOARD_SIZE && !board->CheckIfPositionProtected(row + 1, col + 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row + 1, col + 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row + 1;
            legalPositionData->legalPositions[count].col = col + 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row + 1;
                legalPositionData->legalPositions[count].col = col + 1;

                count++;
            }
        }
    }

    // downLeft
    if (row - 1 >= 0 && col - 1 >= 0 && !board->CheckIfPositionProtected(row - 1, col - 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row - 1, col - 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row - 1;
            legalPositionData->legalPositions[count].col = col - 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row - 1;
                legalPositionData->legalPositions[count].col = col - 1;

                count++;
            }
        }
    }

    // downRight
    if (row - 1 >= 0 && col + 1 < BOARD_SIZE && !board->CheckIfPositionProtected(row - 1, col + 1, !isWhite))
    {
        pieceAtPosition = board->SelectSquare(row - 1, col + 1)->piece;

        if (pieceAtPosition == nullptr)
        {
            legalPositionData->legalPositions[count].row = row - 1;
            legalPositionData->legalPositions[count].col = col + 1;

            count++;
        }
        else
        {
            if (pieceAtPosition->GetIsWhite() == !isWhite)
            {
                legalPositionData->legalPositions[count].row = row - 1;
                legalPositionData->legalPositions[count].col = col + 1;

                count++;
            }
        }
    }

    legalPositionData->numberOfPositions = count;
}