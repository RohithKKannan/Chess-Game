#include "header.h"

Knight::Knight(char piece, bool isWhite) : Piece(piece, isWhite)
{
    pieceType = PieceType::Knight;
}

Knight::~Knight()
{

}

void Knight::PreprocessAttackInfo(Board *board)
{
    if (!ProcessKnightAttack(board, 1, 2))
        return;

    if (!ProcessKnightAttack(board, 1, -2))
        return;

    if (!ProcessKnightAttack(board, -1, 2))
        return;

    if (!ProcessKnightAttack(board, -1, -2))
        return;

    if (!ProcessKnightAttack(board, 2, 1))
        return;

    if (!ProcessKnightAttack(board, 2, -1))
        return;

    if (!ProcessKnightAttack(board, -2, 1))
        return;

    if (!ProcessKnightAttack(board, -2, -1))
        return;
}

void Knight::SetLegalPositions(Board *board)
{
    if (!SetLegalMoveForKnight(board, 1, 2))
        return;

    if (!SetLegalMoveForKnight(board, 1, -2))
        return;

    if (!SetLegalMoveForKnight(board, -1, 2))
        return;

    if (!SetLegalMoveForKnight(board, -1, -2))
        return;

    if (!SetLegalMoveForKnight(board, 2, 1))
        return;

    if (!SetLegalMoveForKnight(board, 2, -1))
        return;

    if (!SetLegalMoveForKnight(board, -2, 1))
        return;

    if (!SetLegalMoveForKnight(board, -2, -1))
        return;
}

bool Knight::ProcessKnightAttack(Board* board, int rowDir, int colDir)
{
    int row = position.row + rowDir;
    int col = position.col + colDir;

    Piece *tempPiece;
    Square *attackingSquare;

    Piece *king = board->GetKing(isWhite);

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    // cout << "Preprocessing Knight at " << row << " " << col << endl;

    attackingSquare = board->GetSquare(position.row,position.col);

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        tempPiece = board->GetSquare(row,col)->GetPiece();
        if (tempPiece != nullptr && (tempPiece->GetIsWhite() != isWhite) && tempPiece->GetIsKing())
        {
            // knight attacks opp king
            tempPiece->SetKingIsInCheck();
            tempPiece->AddSquareToAttackPath(attackingSquare);
            return false;
        }
    }

    return true;
}

bool Knight::SetLegalMoveForKnight(Board *board, int rowDir, int colDir)
{
    int row = position.row + rowDir;
    int col = position.col + colDir;

    Piece *tempPiece = nullptr;

    Piece *king = board->GetKing(isWhite);
    bool kingInCheck = king->GetIsInCheck();
    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].row = row;
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].col = col;

        legalPositionData->numberOfPositionsWithoutKing++;

        tempPiece = board->GetSquare(row, col)->GetPiece();

        if (isPinned && !CheckIfAttackPathContainsPosition(row, col))
        {
            return false;
        }

        if (tempPiece != nullptr)
        {
            if (tempPiece->GetIsWhite() == isWhite)
                return true;
        }

        if (kingInCheck && !king->CheckIfAttackPathContainsPosition(row, col))
        {
            return true;
        }

        legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = row;
        legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = col;

        legalPositionData->numberOfPositions++;
    }

    return true;
}
