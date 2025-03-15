#include "header.h"

LegalPositionData::LegalPositionData()
{
    legalPositions = new Position[100];
    numberOfPositions = 0;
}

LegalPositionData::~LegalPositionData()
{
    delete[] legalPositions;
}