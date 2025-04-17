#include <iostream>
#include <tuple>
#include <ctype.h>
#include <string>
#include <sstream>

#include "utilities.h"
#include "../Board/square.h"
#include "../Board/board.h"
#include "../Pieces/king.h"
#include "../Pieces/pawn.h"

using namespace std;

Utilities::Utilities()
{
	
}

void Utilities::InitializePieceImages()
{
	cout << "Initialize Piece Images called" << endl;
	
	if(!whiteKingImage.CreateFromPng("res/Game/king.png"))
		std::cout << "Error creating image for piece! W King" << std::endl;
	
	if(!blackKingImage.CreateFromPng("res/Game/king1.png"))
		std::cout << "Error creating image for piece! B King" << std::endl;
	
	if(!whiteQueenImage.CreateFromPng("res/Game/queen.png"))
		std::cout << "Error creating image for piece! W Queen" << std::endl;
	
	if(!blackQueenImage.CreateFromPng("res/Game/queen1.png"))
		std::cout << "Error creating image for piece! B Queen" << std::endl;
			
	if(!whiteBishopImage.CreateFromPng("res/Game/bishop.png"))
		std::cout << "Error creating image for piece! W Bishop" << std::endl;
		
	if(!blackBishopImage.CreateFromPng("res/Game/bishop1.png"))
		std::cout << "Error creating image for piece! B Bishop" << std::endl;
		
	if(!whiteKnightImage.CreateFromPng("res/Game/knight.png"))
		std::cout << "Error creating image for piece! W Knight" << std::endl;
	
	if(!blackKnightImage.CreateFromPng("res/Game/knight1.png"))
		std::cout << "Error creating image for piece! B Knight" << std::endl;
		
	if(!whiteRookImage.CreateFromPng("res/Game/rook.png"))
		std::cout << "Error creating image for piece! W Rook" << std::endl;
	
	if(!blackRookImage.CreateFromPng("res/Game/rook1.png"))
		std::cout << "Error creating image for piece! B Rook" << std::endl;
		
	if(!whitePawnImage.CreateFromPng("res/Game/pawn.png"))
		std::cout << "Error creating image for piece! W Pawn" << std::endl;
	
	if(!blackPawnImage.CreateFromPng("res/Game/pawn1.png"))
		std::cout << "Error creating image for piece! B Pawn" << std::endl;
}

spn::Image* Utilities::GetImageForPiece(PieceType pieceType, bool isWhite)
{
	switch(pieceType)
	{
		case PieceType::King :
			return (isWhite ? &whiteKingImage : &blackKingImage);
		case PieceType::Queen :
			return (isWhite ? &whiteQueenImage : &blackQueenImage);
		case PieceType::Bishop :
			return (isWhite ? &whiteBishopImage : &blackBishopImage);
		case PieceType::Knight :
			return (isWhite ? &whiteKnightImage : &blackKnightImage);
		case PieceType::Rook :
			return (isWhite ? &whiteRookImage : &blackRookImage);
		case PieceType::Pawn :
			return (isWhite ? &whitePawnImage : &blackPawnImage);
	}
	
	return nullptr;
}

PieceType GetPieceTypeForChar(char pieceChar)
{
	PieceType pieceType;
	
	switch (tolower(pieceChar))
    {
    case 'k':
    case 'K': return PieceType::King;
    case 'q':
	case 'Q': return PieceType::Queen;
    case 'b':
    case 'B': return PieceType::Bishop;
    case 'n':
	case 'N': return PieceType::Knight;
    case 'r':
    case 'R': return PieceType::Rook;
    case 'p':
    case 'P': return PieceType::Pawn;
    default:
        return PieceType::None;
    }
}

bool GetIsWhiteForChar(char pieceChar)
{
	return (pieceChar >= 'A' && pieceChar <= 'Z');
}

char GetCharForPiece(Piece *piece)
{
    bool isWhite = piece->GetIsWhite();
    switch (piece->GetPieceType())
    {
    case PieceType::King:
        return isWhite ? 'K' : 'k';
    case PieceType::Queen:
        return isWhite ? 'Q' : 'q';
    case PieceType::Bishop:
        return isWhite ? 'B' : 'b';
    case PieceType::Knight:
        return isWhite ? 'N' : 'n';
    case PieceType::Rook:
        return isWhite ? 'R' : 'r';
    case PieceType::Pawn:
        return isWhite ? 'P' : 'p';
    case PieceType::None:
        break;
    }

    return '-';
}

