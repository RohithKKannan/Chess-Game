#include <string>
#include <sstream>
#include <iostream>

#include "board.h"
#include "square.h"
#include "../Core/core.h"
#include "../Utils/utilities.h"
#include "../Pieces/piece.h"
#include "../Pieces/king.h"
#include "../Pieces/queen.h"
#include "../Pieces/bishop.h"
#include "../Pieces/knight.h"
#include "../Pieces/rook.h"
#include "../Pieces/pawn.h"
#include "../CommandSystem/command.h"
#include "../CommandSystem/captureCommand.h"
#include "../CommandSystem/castleCommand.h"
#include "../CommandSystem/enPassantCommand.h"
#include "../CommandSystem/moveCommand.h"
#include "../CommandSystem/promoteCommand.h"

using namespace std;

Board::Board()
{
	boardImage.CreateCheckerImage(480,480, 60, 118, 150, 86, 238, 238, 210);
		
    pieces = new Piece*[32];
    whitePieces = new Piece*[16];
    blackPieces = new Piece*[16];
    whitePawns = new Pawn*[8];
    blackPawns = new Pawn*[8];

    for (int i = 0; i < 32; i++)
        pieces[i] = nullptr;

    for (int i = 0; i < 16; i++)
    {
        whitePieces[i] = nullptr;
        blackPieces[i] = nullptr;
    }

    board = new Square*[BOARD_SIZE];

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        board[i] = new Square[BOARD_SIZE];

        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].SetPosition(i, j);
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < pieceCount; i++)
    {
        if (pieces[i] != nullptr)
        {
            delete pieces[i];
        }
    }

    delete[] pieces;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i] != nullptr)
        {
            delete[] board[i];
        }
    }

    delete[] board;

    delete[] whitePieces;
    delete[] blackPieces;
}

void Board::SetupBoard()
{
    std::string initialBoardState = "RA1 RH1 rA8 rH8 KE1 kE8 QD1 qD8 BC1 BF1 bC8 bF8 NB1 NG1 nB8 nG8 PA2 pA7 PB2 pB7 PC2 pC7 PD2 pD7 PE2 pE7 PF2 pF7 PG2 pG7 PH2 pH7";

    // string initialBoardState = "RA1 RH1 rA8 rH8 KE1 kE8";

    // string initialBoardState = "PB7 pA2 rA8 KE1 kE8";

    std::stringstream ss(initialBoardState);
    std::string piece;
    std::string pieceSpecifics;

    char pieceChar;
    int row, col;

    while (std::getline(ss, piece, ' '))
    {
        pieceChar = piece[0];
        col = (int)piece[1] - 'A';
        row = (int)piece[2] - '1';
        
        if(piece.length() == 3)
            AddPiece(pieceChar, row, col);
        else
        {
            // pA4/EL/ER
            // kA5/o-o/o-o-o/

            if(pieceChar == 'k' || pieceChar == 'K')
            {
                King* king = new King(pieceChar, pieceChar == 'K');
                
                std::stringstream specificsSS(piece);
                while(std::getline(specificsSS, pieceSpecifics, '/'))
                {
                    if(pieceSpecifics == "o-o")
                        king->SetIsShortCastlingPossible();

                    if(pieceSpecifics == "o-o-o")
                        king->SetIsLongCastlingPossible();
                }

                AddPiece(king, row, col);
            }

            if(pieceChar == 'p' || pieceChar == 'P')
            {
                Pawn* pawn = new Pawn(pieceChar, pieceChar == 'P');

                std::stringstream specificsSS(piece);
                while(std::getline(specificsSS, pieceSpecifics, '/'))
                {
                    if(pieceSpecifics == "T")
                        pawn->SetCanMoveTwoSteps();
                    if(pieceSpecifics == "L")
                        pawn->SetCanEnPassantLeft();
                    if(pieceSpecifics == "R")
                        pawn->SetCanEnPassantRight();
                }

                AddPiece(pawn, row, col);
            }
        }
    }
}

void Board::ResetAllPieceInfo()
{
    for (int i = 0; i < pieceCount; i++)
    {
        if (pieces[i] == nullptr)
        {
            std::cout << "ERROR: Found NULL piece at index " << i << std::endl;
            continue;
        }

        pieces[i]->ResetPieceInfo();
    }
}

