#include "header.h"

bool AddPieceCommand::Execute(Board* board)
{
    Position position = squareToAddAt->GetPosition();

    switch (pieceType)
    {
    case PieceType::King:
        board->AddPiece(new King(isWhite? 'K' : 'k', isWhite), position.row, position.col);
        break;
    case PieceType::Queen:
        board->AddPiece(new Queen(isWhite? 'Q' : 'q', isWhite), position.row, position.col);
        break;
    case PieceType::Bishop:
        board->AddPiece(new Bishop(isWhite? 'B' : 'b', isWhite), position.row, position.col);
        break;
    case PieceType::Knight:
        board->AddPiece(new Knight(isWhite? 'N' : 'n', isWhite), position.row, position.col);
        break;
    case PieceType::Rook:
        board->AddPiece(new Rook(isWhite? 'R' : 'r', isWhite), position.row, position.col);
        break;
    case PieceType::Pawn:
        board->AddPiece(new Pawn(isWhite? 'P' : 'p', isWhite), position.row, position.col);
        break;
    default:
        return false;
        break;
    }

    return true;
}

bool AddPieceCommand::Undo(Board* board)
{
    squareToAddAt->ClearPiece();
    return true;
}

bool RemovePieceCommand::Execute()
{
    pieceToRemove = squareToRemoveFrom->ClearPiece();
    return true;
}

bool RemovePieceCommand::Undo()
{
    squareToRemoveFrom->SetPiece(pieceToRemove);
    return true;
}

bool MoveCommand::Execute()
{
    sourceSquare->ClearPiece();

    destinationSquare->SetPiece(piece);

    return true;
}

bool MoveCommand::Undo()
{
    destinationSquare->ClearPiece();

    sourceSquare->SetPiece(piece);

    return true;
}