string GetCodeForSquare(int row, int col)
{
    char xPos = (char)col + 'A';
    char yPos = (char)(row + '1');

    std::ostringstream oss;
    oss << xPos << yPos;
    return oss.str();
}

string GetCodeForPiece(Piece* piece)
{
    // std::cout << typeid(piece).name() << std::endl;

    std::ostringstream oss;

    char pieceChar = GetCharForPiece(piece);

    string piecePos = GetCodeForSquare(piece->GetPosition().row, piece->GetPosition().col);

    oss << pieceChar << piecePos;

    if(piece->GetIsKing())
    {
        King* king = (King*)piece;
        if(king->GetIsShortCastlingPossible())
            oss << "/" << "o-o";
        if(king->GetIsLongCastlingPossible())
            oss << "/" << "o-o-o";
    }

    if(piece->GetPieceType() == PieceType::Pawn)
    {
        Pawn* pawn = (Pawn*)piece;

        if(pawn->GetCanMoveTwoSteps())
            oss << "/" << "T";
        if(pawn->GetCanEnPassantLeft())
            oss << "/" << "L";
        if(pawn->GetCanEnPassantRight())
            oss << "/" << "R"; 
    }

    return oss.str();
}

void GetCastlingPositions(int &rookRow, int &rookCol, int &kingRow, int &kingCol, bool isWhite, bool isLongCastling)
{
    // if king is white and short castle, then king moves to G1 and rook moves to F1
    // if king is white and long castle, then king moves to C1 and rook moves to D1
    // if king is black and short castle, then king moves to G8 and rook moves to F8
    // if king is black and long castle, then king moves to C8 and rook moves to D8

    if (isWhite)
    {
        kingRow = 0;
        kingCol = isLongCastling ? 2 : 6;
        rookRow = 0;
        rookCol = isLongCastling ? 3 : 5;
    }
    else
    {
        kingRow = 7;
        kingCol = isLongCastling ? 2 : 6;
        rookRow = 7;
        rookCol = isLongCastling ? 3 : 5;
    }
}

PieceType GetPromotionPieceType()
{
    char pieceChar;
    
    do
    {
        cout << "Enter the piece type to promote to (Q/R/B/N): ";
        cin >> pieceChar;

        switch (pieceChar)
        {
            case 'Q':
                return PieceType::Queen;
            case 'R':
                return PieceType::Rook;
            case 'B':
                return PieceType::Bishop;
            case 'N':
                return PieceType::Knight;
            default:
                cout << "Invalid piece type! Please enter a valid piece type (Q/R/B/N): ";
                break;
        }
    } while (pieceChar != 'Q' && pieceChar != 'R' && pieceChar != 'B' && pieceChar != 'N');

    return PieceType::None;
}

bool ProcessAttackInDirection(Board* board, Piece* piece, int rowDir, int colDir)
{
    Piece *firstPiece = nullptr;
    Piece *secondPiece = nullptr;

    Square **attackPath = new Square *[100];
    int attackPathIndex = 0;

    int row = piece->GetPosition().row;
    int col = piece->GetPosition().col;

    Piece *tempPiece;
    Square *currentSquare;

    int limit = BOARD_SIZE;

    // add piece's square to attack path
    attackPath[attackPathIndex++] = board->GetSquare(row, col);

    // cout << "Piece square " << row << " " << col << " Limit : " << limit << endl;

    for (int i = 1; i < limit; i++)
    {
        int newRow = row + (i * rowDir);
        int newCol = col + (i * colDir);

        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE)
            break; // Out of bounds, stop checking

        // cout << "Checking square at " << newRow << " " << newCol << endl;

        currentSquare = board->GetSquare(newRow,newCol);
        tempPiece = currentSquare->GetPiece();

        if (tempPiece != nullptr)
        {
            if (tempPiece->GetIsWhite() == piece->GetIsWhite())
            {
                // cout << "Piece encountered - Same color - Ending traversal!" << endl;
                // piece of same color -> end traversal
                break;
            }

            if (firstPiece == nullptr)
            {
                // cout << "First Piece encountered : " << endl;
                firstPiece = tempPiece;
                // firstPiece->PrintPiece();
                // cout << endl;
                if (firstPiece->GetIsKing())
                {
                    // cout << "First piece is king - setting in check - adding attack path" << endl;
                    firstPiece->SetKingIsInCheck();
                    for (int i = 0; i < attackPathIndex; i++)
                    {
                        firstPiece->AddSquareToAttackPath(attackPath[i]);
                    }
                    return false;
                }
            }
            else if (secondPiece == nullptr)
            {
                // cout << "Second Piece encountered" << endl;
                secondPiece = tempPiece;
                // secondPiece->PrintPiece();
                // cout << endl;
                if (secondPiece->GetIsKing())
                {
                    // cout << "Second piece is king - setting first piece is pinned - adding pin path" << endl;
                    firstPiece->SetPieceIsPinned();
                    for (int i = 0; i < attackPathIndex; i++)
                    {
                        // cout << "Adding square " << attackPath[i]->GetPosition().row << " " << attackPath[i]->GetPosition().col << endl;
                        firstPiece->AddSquareToAttackPath(attackPath[i]);
                    }
                    // Add attacking piece to attack path
                    // cout << "Adding current square " << row << " " << col << endl;
                    firstPiece->AddSquareToAttackPath(board->GetSquare(row, col));
                    break;
                }
            }
        }

        attackPath[attackPathIndex++] = currentSquare;
    }

    // cout << "Direction complete!" << endl;

    return true;
}

