#include <iostream>
#include <unordered_map>
#include <sstream>
#include <queue>
using namespace std;

#define BOARD_SIZE 8

enum class PieceType
{
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn,
    None
};

enum BishopType
{
    WhiteBishop,
    BlackBishop
};

#pragma region Data Classes

struct Position
{
    int row;
    int col;
};

class LegalPositionData
{
    public:
        LegalPositionData()
        {
            legalPositions = new Position[100];
            legalPositionsWithoutKing = new Position[100];
            numberOfPositions = 0;
            numberOfPositionsWithoutKing = 0;
        }
        ~LegalPositionData()
        {
            delete[] legalPositions;
            delete[] legalPositionsWithoutKing;
        }

        Position *legalPositions;
        Position *legalPositionsWithoutKing;
        
        int numberOfPositions;
        int numberOfPositionsWithoutKing;
};

#pragma endregion

class Piece;
class Pawn;
class Command;
class MoveCommand;

#pragma region Board Elements

class Square
{
    private:
        Position position;
        bool isMarked;
        Piece *piece;

    public:
        Square();
        ~Square();
        
        void SetPosition(int, int);
        Position GetPosition() { return position; };
        
        void MarkSquare();
        void UnMarkSquare();
        
        void SetPiece(Piece *);
        Piece* GetPiece() { return piece; };
        Piece* ClearPiece();
        
        void PrintSquare();
};

class Board
{
    private:
        Square **board;

        Piece** pieces;
        Piece** whitePieces;
        Piece** blackPieces;
        Pawn** whitePawns;
        Pawn** blackPawns;
        Piece *whiteKing;
        Piece *blackKing;

        int pieceCount = 0;
        int whitePieceCount = 0;
        int blackPieceCount = 0;
        int whitePawnCount = 0;
        int blackPawnCount = 0;

        int blackKnightCount = 0;
        int whiteKnightCount = 0;
        int blackWhiteBishopCount = 0;
        int blackBlackBishopCount = 0;
        int whiteWhiteBishopCount = 0;
        int whiteBlackBishopCount = 0;

        int moveCountWithoutPawnMoveOrCapture = 0;

        string boardState;

        std::unordered_map<string, int> positionCount;

        std::queue<Command*> commandQueue;

    public:
        Board();
        ~Board();

        void SetupBoard();
        void ClearBoard();
        void DisplayBoard();

        bool CheckForDraw();
        bool CheckIfPositionRepeatedThrice();

        void MarkPositions(LegalPositionData*);
        void UnMarkPositions();

        string GetBoardState();
        void TrackBoardState(const string &boardState);

        Square* GetSquare(int row, int col) { return &board[row][col]; };
        Square *SelectSquare(int, int);

        void AddPiece(Piece*, int, int);
        void AddPiece(char, int, int);

        void RemovePiece(Piece*);

        bool MovePieceToSquare(Piece*, int, int);

        bool CheckIfPositionProtected(int row, int col, bool protectedByWhite);
        bool CheckIfAnyLegalMovesAvailable(bool isWhite);

        Piece *GetKing(bool isWhite) { return isWhite ? whiteKing : blackKing; };

        void PreprocessAllPieceAttacks();
        void SetAllPieceLegalMoves();
        void ResetAllPieceInfo();
        void ResetPawnsTwoStepsMove(bool isWhite);

        void AddCommandToQueue(Command* command) { commandQueue.push(command); };
        void ExecuteCommands();
};

#pragma endregion

#pragma region Pieces

class Piece
{
    protected:
        char piece;
        int moveCount = 0;
        bool isWhite;
        PieceType pieceType;

        Position position;
        LegalPositionData *legalPositionData = nullptr;

        bool isPinned;
        Piece *pinningPiece = nullptr;

        bool isInCheck;
        int attackerCount = 0;
        Square **attackPath = new Square *[100];
        int attackPathSquareCount;

    public:
        Piece(char, bool);
        virtual ~Piece();

        void SetPosition(int, int);
        void SetPieceMoved() { moveCount++; };
        void PrintPiece();
        char GetPieceChar() { return piece; };

        bool GetIsKing() { return pieceType == PieceType::King; };
        bool GetIsWhite() { return isWhite; };
        bool GetIsInCheck() { return isInCheck; };
        bool GetIsPinned() { return isPinned; };
        int GetAttackerCount() { return attackerCount; };
        int GetMoveCount() { return moveCount; };
        Position GetPosition() { return position; };
        PieceType GetPieceType() { return pieceType; };
        LegalPositionData* GetLegalPositionData() { return legalPositionData; };

        void SetPieceIsPinned() { isPinned = true; };
        void AddPieceToPinningPiece(Piece *piece) { pinningPiece = piece; };
        void SetKingIsInCheck()
        {
            attackerCount++;
            isInCheck = true;
        };

        virtual void PreprocessAttackInfo(Board *) = 0;
        virtual void SetLegalPositions(Board *) = 0;
        bool CheckIfAttackPathContainsPosition(int row, int col);
        bool CheckIfPositionInLegalPositionsWithoutKing(int, int);
        void AddSquareToAttackPath(Square *square) { attackPath[attackPathSquareCount++] = square; };
        void ResetPieceInfo();
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
    private:
        bool isShortCastlingPossible;
        bool isLongCastlingPossible;
    public:
        King(char piece, bool isWhite);
        ~King();
        bool GetIsShortCastlingPossible() { return isShortCastlingPossible; };
        void SetIsShortCastlingPossible() { isShortCastlingPossible = true; };
        bool GetIsLongCastlingPossible() { return isLongCastlingPossible; };
        void SetIsLongCastlingPossible() { isLongCastlingPossible = true; };
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
        bool ProcessKnightAttack(Board *, int, int);
        bool SetLegalMoveForKnight(Board *, int, int);
};

