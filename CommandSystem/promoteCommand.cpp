#include "promoteCommand.h"
#include "../Board/square.h"
#include "../Board/board.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Rook.h"

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
