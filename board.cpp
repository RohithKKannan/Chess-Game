#include "header.h"

Board::Board()
{
    board = new Square*[8];

    for(int i = 0; i < 8; i++)
    {
        board[i] = new Square[8];
    }
}

Board::~Board()
{
    for(int i = 0; i < 8; i++)
    {
        delete board[i];
    }

    delete board;
}

void Board::DisplayBoard()
{
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
    cout << "   A B C D E F G H" << endl;
}