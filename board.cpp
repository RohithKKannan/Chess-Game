#include "header.h"

Board::Board()
{
    board = new Square*[8];

    for(int i = 0; i < 8; i++)
    {
        board[i] = new Square[8];

        for (int j = 0; j < 8; j++)
        {
            board[i][j].SetPosition(i, j);
        }
    }
}

Board::~Board()
{
    for(int i = 0; i < 8; i++)
    {
        delete[] board[i];
    }

    delete[] board;
}

void Board::SetupBoard()
{
    Rook *whiteRook1 = new Rook('R', true);
    board[0][0].SetPiece(whiteRook1);

    Rook *whiteRook2 = new Rook('R', true);
    board[0][7].SetPiece(whiteRook2);

    Rook *blackRook1 = new Rook('r', false);
    board[7][0].SetPiece(blackRook1);

    Rook *blackRook2 = new Rook('r', false);
    board[7][7].SetPiece(blackRook2);
}

void Board::ClearBoard()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j].ClearPiece();
        }
    }
}

void Board::DisplayBoard()
{
    cout << endl;
    for(int i = 7; i >= 0; i--)
    {
        cout << i+1 << " |";
        for(int j = 0; j < 8; j++)
        {
            board[i][j].PrintSquare();
            cout << "|";
        }
        cout << endl;
    }
    cout << "   A B C D E F G H" << endl << endl;
}

void Board::MarkPositions(LegalPositions *legalPositions)
{
    Position* positions = legalPositions->positions;

    for(int i = 0; i < legalPositions->numberOfPositions; i++)
    {
        board[positions[i].row][positions[i].col].MarkSquare();
    }
}

void Board::UnMarkPositions()
{
    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j].UnMarkSquare();
        }
    }
}

void Board::MovePieceToSquare(Piece *selectedPiece, int row, int col)
{
    // Check if destination square is occupied

    Square *destination = &board[row][col];

    if(destination->piece != NULL)
    {
        // Take over -> Black takes white and vice versa
        return;
    }

    Position oldPosition = selectedPiece->GetPosition();

    Square *source = &board[oldPosition.row][oldPosition.col];
    source->ClearPiece();

    destination->SetPiece(selectedPiece);
}

Piece* Board::SelectSquare(int row, int col)
{
    if(board[row][col].piece == NULL)
        return NULL;

    return board[row][col].piece;
}
