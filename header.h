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
        Position *legalPositionsWithoutKing;
        int numberOfPositions;
        int numberOfPositionsWithoutKing;
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
        Piece *whiteKing;
        Piece *blackKing;

    public:
        Square **board;
        Board();
        ~Board();
        void SetupBoard();
        void ResetAllPieceInfo();
        void PreprocessAllAttacks();
        void SetAllLegalMoves();
        bool CheckForDraw();
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
        Piece *GetKing(bool isWhite) { return isWhite ? whiteKing : blackKing; };
        bool ProcessAttackInDirection(Piece *piece, int rowDir, int colDir, bool isPawn);
        bool SetLegalMovesInDirection(Piece *piece, int rowDir, int colDir, bool isPawn, bool hasPawnMoved);
};

#pragma endregion

#pragma region Pieces

class Piece
{
    protected:
        char piece;
        bool isWhite;
        bool isKing = false;
        bool hasMoved = false;
        Position position;
        LegalPositionData *legalPositionData;

        bool isPinned;

        Piece *pinningPiece;

        bool isInCheck;
        int attackerCount;

        Square **attackPath;
        int attackPathSquareCount;

    public:
        Piece(char, bool);
        virtual ~Piece();
        void SetPosition(int, int);
        void PrintPiece();
        bool GetIsKing() { return isKing; };
        bool GetIsWhite() { return isWhite; };
        bool GetIsInCheck() { return isInCheck; };
        bool GetIsPinned() { return isPinned; };
        int GetAttackerCount() { return attackerCount; };
        Position GetPosition() { return position; };
        LegalPositionData* GetLegalPositionData() { return legalPositionData; };
        bool CheckIfPositionInLegalPositionsWithoutKing(int, int);
        void ResetPieceInfo();
        virtual void PreprocessAttackInfo(Board *) = 0;
        virtual void SetLegalPositions(Board *) = 0;

        void SetPieceHasMoved() { hasMoved = true; };
        void SetPieceIsPinned() { isPinned = true; };
        void AddPieceToPinningPiece(Piece *piece) { pinningPiece = piece; };
        void SetKingIsInCheck() { isInCheck = true; };
        void AddSquareToAttackPath(Square *square) { attackPath[attackPathSquareCount++] = square; };
        bool CheckIfAttackPathContainsPosition(int row, int col);
};

class Rook: public Piece
{
    public:
        Rook(char piece, bool isWhite);
        ~Rook();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

class King: public Piece
{
    public:
        King(char piece, bool isWhite);
        ~King();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

class Queen: public Piece
{
    public:
        Queen(char piece, bool isWhite);
        ~Queen();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

class Bishop: public Piece
{
    public:
        Bishop(char piece, bool isWhite);
        ~Bishop();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

class Knight: public Piece
{
    public:
        Knight(char piece, bool isWhite);
        ~Knight();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

class Pawn: public Piece
{
    public:
        Pawn(char piece, bool isWhite);
        ~Pawn();
        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
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
        void Game();
        void InitiateTurn();
        Square *SelectSquare();
        bool ParseInput(string *, int *, int *);
};

#pragma endregion
