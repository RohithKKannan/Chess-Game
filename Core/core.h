#pragma once

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

enum GameState
{
	Menu,
    WhiteTurn,
    BlackTurn,
    Stalemate,
    WhiteWins,
    BlackWins,
    Draw
};

enum InputState
{
	Idle,
	WaitingForSourceSelect,
	WaitingForDestinationSelect
};

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
