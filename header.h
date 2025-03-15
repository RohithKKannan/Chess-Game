#include <iostream>
using namespace std;

struct Position
{
    int row;
    int col;
};

class LegalPositionData
{
    public:
        Position* legalPositions;
        int numberOfPositions;
        LegalPositionData();
        ~LegalPositionData();
};

class Board;

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
        virtual void GetLegalPositions(int, int, Board*, LegalPositionData*)= 0;
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
        void MarkPositions(LegalPositionData*);
        void UnMarkPositions();
        void MovePieceToSquare(Piece*, int, int);
        Piece* SelectSquare(int,int);
};

class GameManager
{
    private:
        Board *board;
        LegalPositionData *legalPositionData;
        Piece *selectedPiece;
        bool isWhitesTurn;
    public:
        GameManager();
        ~GameManager();
        void StartGame();
        void InitiateTurn();
};

#pragma region Pieces

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        void GetLegalPositions(int, int, Board*, LegalPositionData*);
};

#pragma endregion
