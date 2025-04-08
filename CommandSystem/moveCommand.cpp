#include "moveCommand.h"
#include "../Board/square.h"
#include "../Pieces/piece.h"

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
