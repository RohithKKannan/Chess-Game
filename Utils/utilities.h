#pragma once

#include <tuple>
#include <string>

#include "../Core/core.h"
#include "../Pieces/piece.h"

class Board;

// Singleton class
class Utilities
{
	private:
		Utilities();
		
    	spn::Image whiteKingImage;
        spn::Image whiteQueenImage;
        spn::Image whiteBishopImage;
        spn::Image whiteKnightImage;
        spn::Image whiteRookImage;
        spn::Image whitePawnImage;
        
        spn::Image blackKingImage;
        spn::Image blackQueenImage;
        spn::Image blackBishopImage;
        spn::Image blackKnightImage;
        spn::Image blackRookImage;
        spn::Image blackPawnImage;
        
    public:
    	static Utilities& GetInstance()
    	{
    		static Utilities instance;
    		return instance;
		}
		
		void InitializePieceImages();
    	
    	spn::Image* GetImageForPiece(PieceType, bool);
};

PieceType GetPieceTypeForChar(char pieceChar);

bool GetIsWhiteForChar(char pieceChar);

char GetCharForPiece(Piece *piece);

std::string GetCodeForSquare(int row, int col);

std::string GetCodeForPiece(Piece* piece);

void GetCastlingPositions(int &rookRow, int &rookCol, int &kingRow, int &kingCol, bool isWhite, bool isLongCastling);

PieceType GetPromotionPieceType();

bool ProcessAttackInDirection(Board* board, Piece* piece, int rowDir, int colDir);

bool SetLegalMovesInDirection(Board* board, Piece* piece, int rowDir, int colDir);
