#pragma once

#include <tuple>
#include <string>

#include "../Core/core.h"
#include "../Pieces/piece.h"

class Board;

PieceType GetPieceTypeForChar(char pieceChar);

bool GetIsWhiteForChar(char pieceChar);

char GetCharForPiece(Piece *piece);

std::string GetCodeForSquare(int row, int col);

std::string GetCodeForPiece(Piece* piece);

void GetCastlingPositions(int &rookRow, int &rookCol, int &kingRow, int &kingCol, bool isWhite, bool isLongCastling);

PieceType GetPromotionPieceType();

bool ProcessAttackInDirection(Board* board, Piece* piece, int rowDir, int colDir);

bool SetLegalMovesInDirection(Board* board, Piece* piece, int rowDir, int colDir);
