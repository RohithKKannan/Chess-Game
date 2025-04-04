#include "header.h"

Board::Board()
{
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

    pieceCount = 0;
    whitePieceCount = 0;
    blackPieceCount = 0;
    whitePawnCount = 0;
    blackPawnCount = 0;
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
    string initialBoardState = "RA1 RH1 rA8 rH8 KE1 kE8 QD1 qD8 BC1 BF1 bC8 bF8 NB1 NG1 nB8 nG8 PA2 pA7 PB2 pB7 PC2 pC7 PD2 pD7 PE2 pE7 PF2 pF7 PG2 pG7 PH2 pH7";

    std::stringstream ss(initialBoardState);
    std::string word;

    char pieceChar;
    int row, col;

    while (std::getline(ss, word, ' '))
    {
        pieceChar = word[0];
        col = (int)word[1] - 'A';
        row = (int)word[2] - '1';

        AddPiece(pieceChar, row, col);
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

    piece->SetPosition(row, col);

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

    Piece *piece = nullptr;

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

    delete pieceToRemove;
}

bool Board::MovePieceToSquare(Piece *selectedPiece, int row, int col)
{
    // Check if destination square is occupied

    Square *destination = &board[row][col];

    Position oldPosition = selectedPiece->GetPosition();
    
    Square *source = &board[oldPosition.row][oldPosition.col];
    source->ClearPiece();

    if(destination->GetPiece() == NULL)
    {
        destination->SetPiece(selectedPiece);

        if (selectedPiece->GetPieceType() == PieceType::Pawn)
        {
            Pawn* pawn = (Pawn*)selectedPiece;
            
            if(row - oldPosition.row == 2 || row - oldPosition.row == -2)
            {
                pawn->SetHasMovedTwoSteps(true);
            }

            // En passant
            // Check if pawn moved diagonally
            // Check if the square in the direction of the move , in the same row, is occupied by an opponent's pawn
            // Remove that pawn from the board
            
            if(col - oldPosition.col == 1 || col - oldPosition.col == -1)
            {
                int opponentRow = oldPosition.row;
                int opponentCol = col;

                Piece* opponentPiece = board[opponentRow][opponentCol].GetPiece();
    
                if(opponentPiece != NULL && opponentPiece->GetIsWhite() != selectedPiece->GetIsWhite() && opponentPiece->GetPieceType() == PieceType::Pawn)
                {
                    Piece* removedPiece = board[opponentRow][opponentCol].ClearPiece();

                    RemovePiece(removedPiece);
                }
            }

            moveCountWithoutPawnMoveOrCapture = 0;
        }
        else
            moveCountWithoutPawnMoveOrCapture++;
    }
    else
    {
        // Take over -> Black takes white and vice versa
        Piece* removedPiece = destination->ClearPiece();

        destination->SetPiece(selectedPiece);
    
        RemovePiece(removedPiece);

        moveCountWithoutPawnMoveOrCapture = 0;
    }

    selectedPiece->SetPieceMoved();

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

Square *Board::SelectSquare(int row, int col)
{
    return &board[row][col];
}

#pragma region Directional processing

bool Board::ProcessAttackInDirection(Piece *piece, int rowDir, int colDir)
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

    // cout << "Piece square " << row << " " << col << " Limit : " << limit << endl;

    for (int i = 1; i < limit; i++)
    {
        int newRow = row + (i * rowDir);
        int newCol = col + (i * colDir);

        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE)
            break; // Out of bounds, stop checking

        // cout << "Checking square at " << newRow << " " << newCol << endl;

        currentSquare = &board[newRow][newCol];
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
                    firstPiece->AddSquareToAttackPath(SelectSquare(row, col));
                    break;
                }
            }
        }

        attackPath[attackPathIndex++] = currentSquare;
    }

    // cout << "Direction complete!" << endl;

    return true;
}

bool Board::SetLegalMovesInDirection(Piece *piece, int rowDir, int colDir)
{
    int row = piece->GetPosition().row;
    int col = piece->GetPosition().col;

    // cout << "Piece square " << row << " " << col << endl;

    Piece *king = GetKing(piece->GetIsWhite());

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

        // cout << "Checking square at " << newRow << " " << newCol << endl;

        if (piece->GetIsPinned() && !piece->CheckIfAttackPathContainsPosition(newRow, newCol))
        {
            // cout << "Pinned piece and Square " << newRow << " " << newCol << " not in attack path" << endl;
            continue;
        }

        // cout << "Adding square " << newRow << " " << newCol << " to Legal Positions without King " << endl;

        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].row = newRow;
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].col = newCol;

        legalPositionData->numberOfPositionsWithoutKing++;

        tempPiece = board[newRow][newCol].GetPiece();

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
                    // cout << "King in check and Square " << newRow << " " << newCol << " not in King's attack path" << endl;
                    continue;
                }

                // cout << "Adding square " << newRow << " " << newCol << " to Legal Positions " << endl;

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
                // cout << "King in check and Square " << newRow << " " << newCol << " not in King's attack path" << endl;
                continue;
            }

            // cout << "Adding square " << newRow << " " << newCol << " to Legal Positions " << endl;

            legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
            legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;

            legalPositionData->numberOfPositions++;
        }
    }

    // cout << "Direction complete!" << endl
    //  << endl;

    return true;
}

#pragma endregion

#pragma region Knight

bool Board::ProcessKnightAttack(Piece *knight, int rowDir, int colDir)
{
    int row = knight->GetPosition().row + rowDir;
    int col = knight->GetPosition().col + colDir;

    Piece *tempPiece;
    Square *attackingSquare;

    Piece *king = GetKing(knight->GetIsWhite());

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    // cout << "Preprocessing Knight at " << row << " " << col << endl;

    attackingSquare = &board[knight->GetPosition().row][knight->GetPosition().col];

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        tempPiece = board[row][col].GetPiece();
        if (tempPiece != nullptr && (tempPiece->GetIsWhite() != knight->GetIsWhite()) && tempPiece->GetIsKing())
        {
            // knight attacks opp king
            tempPiece->SetKingIsInCheck();
            tempPiece->AddSquareToAttackPath(attackingSquare);
            return false;
        }
    }

    return true;
}

bool Board::SetLegalMoveForKnight(Piece *knight, int rowDir, int colDir)
{
    int row = knight->GetPosition().row + rowDir;
    int col = knight->GetPosition().col + colDir;

    Piece *tempPiece;
    Square *attackingSquare;

    Piece *king = GetKing(knight->GetIsWhite());

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        // cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    LegalPositionData *legalPositionData = knight->GetLegalPositionData();

    attackingSquare = &board[knight->GetPosition().row][knight->GetPosition().col];

    int count = 0;

    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].row = row;
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].col = col;

        legalPositionData->numberOfPositionsWithoutKing++;

        tempPiece = board[row][col].GetPiece();

        if (knight->GetIsPinned() && !knight->CheckIfAttackPathContainsPosition(row, col))
        {
            return false;
        }

        if (tempPiece != nullptr)
        {
            if (tempPiece->GetIsWhite() == knight->GetIsWhite())
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

string Board::GetBoardState()
{
    ostringstream oss;

    for (int i = 0; i < pieceCount; i++)
    {
        oss << GetCodeForPiece(pieces[i]) << ' ';
    }

    return oss.str();
}

void Board::TrackBoardState(const string &boardState)
{
    positionCount[boardState]++;
}

#pragma endregion
