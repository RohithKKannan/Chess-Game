#include <iostream>

#include "pawn.h"
#include "../Board/square.h"
#include "../Board/board.h"

Pawn::Pawn(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Pawn;

    canMoveTwoSteps = false;
    hasMovedTwoSteps = false;
    canEnPassantLeft = false;
    canEnPassantRight = false;
}

Pawn::~Pawn()
{
}

void Pawn::PreprocessAttackInfo(Board *board)
{
    // Pawn can attack diagonally one square forward
    int row = position.row;
    int col = position.col;

    int direction = isWhite ? -1 : 1; // White moves up, Black moves down

    // Check for diagonal attacks
    // Left diagonal attack

    int newRow = row + direction;
    int newCol = col - 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        Piece *tempPiece = board->GetSquare(newRow, newCol)->GetPiece();
        if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite)
        {
            if(tempPiece->GetIsKing())
            {
                // Pawn attacks opponent's king
                tempPiece->SetKingIsInCheck();
                tempPiece->AddSquareToAttackPath(board->GetSquare(newRow, newCol));
                tempPiece->AddSquareToAttackPath(board->GetSquare(row, col));
                return;
            }
        }
    }

    // Right diagonal attack
    newCol = col + 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        Piece *tempPiece = board->GetSquare(newRow, newCol)->GetPiece();
        if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite)
        {
            if(tempPiece->GetIsKing())
            {
                // Pawn attacks opponent's king
                tempPiece->SetKingIsInCheck();
                tempPiece->AddSquareToAttackPath(board->GetSquare(newRow, newCol));
                tempPiece->AddSquareToAttackPath(board->GetSquare(row, col));
                return;
            }
        }
    }
}

void Pawn::SetLegalPositions(Board *board)
{
    int row = position.row;
    int col = position.col;

    Piece *king = board->GetKing(isWhite);

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return;
    }

    int direction = isWhite ? 1 : -1;

    // Pawn can move 
    // 1. forward one square 
    //          a. if first square empty -> forward two squares if it hasn't moved yet
    // 3. diagonally one square forward to capture opponent's pieces
    // 4. En passant

    // Forward move one square
    int newRow = row + direction;
    int newCol = col;

    canMoveTwoSteps = false;

    Piece *tempPiece;
    
    if (GetIsPinned() && !CheckIfAttackPathContainsPosition(newRow, newCol))
    {
//    	cout << "Pinned piece and Square " << GetCodeForSquare(newRow, newCol) << " not in attack path" << endl;
        return;
    }

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        bool positionInAttackPath = king->CheckIfAttackPathContainsPosition(newRow, newCol);
        if ((kingInCheck && positionInAttackPath) || !kingInCheck)
        {
            tempPiece = board->GetSquare(newRow, newCol)->GetPiece();

            if (tempPiece == nullptr)
            {
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                legalPositionData->numberOfPositions++;

                if(moveCount == 0)
                {
                    // Pawn can move two squares forward if it hasn't moved yet
                    newRow += direction;

                    if(newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
                    {
                        tempPiece = board->GetSquare(newRow, newCol)->GetPiece();

                        if (tempPiece == nullptr)
                        {
                            legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                            legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                            legalPositionData->numberOfPositions++;

                            canMoveTwoSteps = true;
                        }
                    }
                }
            }
        }
    }

    // Diagonal attack left
    newRow = row + direction;
    newCol = col - 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        bool positionInAttackPath = king->CheckIfAttackPathContainsPosition(newRow, newCol);
        if ((kingInCheck && positionInAttackPath) || !kingInCheck)
        {
            tempPiece = board->GetSquare(newRow, newCol)->GetPiece();
            
            if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                legalPositionData->numberOfPositions++;
            }
        }
    }

    // Diagonal attack right
    newCol = col + 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        bool positionInAttackPath = king->CheckIfAttackPathContainsPosition(newRow, newCol);
        if ((kingInCheck && positionInAttackPath) || !kingInCheck)
        {
            tempPiece = board->GetSquare(newRow, newCol)->GetPiece();
            
            if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite)
            {
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                legalPositionData->numberOfPositions++;
            }
        }
    }

    // En passant - check piece next to pawn - if it is an opponent's pawn, and it has moved two squares, add it to legal positions
    // Check left en passant

    canEnPassantLeft = false;

    newRow = row;
    newCol = col - 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        bool positionInAttackPath = king->CheckIfAttackPathContainsPosition(newRow, newCol);
        if ((kingInCheck && positionInAttackPath) || !kingInCheck)
        {
            tempPiece = board->GetSquare(newRow, newCol)->GetPiece();

            if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite && tempPiece->GetPieceType() == PieceType::Pawn)
            {
                Pawn *opponentPawn = (Pawn *)tempPiece;
                if(opponentPawn->GetHasMovedTwoSteps())
                {
                    legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow + direction;
                    legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                    legalPositionData->numberOfPositions++;

                    canEnPassantLeft = true;
                }
            }
        }
    }

    // Check right en passant

    canEnPassantRight = false;

    newCol = col + 1;

    if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
    {
        bool positionInAttackPath = king->CheckIfAttackPathContainsPosition(newRow, newCol);
        if ((kingInCheck && positionInAttackPath) || !kingInCheck)
        {
            tempPiece = board->GetSquare(newRow, newCol)->GetPiece();

            if (tempPiece != nullptr && tempPiece->GetIsWhite() != isWhite && tempPiece->GetPieceType() == PieceType::Pawn)
            {
                Pawn *opponentPawn = (Pawn *)tempPiece;
                if(opponentPawn->GetHasMovedTwoSteps())
                {
                    legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow + direction;
                    legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;
                    legalPositionData->numberOfPositions++;

                    canEnPassantRight = true;
                }
            }
        }
    }
}
