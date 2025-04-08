#include "castleCommand.h"
#include "../Board/square.h"
#include "../Pieces/king.h"
#include "../Pieces/rook.h"

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
