#include "header.h"

bool AddPieceCommand::Execute()
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

bool AddPieceCommand::Undo()
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

    piece->SetPieceMoved();

    return true;
}

bool MoveCommand::Undo()
{
    destinationSquare->ClearPiece();

    sourceSquare->SetPiece(piece);

    piece->UndoPieceMoved();

    return true;
}

bool CaptureCommand::Execute()
{
    capturedPiece = sourceSquare->ClearPiece();

    sourceSquare->ClearPiece();
    
    destinationSquare->SetPiece(attackingPiece);

    attackingPiece->SetPieceMoved();

    return true;
}

bool CaptureCommand::Undo()
{
    destinationSquare->SetPiece(capturedPiece);

    sourceSquare->SetPiece(attackingPiece);

    attackingPiece->UndoPieceMoved();

    return true;
}

bool EnPassantCommand::Execute()
{
    Piece* opponentPiece = capturingSquare->GetPiece();

    if(opponentPiece != NULL && opponentPiece->GetIsWhite() != pawn->GetIsWhite() && opponentPiece->GetPieceType() == PieceType::Pawn)
    {
        capturedPawn = capturingSquare->ClearPiece();

        board->RemovePiece(capturedPawn);

        sourceSquare->ClearPiece();

        destinationSquare->SetPiece(pawn);

        pawn->SetPieceMoved();
    }

    return true;
}

bool EnPassantCommand::Undo()
{
    board->AddPiece(capturedPawn, capturingSquare->GetPosition().row, capturingSquare->GetPosition().col);

    destinationSquare->ClearPiece();

    sourceSquare->SetPiece(pawn);

    pawn->UndoPieceMoved();

    return true;
}

bool PromoteCommand::Execute()
{
    switch (pieceType)
    {
        case PieceType::Queen:
            promotedPiece = new Queen(pawnToPromote->GetIsWhite() ? 'Q' : 'q', pawnToPromote->GetIsWhite());
            break;
        case PieceType::Rook:
            promotedPiece = new Rook(pawnToPromote->GetIsWhite() ? 'R' : 'r', pawnToPromote->GetIsWhite());
            break;
        case PieceType::Bishop:
            promotedPiece = new Bishop(pawnToPromote->GetIsWhite() ? 'B' : 'b', pawnToPromote->GetIsWhite());
            break;
        case PieceType::Knight:
            promotedPiece = new Knight(pawnToPromote->GetIsWhite() ? 'N' : 'n', pawnToPromote->GetIsWhite());
            break;
        default:
            cout << "Invalid promotion piece type!" << endl;
            return false;
    }

    board->RemovePiece(pawnToPromote);

    board->AddPiece(promotedPiece, pawnToPromote->GetPosition().row, pawnToPromote->GetPosition().col);

    promotedPiece->SetPieceMoved();

    return true;
}

bool PromoteCommand::Undo()
{
    board->RemovePiece(promotedPiece);

    board->AddPiece(pawnToPromote, pawnToPromote->GetPosition().row, pawnToPromote->GetPosition().col);

    promotedPiece->UndoPieceMoved();

    return true;
}

bool CastleCommand::Execute()
{
    kingSource->ClearPiece();
    rookSource->ClearPiece();

    kingDestination->SetPiece(king);
    rookDestination->SetPiece(rook);

    king->SetPieceMoved();
    rook->SetPieceMoved();

    return true;
}

bool CastleCommand::Undo()
{
    kingDestination->ClearPiece();
    rookDestination->ClearPiece();

    kingSource->SetPiece(king);
    rookSource->SetPiece(rook);

    king->UndoPieceMoved();
    rook->UndoPieceMoved();

    return true;
}
