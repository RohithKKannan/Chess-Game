#include "header.h"

LegalPositions::LegalPositions()
{
    positions = new Position[100];
    numberOfPositions = 0;
}

LegalPositions::~LegalPositions()
{
    delete[] positions;
}