void Board::ResetPawnsTwoStepsMove(bool isWhite)
{
    Pawn **pawns = isWhite ? whitePawns : blackPawns;
    int pawnCount = isWhite ? whitePawnCount : blackPawnCount;

    for (int i = 0; i < pawnCount; i++)
    {
        if (pawns[i] == nullptr)
        {
            std::cout << "ERROR: Found NULL pawn at index " << i << std::endl;
            continue;
        }

        if(pawns[i]->GetHasMovedTwoSteps())
            pawns[i]->SetHasMovedTwoSteps(false);
    }
}

void Board::ExecuteCommands()
{
    Command* command;

    while(!commandQueue.empty())
    {
        command = commandQueue.front();

        command->Execute();

        commandQueue.pop();
    }
}

void Board::PreprocessAllPieceAttacks()
{
    // cout << "Starting Preprocessed Attack : " << endl;
    for (int i = 0; i < pieceCount; i++)
    {
        // cout << "Preprocessed Attack for : " << endl;
        // pieces[i]->PrintPiece();
        // cout << endl;
        // cout << "Piece position : " << pieces[i]->GetPosition().row << " " << pieces[i]->GetPosition().col << endl;

        pieces[i]->PreprocessAttackInfo(this);
    }
}

void Board::SetAllPieceLegalMoves()
{
    // cout << endl
    //      << "Refreshing All Legal moves!" << endl;
    for (int i = 0; i < pieceCount; i++)
    {
        if (!pieces[i]->GetIsKing())
        {
            // cout << endl
            //      << "Refresh Legal Moves for : " << endl;
            // pieces[i]->PrintPiece();
            // cout << endl;
            // cout << "Piece position : " << pieces[i]->GetPosition().row << " " << pieces[i]->GetPosition().col << endl;
            pieces[i]->SetLegalPositions(this);
        }
    }

    // cout << endl
    //      << "Refresh Legal Moves for : " << endl;
    // whiteKing->PrintPiece();
    // cout << endl;
    // cout << "Piece position : " << whiteKing->GetPosition().row << " " << whiteKing->GetPosition().col << endl;
    whiteKing->SetLegalPositions(this);

    // cout << endl
    //      << "Refresh Legal Moves for : " << endl;
    // blackKing->PrintPiece();
    // cout << endl;
    // cout << "Piece position : " << blackKing->GetPosition().row << " " << blackKing->GetPosition().col << endl;
    blackKing->SetLegalPositions(this);
}

bool Board::CheckForDraw()
{
    // Repeating moves
    if (CheckIfPositionRepeatedThrice())
        return true;

    // Insufficient material
    if (pieceCount == 2)
        return true;

    if (pieceCount == 3 && (whiteKnightCount == 1 || blackKnightCount == 1 || whiteBlackBishopCount == 1 || blackBlackBishopCount == 1 || whiteWhiteBishopCount == 1 || whiteBlackBishopCount == 1))
        return true;

    if (pieceCount == 4 && ((blackWhiteBishopCount == 1 && whiteWhiteBishopCount == 1) || (blackBlackBishopCount == 1 && whiteBlackBishopCount == 1)))
        return true;

    // Fifty move rule
    if (moveCountWithoutPawnMoveOrCapture == 50)
        return true;

    return false;
}

bool Board::CheckIfPositionRepeatedThrice()
{
    for (const auto &pair : positionCount)
    {
        if (pair.second >= 3)
            return true;
    }

    return false;
}

void Board::ClearBoard()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].ClearPiece();
        }
    }
}

void Board::DisplayBoard()
{
    cout << endl;
    for(int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        cout << i+1 << " |";
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].PrintSquare();
            cout << "|";
        }
        cout << endl;
    }
    cout << "   A B C D E F G H" << endl << endl;
}

void Board::DisplayBoard(spn::Canvas* canvas)
{
	canvas->DrawImage(&boardImage, 0, 0);
}

void Board::MarkPositions(LegalPositionData *legalPositionData)
{
    Position* positions = legalPositionData->legalPositions;

    for(int i = 0; i < legalPositionData->numberOfPositions; i++)
    {
        board[positions[i].row][positions[i].col].MarkSquare();
    }
}

void Board::UnMarkPositions()
{
    for(int i = BOARD_SIZE - 1; i >= 0; i--)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j].UnMarkSquare();
        }
    }
}

