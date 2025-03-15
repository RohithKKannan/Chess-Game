#include <iostream>
using namespace std;

#define BOARD_SIZE 8

#pragma region Data Classes

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

#pragma endregion

class Piece;

#pragma region Board Elements

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

#pragma endregion

#pragma region Pieces

class Piece
{
    private:
        char piece;
        bool isWhite;
        Position position;

    public:
        Piece(char, bool);
        virtual ~Piece();
        void SetPosition(int, int);
        void PrintPiece();
        bool GetIsWhite() { return isWhite; };
        Position GetPosition();
        virtual void GetLegalPositions(int, int, Board*, LegalPositionData*)= 0;
};

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        void GetLegalPositions(int, int, Board*, LegalPositionData*);
};

#pragma endregion

#pragma region Gameplay

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

#pragma endregion
