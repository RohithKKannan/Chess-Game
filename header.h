#include <iostream>
#include <unordered_map>
#include <sstream>
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

        bool ProcessAttackInDirection(Piece *piece, int rowDir, int colDir);
        bool SetLegalMovesInDirection(Piece *piece, int rowDir, int colDir);

        bool ProcessKnightAttack(Piece *knight, int row, int col);
        bool SetLegalMoveForKnight(Piece *knight, int row, int col);
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

std::tuple<PieceType, bool> static GetPieceTypeAndIsWhiteForChar(char pieceChar)
{
    PieceType pieceType;
    bool isWhite = (pieceChar >= 'A' && pieceChar <= 'Z');

    switch (tolower(pieceChar))
    {
    case 'k':
        pieceType = PieceType::King;
        break;
    case 'q':
        pieceType = PieceType::Queen;
        break;
    case 'b':
        pieceType = PieceType::Bishop;
        break;
    case 'n':
        pieceType = PieceType::Knight;
        break;
    case 'r':
        pieceType = PieceType::Rook;
        break;
    case 'p':
        pieceType = PieceType::Pawn;
        break;
    default:
        return {PieceType::None, false};
    }

    return {pieceType, isWhite};
}

char static GetCharForPiece(Piece *piece)
{
    bool isWhite = piece->GetIsWhite();
    switch (piece->GetPieceType())
    {
    case PieceType::King:
        return isWhite ? 'K' : 'k';
    case PieceType::Queen:
        return isWhite ? 'Q' : 'q';
    case PieceType::Bishop:
        return isWhite ? 'B' : 'b';
    case PieceType::Knight:
        return isWhite ? 'N' : 'n';
    case PieceType::Rook:
        return isWhite ? 'R' : 'r';
    case PieceType::Pawn:
        return isWhite ? 'P' : 'p';
    }

    return '-';
}

string static GetCodeForPiece(Piece *piece)
{
    std::ostringstream oss;

    char pieceChar = GetCharForPiece(piece);

    char xPos = (char)piece->GetPosition().col + 'A';
    char yPos = (char)(piece->GetPosition().row + '1');

    oss << pieceChar << xPos << yPos;

    if(piece->GetIsKing())
    {
        King* king = (King*)piece;
        if(king->GetIsShortCastlingPossible())
            oss << "/" << "o-o";
        if(king->GetIsLongCastlingPossible())
            oss << "/" << "o-o-o";
    }

    if(piece->GetPieceType() == PieceType::Pawn)
    {
        Pawn* pawn = (Pawn*)piece;

        if(pawn->GetCanMoveTwoSteps())
            oss << "/" << "T";
        if(pawn->GetCanEnPassantLeft())
            oss << "/" << "L";
        if(pawn->GetCanEnPassantRight())
            oss << "/" << "R"; 
    }

    return oss.str();
}

string static GetCodeForSquare(int row, int col)
{
    char xPos = (char)col + 'A';
    char yPos = (char)(row + '1');

    std::ostringstream oss;
    oss << xPos << yPos;
    return oss.str();
}

void static GetCastlingPositions(int &rookRow, int &rookCol, int &kingRow, int &kingCol, bool isWhite, bool isLongCastling)
{
    // if king is white and short castle, then king moves to G1 and rook moves to F1
    // if king is white and long castle, then king moves to C1 and rook moves to D1
    // if king is black and short castle, then king moves to G8 and rook moves to F8
    // if king is black and long castle, then king moves to C8 and rook moves to D8

    if (isWhite)
    {
        kingRow = 0;
        kingCol = isLongCastling ? 2 : 6;
        rookRow = 0;
        rookCol = isLongCastling ? 3 : 5;
    }
    else
    {
        kingRow = 7;
        kingCol = isLongCastling ? 2 : 6;
        rookRow = 7;
        rookCol = isLongCastling ? 3 : 5;
    }
}

PieceType static GetPromotionPieceType()
{
    char pieceChar;

    while(pieceChar != 'Q' && pieceChar != 'R' && pieceChar != 'B' && pieceChar != 'N')
    {
        cout << "Enter the piece type to promote to (Q/R/B/N): ";
        cin >> pieceChar;

        switch (pieceChar)
        {
            case 'Q':
                return PieceType::Queen;
            case 'R':
                return PieceType::Rook;
            case 'B':
                return PieceType::Bishop;
            case 'N':
                return PieceType::Knight;
            default:
                cout << "Invalid piece type! Please enter a valid piece type (Q/R/B/N): ";
                break;
        }
    }

    return PieceType::None;
}