void Board::AddPiece(Piece *piece, int row, int col)
{
    board[row][col].SetPiece(piece);

    if(piece->GetIsWhite())
    {
        whitePieces[whitePieceCount++] = piece;
        
        if (piece->GetIsKing())
            whiteKing = piece;
        else if (piece->GetPieceType() == PieceType::Bishop)
            (row + col) % 2 == 0 ? whiteBlackBishopCount++ : whiteWhiteBishopCount++;
        else if (piece->GetPieceType() == PieceType::Knight)
            whiteKnightCount++;
        else if (piece->GetPieceType() == PieceType::Pawn)
            whitePawns[whitePawnCount++] = (Pawn*)piece;
    }
    else
    {
        blackPieces[blackPieceCount++] = piece;
        
        if (piece->GetIsKing())
            blackKing = piece;
        else if (piece->GetPieceType() == PieceType::Bishop)
            (row + col) % 2 == 0 ? blackBlackBishopCount++ : blackWhiteBishopCount++;
        else if (piece->GetPieceType() == PieceType::Knight)
            blackKnightCount++;
        else if (piece->GetPieceType() == PieceType::Pawn)
            blackPawns[blackPawnCount++] = (Pawn*)piece;
    }

    pieces[pieceCount++] = piece;
}

void Board::AddPiece(char pieceChar, int row, int col)
{
    auto [pieceType, isWhite] = GetPieceTypeAndIsWhiteForChar(pieceChar);

    if (pieceType == PieceType::None)
    {
        cout << "Invalid piece char!" << endl;
        return;
    }

    switch (pieceType)
    {
    case PieceType::King:
        AddPiece(new King(pieceChar, isWhite), row, col);
        break;
    case PieceType::Queen:
        AddPiece(new Queen(pieceChar, isWhite), row, col);
        break;
    case PieceType::Bishop:
        AddPiece(new Bishop(pieceChar, isWhite), row, col);
        break;
    case PieceType::Knight:
        AddPiece(new Knight(pieceChar, isWhite), row, col);
        break;
    case PieceType::Rook:
        AddPiece(new Rook(pieceChar, isWhite), row, col);
        break;
    case PieceType::Pawn:
        AddPiece(new Pawn(pieceChar, isWhite), row, col);
        break;
    default:
        break;
    }
}

void Board::RemovePiece(Piece *pieceToRemove)
{
    bool swap = false;
    for(int i = 0; i < pieceCount; i++)
    {
        if(pieces[i] == pieceToRemove)
        {
            swap = true;
        }

        if(swap)
        {
            if(i + 1 < pieceCount)
            {
                pieces[i] = pieces[i + 1];
            }
        }
    }

    if (swap)
    {
        pieces[pieceCount] = nullptr;
        pieceCount--;
    }

    if(pieceToRemove->GetIsWhite())
    {
        swap = false;

        for(int i = 0; i < whitePieceCount; i++)
        {
            if(whitePieces[i] == pieceToRemove)
            {
                swap = true;
            }

            if(swap)
            {
                if(i + 1 < whitePieceCount)
                {
                    whitePieces[i] = whitePieces[i + 1];
                }
            }   
        }

        if (swap)
        {
            whitePieces[whitePieceCount] = nullptr;
            whitePieceCount--;
        }
    }
    else
    {
        swap = false;

        for(int i = 0; i < blackPieceCount; i++)
        {
            if(blackPieces[i] == pieceToRemove)
            {
                swap = true;
            }

            if(swap)
            {
                if(i + 1 < blackPieceCount)
                {
                    blackPieces[i] = blackPieces[i + 1];
                }
            }
        }

        if (swap)
        {
            blackPieces[blackPieceCount] = nullptr;
            blackPieceCount--;
        }
    }
}