bool SetLegalMovesInDirection(Board* board, Piece* piece, int rowDir, int colDir)
{
    int row = piece->GetPosition().row;
    int col = piece->GetPosition().col;

    // cout << "Piece " << piece->GetPieceChar() << " square " << GetCodeForSquare(row, col) << endl;

    Piece *king = board->GetKing(piece->GetIsWhite());

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    LegalPositionData *legalPositionData = piece->GetLegalPositionData();

    Piece *tempPiece;

    int limit = BOARD_SIZE;

    // cout << "Limit : " << limit << endl;

    for (int i = 1; i < limit; i++)
    {
        int newRow = row + (i * rowDir);
        int newCol = col + (i * colDir);

        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE)
            break; // Out of bounds, stop checking

        // cout << "Checking square at " << GetCodeForSquare(newRow, newCol) << endl;

        if (piece->GetIsPinned() && !piece->CheckIfAttackPathContainsPosition(newRow, newCol))
        {
            // cout << "Pinned piece and Square " << GetCodeForSquare(newRow, newCol) << " not in attack path" << endl;
            continue;
        }

        // cout << "Adding square " << GetCodeForSquare(newRow, newCol) << " to Legal Positions without King " << endl;

        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].row = newRow;
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].col = newCol;

        legalPositionData->numberOfPositionsWithoutKing++;

        tempPiece = board->GetSquare(newRow,newCol)->GetPiece();

        if (tempPiece != NULL)
        {
            // cout << "Piece in path : " << endl;
            // tempPiece->PrintPiece();
            // cout << endl;

            if (tempPiece->GetIsWhite() == piece->GetIsWhite())
            {
                // cout << "Piece is of same color! Stop iteration! " << piece->GetIsWhite() << " " << tempPiece->GetIsWhite() << endl;
                break;
            }
            else
            {
                if (kingInCheck && !king->CheckIfAttackPathContainsPosition(newRow, newCol))
                {
                    // cout << "King in check and Square " << GetCodeForSquare(newRow, newCol) << " not in King's attack path" << endl;
                    continue;
                }

                // cout << "Adding square " << GetCodeForSquare(newRow, newCol) << " to Legal Positions " << endl;

                legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;

                legalPositionData->numberOfPositions++;

                if (!tempPiece->GetIsKing())
                {
                    // cout << "Piece found is not king and an opp! End traversal!" << endl;

                    break;
                }
            }
        }
        else
        {
            if (kingInCheck && !king->CheckIfAttackPathContainsPosition(newRow, newCol))
            {
                // cout << "King in check and Square " << GetCodeForSquare(newRow, newCol) << " not in King's attack path" << endl;
                continue;
            }

            // cout << "Adding square " << GetCodeForSquare(newRow, newCol) << " to Legal Positions " << endl;

            legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
            legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;

            legalPositionData->numberOfPositions++;
        }
    }

    // cout << "Direction complete!" << endl
    //  << endl;

    return true;
}
