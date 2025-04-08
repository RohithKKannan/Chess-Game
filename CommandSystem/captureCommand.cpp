#include "captureCommand.h"
#include "../Board/board.h"
#include "../Board/square.h"
#include "../Pieces/piece.h"

bool CaptureCommand::Execute()
{
    capturedPiece = destinationSquare->ClearPiece();

    board->RemovePiece(capturedPiece);

    sourceSquare->ClearPiece();
    
    destinationSquare->SetPiece(attackingPiece);

    attackingPiece->SetPieceMoved();

    return true;
}

bool CaptureCommand::Undo()
{
    destinationSquare->SetPiece(capturedPiece);

    board->AddPiece(capturedPiece, capturedPiece->GetPosition().row, capturedPiece->GetPosition().col);

    sourceSquare->SetPiece(attackingPiece);

    attackingPiece->UndoPieceMoved();

    return true;
}