bool Board::MovePieceToSquare(Piece *selectedPiece, int row, int col)
{
    Position oldPosition = selectedPiece->GetPosition();

    Square *source = &board[oldPosition.row][oldPosition.col];
    Square *destination = &board[row][col];

    moveCountWithoutPawnMoveOrCapture++;

    if(destination->GetPiece() == NULL)
    {
        if (selectedPiece->GetPieceType() == PieceType::Pawn)
        {
            Pawn* pawn = (Pawn*)selectedPiece;

            moveCountWithoutPawnMoveOrCapture = 0;
            
            if(row - oldPosition.row == 2 || row - oldPosition.row == -2)
            {
                pawn->SetHasMovedTwoSteps(true);
            }

            // En passant
            if(col - oldPosition.col == 1 || col - oldPosition.col == -1)
            {
                Command* enPassantCommand = new EnPassantCommand(this, pawn, source, destination, GetSquare(row, col));
                AddCommandToQueue(enPassantCommand);

                return true;
            }

            // Promotion
            // Check if pawn reached the last row
            bool promotion = pawn->GetIsWhite() ? row == 7 : row == 0;
            if(promotion)
            {
                PieceType pieceTypeToPromoteTo = GetPromotionPieceType();

                Command* promoteCommand = new PromoteCommand(this, pieceTypeToPromoteTo, pawn);
                AddCommandToQueue(promoteCommand);

                return true;
            }
        }
        else if(selectedPiece->GetPieceType() == PieceType::King)
        {
            King* king = (King*)selectedPiece;

            if(col - oldPosition.col == 2 || col - oldPosition.col == -2)
            {
                bool isLongCastling = (col - oldPosition.col == -2);

                // Castling
                // loop until the end and rook is found in the direction of the move

                for(int i = isLongCastling ? col - 1 : col + 1; isLongCastling ? i >= 0 : i < BOARD_SIZE; isLongCastling ? i-- : i++)
                {
                    Piece* rook = board[king->GetPosition().row][i].GetPiece();

                    if(rook != nullptr)
                    {
                        if(rook->GetPieceType() == PieceType::Rook)
                        {
                            int rookRow;
                            int rookCol;
                            int kingRow;
                            int kingCol;

                            GetCastlingPositions(rookRow, rookCol, kingRow, kingCol, king->GetIsWhite(), isLongCastling);

                            Square* kingDestination = &board[kingRow][kingCol];
                            Square* rookDestination = &board[rookRow][rookCol];

                            Square* rookSource = &board[rook->GetPosition().row][rook->GetPosition().col];

                            Command* castlingCommand = new CastleCommand(this, king, (Rook*)rook, source, kingDestination, rookSource, rookDestination);
                            AddCommandToQueue(castlingCommand);

                            return true;
                        }
                        else
                        {
                            cout << "Error: Found piece that's not rook in path!" << endl;
                            return false;
                        }
                    }
                }
            }
        }

        Command* moveCommand = new MoveCommand(this, selectedPiece, source, destination);
        AddCommandToQueue(moveCommand);
    }
    else
    {
        Command* captureCommand = new CaptureCommand(this, selectedPiece, source, destination);
        AddCommandToQueue(captureCommand);

        moveCountWithoutPawnMoveOrCapture = 0;
    }

    return true;
}

bool Board::CheckIfPositionProtected(int row, int col, bool protectedByWhite)
{
    Piece** currentPieces = protectedByWhite ? whitePieces : blackPieces;
    int pieceCount = protectedByWhite ? whitePieceCount : blackPieceCount;

    for(int i = 0; i < pieceCount; i++)
    {
        if (currentPieces[i]->CheckIfPositionInLegalPositionsWithoutKing(row, col))
            return true;
    }

    return false;
}

bool Board::CheckIfAnyLegalMovesAvailable(bool isWhite)
{
    Piece **currentPieces = isWhite ? whitePieces : blackPieces;
    int currentPiecesCount = isWhite ? whitePieceCount : blackPieceCount;

    for (int i = 0; i < currentPiecesCount; i++)
    {
        if (currentPieces[i]->GetLegalPositionData()->numberOfPositions > 0)
            return true;
    }

    return false;
}

#pragma region Board State

string Board::GetBoardState()
{
    std::ostringstream oss;

    Piece* piece = nullptr;

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            piece = board[row][col].GetPiece();

            if(piece != nullptr)
            {
                // std::cout << typeid(piece).name() << std::endl;
                oss << GetCodeForPiece(piece) << " ";
            }
        
            piece = nullptr;
        }
    }

    std::string result = oss.str();
    
    result.pop_back();
    return result;
}

void Board::TrackBoardState(const string &boardState)
{
    // cout << boardState << endl;
    positionCount[boardState]++;
}

Square *Board::GetSquare(int row, int col)
{
    return (&board[row][col]);
}

#pragma endregion
