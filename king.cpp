#include "header.h"

King::King(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::King;

    isShortCastlingPossible = false;
    isLongCastlingPossible = false;
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
            pieceAtPosition = board->SelectSquare(newRow, newCol)->GetPiece();

            if (pieceAtPosition == nullptr || pieceAtPosition->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[count].row = newRow;
                legalPositionData->legalPositions[count].col = newCol;
                count++;
            }
        }
    }

    legalPositionData->numberOfPositions = count;

    if(isInCheck)
        return;

    if(moveCount > 0)
        return;

    // Castling
    // Check if the king and rook have not moved, and the squares between them are empty and protected

    Piece *rook;
    Position rookPosition;
    bool rookFound = false;
    bool pathProtected = false;
    int squaresTravelledByKing = 0;

    // Long castling - loop left until rook

    for(int i = col - 1; i >= 0; i--)
    {
        Piece *piece = board->SelectSquare(row, i)->GetPiece();

        if(piece != nullptr)
        {
            if(piece->GetPieceType() == PieceType::Rook && (piece->GetIsWhite() == isWhite) && !piece->GetMoveCount() > 0)
            {
                rookPosition.row = row;
                rookPosition.col = i;

                rookFound = true;
            }
            else
                break;
        }
    }

    if(rookFound)
    {
        rook = board->SelectSquare(rookPosition.row, rookPosition.col)->GetPiece();

        if(rook->GetMoveCount() == 0)
        {
            // Check if the two squares travelled by the king are protected
            squaresTravelledByKing = 0;
            for(int i = col - 1; i > rookPosition.col; i--)
            {
                if(squaresTravelledByKing == 2)
                    break;

                if(board->CheckIfPositionProtected(row, i, !isWhite))
                {
                    pathProtected = true;
                    break;                
                }

                squaresTravelledByKing++;
            }

            if(!pathProtected)
            {
                // add second square to legal positions
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = col - 2;
                count++;
            }
        }
    }

    rookFound = false;
    pathProtected = false;

    // Short castling - for white its loop right until rook, for black its loop left until rook

    for(int i = col + 1; i < BOARD_SIZE; i++)
    {
        Piece *piece = board->SelectSquare(row, i)->GetPiece();

        if(piece != nullptr)
        {
            if(piece->GetPieceType() == PieceType::Rook && !piece->GetMoveCount() > 0)
            {
                rookPosition.row = row;
                rookPosition.col = i;

                rookFound = true;
            }
            else
                break;
        }
    }

    if(rookFound)
    {
        rook = board->SelectSquare(rookPosition.row, rookPosition.col)->GetPiece();
    
        if(rook->GetMoveCount() == 0)
        {
            // Check if the two squares travelled by the king are protected
            squaresTravelledByKing = 0;
            for(int i = col + 1; i < rookPosition.col; i++)
            {
                if(squaresTravelledByKing == 2)
                    break;

                if(board->CheckIfPositionProtected(row, i, !isWhite))
                {
                    pathProtected = true;
                    break;                
                }

                squaresTravelledByKing++;
            }

            if(!pathProtected)
            {
                // add second square to legal positions
                legalPositionData->legalPositions[count].row = row;
                legalPositionData->legalPositions[count].col = col + 2;
                count++;
            }
        }
    }

    legalPositionData->numberOfPositions = count;
}
