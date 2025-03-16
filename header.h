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
        Position GetPosition() { return position; };
        void MarkSquare();
        void UnMarkSquare();
        void SetPiece(Piece *);
        Piece* ClearPiece();
        void PrintSquare();
};

class Board
{
    private:
        Piece** pieces;
        Piece** whitePieces;
        Piece** blackPieces;
        int whitePieceCount;
        int blackPieceCount;
        int pieceCount;

    public:
        Square **board;
        Board();
        ~Board();
        void SetupBoard();
        void RefreshAllLegalMoves();
        void ClearBoard();
        void DisplayBoard();
        void MarkPositions(LegalPositionData*);
        void UnMarkPositions();
        void AddPiece(Piece*, int, int);
        void RemovePiece(Piece*);
        bool MovePieceToSquare(Piece*, int, int);
        bool CheckIfPositionProtected(int row, int col, bool protectedByWhite);
        bool CheckIfAnyLegalMovesAvailable(bool isWhite);
        Square *SelectSquare(int, int);
};

#pragma endregion

#pragma region Pieces

class Piece
{
    protected:
        char piece;
        bool isWhite;
        bool isKing;
        Position position;
        LegalPositionData *legalPositionData;

    public:
        Piece(char, bool);
        virtual ~Piece();
        void SetPosition(int, int);
        void PrintPiece();
        bool GetIsKing() { return isKing; };
        bool GetIsWhite() { return isWhite; };
        Position GetPosition();
        LegalPositionData* GetLegalPositionData() { return legalPositionData; };
        bool CheckIfPositionInLegalPositions(int, int);
        virtual void RefreshLegalPositions(Board*)= 0;
};

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        void RefreshLegalPositions(Board*);
};

class King: public Piece
{
    public:
        King(char piece, bool isWhite);
        ~King();
        void RefreshLegalPositions(Board*);
};

class Queen: public Piece
{
    public:
        Queen(char piece, bool isWhite);
        ~Queen();
        void RefreshLegalPositions(Board*);
};

class Bishop: public Piece
{
    public:
        Bishop(char piece, bool isWhite);
        ~Bishop();
        void RefreshLegalPositions(Board*);
};

class Knight: public Piece
{
    public:
        Knight(char piece, bool isWhite);
        ~Knight();
        void RefreshLegalPositions(Board*);
};

class Pawn: public Piece
{
    public:
        Pawn(char piece, bool isWhite);
        ~Pawn();
        void RefreshLegalPositions(Board*);
};

#pragma endregion

#pragma region Gameplay

enum GameState
{
    WhiteTurn,
    BlackTurn,
    Stalemate,
    WhiteWins,
    BlackWins,
    Draw
};

class GameManager
{
    private:
        Board *board;
        Piece *selectedPiece;
        Square *selectedSquare;
        GameState currentGameState;

    public:
        GameManager();
        ~GameManager();
        void StartGame();
        void InitiateTurn();
        Square *SelectSquare();
        bool ParseInput(string *, int *, int *);
};

#pragma endregion
