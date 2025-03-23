#include "header.h"

King::King(char piece, bool isWhite) : Piece(piece, isWhite)
{
    isKing = true;
}

King::~King()
{
}

void King::PreprocessAttackInfo(Board *board)
{
    return;
}

void King::SetLegalPositions(Board *board)
{
    int count = 0;
    int row = position.row;
    int col = position.col;

    Piece *pieceAtPosition = nullptr;

    int directions[8][2] = {
        {1, 0},   // Up
        {-1, 0},  // Down
        {0, -1},  // Left
        {0, 1},   // Right
        {1, -1},  // UpLeft
        {1, 1},   // UpRight
        {-1, -1}, // DownLeft
        {-1, 1}   // DownRight
    };

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        if (board->CheckIfPositionProtected(newRow, newCol, !isWhite) || CheckIfAttackPathContainsPosition(newRow, newCol))
            continue;

        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
        {
            pieceAtPosition = board->SelectSquare(newRow, newCol)->piece;

            if (pieceAtPosition == nullptr || pieceAtPosition->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = newRow;
                legalPositionData->legalPositions[count].col = newCol;
                count++;
            }
        }
    }

    legalPositionData->numberOfPositions = count;
}
