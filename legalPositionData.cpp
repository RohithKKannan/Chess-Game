#include "header.h"

LegalPositionData::LegalPositionData()
{
    legalPositions = new Position[100];
    legalPositionsWithoutKing = new Position[100];
    numberOfPositions = 0;
    numberOfPositionsWithoutKing = 0;
}

LegalPositionData::~LegalPositionData()
{
    delete[] legalPositions;
    delete[] legalPositionsWithoutKing;
}