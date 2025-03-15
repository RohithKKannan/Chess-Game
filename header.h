#include <iostream>
using namespace std;

class Piece
{
    public:
        char piece;
        bool isWhite;
};

class Square
{
    public:
        int row;
        int col;
        Piece *piece;
        Square();
        ~Square();
        void SetPiece(Piece *piece);
        void PrintSquare();
};

class Board
{
    public:
        Square **board;
        Board();
        ~Board();
        void DisplayBoard();
};