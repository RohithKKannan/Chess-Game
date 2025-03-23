#include "header.h"

Board::Board()
{
    pieces = new Piece*[32];
    whitePieces = new Piece*[16];
    blackPieces = new Piece*[16];

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
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        delete[] board[i];
    }

    for(int i = 0; i < 16; i++)
    {
        delete whitePieces[i];
        delete blackPieces[i];
    }

    delete[] whitePieces;
    delete[] blackPieces;
    delete[] board;
}

void Board::SetupBoard()
{
    AddPiece(new Rook('R', true), 0, 0);
    AddPiece(new Rook('R', true), 0, 7);

    AddPiece(new Rook('r', false), 7, 0);
    AddPiece(new Rook('r', false), 7, 7);

    AddPiece(new King('K', true), 0, 4);
    AddPiece(new King('k', false), 7, 4);

    // AddPiece(new Queen('Q', true), 0, 3);
    // AddPiece(new Queen('q', false), 7, 3);

    // AddPiece(new Bishop('B', true), 0, 2);
    // AddPiece(new Bishop('B', true), 0, 5);

    // AddPiece(new Bishop('b', false), 7, 2);
    // AddPiece(new Bishop('b', false), 7, 5);

    // AddPiece(new Knight('N', true), 0, 1);
    // AddPiece(new Knight('N', true), 0, 6);

    // AddPiece(new Knight('n', false), 7, 1);
    // AddPiece(new Knight('n', false), 7, 6);

    // for(int i = 0; i < BOARD_SIZE; i++)
    // {
    //     AddPiece(new Pawn('P', true), 1, i);
    //     AddPiece(new Pawn('p', false), 6, i);
    // }
}

void Board::ResetAllPieceInfo()
{
    for (int i = 0; i < pieceCount; i++)
    {
        pieces[i]->ResetPiecesInfo();
    }
}

void Board::PreprocessAllAttacks()
{
    cout << "Starting Preprocessed Attack : " << endl;
    for (int i = 0; i < pieceCount; i++)
    {
        cout << "Preprocessed Attack for : " << endl;
        pieces[i]->PrintPiece();
        cout << endl;
        cout << "Piece position : " << pieces[i]->GetPosition().row << " " << pieces[i]->GetPosition().col << endl;

        pieces[i]->PreprocessAttackInfo(this);
    }
}

