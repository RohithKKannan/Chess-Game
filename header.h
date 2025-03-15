#include <iostream>
using namespace std;

struct Position
{
    int row;
    int col;
};

class LegalPositions
{
    public:
        Position* positions;
        int numberOfPositions;
        LegalPositions();
        ~LegalPositions();
};

class Piece
{
    private:
        char piece;
        bool isWhite;
        Position position;

    public:
        Piece(char, bool);
        void SetPosition(int, int);
        virtual ~Piece();
        void PrintPiece();
        Position GetPosition();
        virtual LegalPositions* GetLegalPositions(int, int) = 0;
};

class Square
{
    private:
        Position position;
        bool isMarked;

    public:
        Piece *piece;
        Square();
        ~Square();
        void SetPosition(int, int);
        void MarkSquare();
        void UnMarkSquare();
        void SetPiece(Piece *);
        void ClearPiece();
        void PrintSquare();
};

class Board
{
    public:
        Square **board;
        Board();
        ~Board();
        void SetupBoard();
        void ClearBoard();
        void DisplayBoard();
        void MarkPositions(LegalPositions*);
        void UnMarkPositions();
        void MovePieceToSquare(Piece*, int, int);
        Piece* SelectSquare(int,int);
};

#pragma region Pieces

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        LegalPositions* GetLegalPositions(int, int);
};

#pragma endregion