class Pawn: public Piece
{
    private:
        bool hasMovedTwoSteps;
        bool canMoveTwoSteps;
        bool canEnPassantLeft;
        bool canEnPassantRight;
    public:
        Pawn(char piece, bool isWhite);
        ~Pawn();

        void SetHasMovedTwoSteps(bool hasMovedTwoSteps) { this->hasMovedTwoSteps = hasMovedTwoSteps; };
        bool GetHasMovedTwoSteps() { return hasMovedTwoSteps; };

        bool GetCanMoveTwoSteps() { return canMoveTwoSteps; };
        void SetCanMoveTwoSteps() { canMoveTwoSteps = true; };
        bool GetCanEnPassantLeft() { return canEnPassantLeft; };
        void SetCanEnPassantLeft() { canEnPassantLeft = true; };
        bool GetCanEnPassantRight() { return canEnPassantRight; };
        void SetCanEnPassantRight() { canEnPassantRight = true; };

        void PreprocessAttackInfo(Board *);
        void SetLegalPositions(Board *);
};

#pragma endregion

#pragma region Command

class Command
{
    public:
        Command() {};
        virtual ~Command() {};

        virtual bool Execute() = 0;
        virtual bool Undo() = 0;
};

class AddPieceCommand : public Command
{
    private:
        PieceType pieceType;
        bool isWhite;
        Square* squareToAddAt;

    public:
        AddPieceCommand(PieceType pieceType, bool isWhite, Square* squareToAddAt)
        {
            this->pieceType = pieceType;
            this->isWhite = isWhite;
            this->squareToAddAt = squareToAddAt;
        }
        ~AddPieceCommand() {};

        bool Execute(Board*);
        bool Undo(Board*);
};

class RemovePieceCommand : public Command
{
    private:
        Piece* pieceToRemove;
        Square* squareToRemoveFrom;

    public:
        RemovePieceCommand(Square* squareToRemoveFrom)
        {
            this->squareToRemoveFrom = squareToRemoveFrom;
        }
        ~RemovePieceCommand() {};

        bool Execute();
        bool Undo();
};

class MoveCommand : public Command
{
    private:
        Piece* piece;
        Square* sourceSquare;
        Square* destinationSquare;

    public:
        MoveCommand(Piece* piece, Square* sourceSquare, Square* destinationSquare)
        {
            this->piece = piece;
            this->sourceSquare = sourceSquare;
            this->destinationSquare = destinationSquare;
        }
        ~MoveCommand() {};

        bool Execute();
        bool Undo();
};

class CaptureCommand : public Command
{
    private:
        Piece* attackingPiece;
        Piece* capturedPiece;

    public:
        CaptureCommand(Piece* attackingPiece, Piece* capturedPiece)
        {
            this->attackingPiece = attackingPiece;
            this->capturedPiece = capturedPiece;
        }
        ~CaptureCommand() {};

        bool Execute();
        bool Undo();
};

class PromoteCommand : public Command
{
    private:
        PieceType typeToPromoteTo;
        Piece* pawnToPromote;
        Piece* promotedPiece;

    public:
        PromoteCommand(PieceType typeToPromoteTo, Piece* pawnToPromote)
        {
            this->typeToPromoteTo = typeToPromoteTo;
            this->pawnToPromote = pawnToPromote;
        }
        ~PromoteCommand() {};

        bool Execute();
        bool Undo();
};

class CastleCommand : public Command
{
    private:
        King* king;
        Rook* rook;

        Square* kingSource;
        Square* kingDestination;
        Square* rookSource;
        Square* rookDestination;

    public:
        CastleCommand(King *king, Rook *rook, Square* kingSource, Square *kingDestination, Square* rookSource, Square* rookDestination)
        {
            this->king = king;
            this->rook = rook;
            this->kingSource = kingSource;
            this->kingDestination = kingDestination;
            this->rookSource = rookSource;
            this->rookDestination = rookDestination;
        }
        ~CastleCommand() {};

        bool Execute();
        bool Undo();
};

class EnPassantCommand : public Command
{
    private:
        Pawn* pawn;
        Pawn* pawnToCapture;
        Square* sourceSquare;
        Square* destinationSquare;
        Square* capturingSquare;

    public:
        EnPassantCommand() {};
        ~EnPassantCommand() {};

        bool Execute();
        bool Undo();
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
        bool Game();
        bool InitiateTurn();

        Square *SelectSquareFromInput();
        bool ParseInput(string *, int *, int *);
};

#pragma endregion

std::tuple<PieceType, bool> GetPieceTypeAndIsWhiteForChar(char pieceChar);

char GetCharForPiece(Piece *piece);

string GetCodeForSquare(int row, int col);

string GetCodeForPiece(Piece *piece);

void GetCastlingPositions(int &rookRow, int &rookCol, int &kingRow, int &kingCol, bool isWhite, bool isLongCastling);

PieceType GetPromotionPieceType();

bool ProcessAttackInDirection(Board* board, Piece* piece, int rowDir, int colDir);

bool SetLegalMovesInDirection(Board* board, Piece* piece, int rowDir, int colDir);