void Board::SetAllLegalMoves()
{
    cout << endl
         << "Refreshing All Legal moves!" << endl;
    for (int i = 0; i < pieceCount; i++)
    {
        cout << endl
             << "Refresh Legal Moves for : " << endl;
        pieces[i]->PrintPiece();
        cout << endl;
        cout << "Piece position : " << pieces[i]->GetPosition().row << " " << pieces[i]->GetPosition().col << endl;
        if (!pieces[i]->GetIsKing())
            pieces[i]->SetLegalPositions(this);
    }

    cout << endl
         << "Refresh Legal Moves for : " << endl;
    whiteKing->PrintPiece();
    cout << endl;
    cout << "Piece position : " << whiteKing->GetPosition().row << " " << whiteKing->GetPosition().col << endl;
    whiteKing->SetLegalPositions(this);

    cout << endl
         << "Refresh Legal Moves for : " << endl;
    blackKing->PrintPiece();
    cout << endl;
    cout << "Piece position : " << blackKing->GetPosition().row << " " << blackKing->GetPosition().col << endl;
    blackKing->SetLegalPositions(this);
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
    }
    else
    {
        blackPieces[blackPieceCount++] = piece;
        if (piece->GetIsKing())
            blackKing = piece;
    }

    pieces[pieceCount++] = piece;
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

    if(swap) pieceCount--;

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

    if(destination->piece == NULL)
    {
        destination->SetPiece(selectedPiece);
    }
    else
    {
        // Take over -> Black takes white and vice versa
        Piece* removedPiece = destination->ClearPiece();

        destination->SetPiece(selectedPiece);
    
        RemovePiece(removedPiece);
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

Square *Board::SelectSquare(int row, int col)
{
    return &board[row][col];
}

bool Board::ProcessAttackInDirection(Piece *piece, int rowDir, int colDir, bool tillEnd)
{
    Piece *firstPiece = nullptr;
    Piece *secondPiece = nullptr;

    Square **attackPath = new Square *[100];
    int attackPathIndex = 0;

    int row = piece->GetPosition().row;
    int col = piece->GetPosition().col;

    Piece *tempPiece;
    Square *currentSquare;

    cout << "Piece square " << row << " " << col << endl;

    for (int i = 1; i < tillEnd ? BOARD_SIZE : 2; i++)
    {
        int newRow = row + (i * rowDir);
        int newCol = col + (i * colDir);

        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE)
            break; // Out of bounds, stop checking

        cout << "Checking square at " << newRow << " " << newCol << endl;

        currentSquare = &board[newRow][newCol];
        tempPiece = currentSquare->piece;

        if (tempPiece != nullptr)
        {
            if (tempPiece->GetIsWhite() == piece->GetIsWhite())
            {
                cout << "Piece encountered - Same color - Ending traversal!" << endl;
                // piece of same color -> end traversal
                break;
            }

            if (firstPiece == nullptr)
            {
                cout << "First Piece encountered : " << endl;
                firstPiece = tempPiece;
                firstPiece->PrintPiece();
                cout << endl;
                if (firstPiece->GetIsKing())
                {
                    cout << "First piece is king - setting in check - adding attack path" << endl;
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
                cout << "Second Piece encountered" << endl;
                secondPiece = tempPiece;
                secondPiece->PrintPiece();
                cout << endl;
                if (secondPiece->GetIsKing())
                {
                    cout << "Second piece is king - setting first piece is pinned - adding pin path" << endl;
                    firstPiece->SetPieceIsPinned();
                    for (int i = 0; i < attackPathIndex; i++)
                    {
                        cout << "Adding square " << attackPath[i]->GetPosition().row << " " << attackPath[i]->GetPosition().col << endl;
                        firstPiece->AddSquareToAttackPath(attackPath[i]);
                    }
                    // Add attacking piece to attack path
                    cout << "Adding current square " << row << " " << col << endl;
                    firstPiece->AddSquareToAttackPath(SelectSquare(row, col));
                    break;
                }
            }
        }

        attackPath[attackPathIndex++] = currentSquare;
    }

    cout << "Direction complete!" << endl;

    return true;
}

bool Board::SetLegalMovesInDirection(Piece *piece, int rowDir, int colDir, bool tillEnd)
{
    int row = piece->GetPosition().row;
    int col = piece->GetPosition().col;

    cout << "Piece square " << row << " " << col << endl;

    Piece *king = GetKing(piece->GetIsWhite());

    bool kingInCheck = king->GetIsInCheck();

    if (kingInCheck && king->GetAttackerCount() > 1)
    {
        cout << "King in check more than once! Skip legal moves for this piece!" << endl;
        return false;
    }

    LegalPositionData *legalPositionData = piece->GetLegalPositionData();

    Piece *tempPiece;

    for (int i = 1; i < tillEnd ? BOARD_SIZE : 2; i++)
    {
        int newRow = row + (i * rowDir);
        int newCol = col + (i * colDir);

        if (newRow < 0 || newRow >= BOARD_SIZE || newCol < 0 || newCol >= BOARD_SIZE)
            break; // Out of bounds, stop checking

        cout << "Checking square at " << newRow << " " << newCol << endl;

        if (piece->GetIsPinned() && !piece->CheckIfAttackPathContainsPosition(newRow, newCol))
        {
            cout << "Pinned piece and Square " << newRow << " " << newCol << " not in attack path" << endl;
            continue;
        }

        cout << "Adding square " << newRow << " " << newCol << " to Legal Positions without King " << endl;

        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].row = newRow;
        legalPositionData->legalPositionsWithoutKing[legalPositionData->numberOfPositionsWithoutKing].col = newCol;

        legalPositionData->numberOfPositionsWithoutKing++;

        tempPiece = board[newRow][newCol].piece;

        if (tempPiece != NULL)
        {
            cout << "Piece in path : " << endl;
            tempPiece->PrintPiece();
            cout << endl;

            if (tempPiece->GetIsWhite() == piece->GetIsWhite())
            {
                cout << "Piece is of same color! Stop iteration! " << piece->GetIsWhite() << " " << tempPiece->GetIsWhite() << endl;
                break;
            }
            else
            {
                if (kingInCheck && !king->CheckIfAttackPathContainsPosition(newRow, newCol))
                {
                    cout << "King in check and Square " << newRow << " " << newCol << " not in King's attack path" << endl;
                    continue;
                }

                cout << "Adding square " << newRow << " " << newCol << " to Legal Positions " << endl;

                legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
                legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;

                legalPositionData->numberOfPositions++;

                if (!tempPiece->GetIsKing())
                {
                    cout << "Piece found is not king and an opp! End traversal!" << endl;

                    break;
                }
            }
        }
        else
        {
            if (kingInCheck && !king->CheckIfAttackPathContainsPosition(newRow, newCol))
            {
                cout << "King in check and Square " << newRow << " " << newCol << " not in King's attack path" << endl;
                continue;
            }

            cout << "Adding square " << newRow << " " << newCol << " to Legal Positions " << endl;

            legalPositionData->legalPositions[legalPositionData->numberOfPositions].row = newRow;
            legalPositionData->legalPositions[legalPositionData->numberOfPositions].col = newCol;

            legalPositionData->numberOfPositions++;
        }
    }

    cout << "Direction complete!" << endl;

    return true;
}
