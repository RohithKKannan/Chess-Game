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

    AddPiece(new Queen('Q', true), 0, 3);
    AddPiece(new Queen('q', false), 7, 3);

    AddPiece(new Bishop('B', true), 0, 2);
    AddPiece(new Bishop('B', true), 0, 5);

    AddPiece(new Bishop('b', false), 7, 2);
    AddPiece(new Bishop('b', false), 7, 5);

    AddPiece(new Knight('N', true), 0, 1);
    AddPiece(new Knight('N', true), 0, 6);

    AddPiece(new Knight('n', false), 7, 1);
    AddPiece(new Knight('n', false), 7, 6);

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        AddPiece(new Pawn('P', true), 1, i);
        AddPiece(new Pawn('p', false), 6, i);
    }
}

void Board::RefreshAllLegalMoves()
{
    for (int i = 0; i < pieceCount; i++)
    {
        pieces[i]->RefreshLegalPositions(this);
    }
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
        whitePieces[whitePieceCount++] = piece;
    else
        blackPieces[blackPieceCount++] = piece;

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
        if(currentPieces[i]->CheckIfPositionInLegalPositions(row, col))
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
