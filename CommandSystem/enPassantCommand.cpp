#include "enPassantCommand.h"
#include "../Board/board.h"
#include "../Board/square.h"
#include "../Pieces/pawn.h"

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
        
		return true;
	}
	else
		return false;
}

bool EnPassantCommand::Undo()
{
    board->AddPiece(capturedPawn, capturingSquare->GetPosition()->row, capturingSquare->GetPosition()->col);

    destinationSquare->ClearPiece();

    sourceSquare->SetPiece(pawn);

    pawn->UndoPieceMoved();

    return true;
}
